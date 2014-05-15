#include "LBNSInterpolator.h"
#include "math.h"

void LBNSInterpolator::printParameters() {
    std::cout << "LB -> NS coupling parameters" << std::endl;
    std::cout << "LowerX: " << _lowerX << std::endl;
    std::cout << "UpperX: " << _upperX << std::endl;
    std::cout << "LowerY: " << _lowerY << std::endl;
    std::cout << "UpperY: " << _upperY << std::endl;
    std::cout << "LowerZ: " << _lowerZ << std::endl;
    std::cout << "UpperZ: " << _upperZ << std::endl;
    std::cout << "Ratio: " << _M << std::endl;
    std::cout << "Half M: " << _halfM << std::endl;
    std::cout << "Modulo: " << _modulo << std::endl;
    std::cout << "Reciprocal ratio: " << _reciprocalRatio << std::endl << std::endl;
}

LBNSInterpolator::LBNSInterpolator (const Parameters & parameters, const LBField & lbField) :
    _parameters (parameters), _lbField (lbField),
    // Add 2 to refer to fluid cells and not to the boundaries
    // The upper limits refer to the last cell inside the overlap region
    _lowerX (parameters.coupling.offsetNS[0]),
    _upperX (_lowerX + parameters.coupling.sizeNS[0] - 1),
    _lowerY (parameters.coupling.offsetNS[1]),
    _upperY (_lowerY + parameters.coupling.sizeNS[1] - 1),
    _lowerZ (parameters.coupling.offsetNS[2]),
    _upperZ (_lowerZ + parameters.coupling.sizeNS[2] - 1),
    _M (parameters.coupling.ratio),
    _halfM (_M / 2),    // Should return the floor of the float operation if operating with ints
    _modulo (_M % 2),
    _reciprocalRatio (1.0 / _M),
    _dx (parameters.coupling.refLength / _M),
    _dt (parameters.lb.viscosity * parameters.flow.Re * _dx * _dx),
    _referenceVelocity (_dx / _dt)
{
    printParameters();
}

// Location will be provided by two integer arrays. One will define the LB cell where the point is
// contained, and the other will tell if, in each direction, the position of the point is in the
// beginning or the middle. The possible position for points in the grid for this problem is a
// discrete set of points anyway, so, out of preference, I will not use floating point numbers.

void LBNSInterpolator::locateInLBGrid (int * const lbPosition, int * const middle,
                                       int ins, int jns, int kns, int component) {

    // At first, locate the point in the center of the NS cell. We will correct later
    lbPosition[0] = _M * (ins - _lowerX) + _halfM + _modulo;
    lbPosition[1] = _M * (jns - _lowerY) + _halfM + _modulo;
    lbPosition[2] = _M * (kns - _lowerZ) + _halfM + _modulo;

    // In this case, the modulo tells if the value is the middle of the cell
    middle[0] = 1 - _modulo;
    middle[1] = 1 - _modulo;
    middle[2] = 1 - _modulo;

    if (component < 3) {    // If we are dealing with a velocity component, there are more steps
        lbPosition[component] += _halfM;    // Move it to the upper end
        middle[component] = 1;  // In this direction, it will always lie on the edge
    } // Notice that we might rewrite values. This kills performance, right?
}


void LBNSInterpolator::loadDensity (){
    for (int l = 0; l < stencilSize; l++){
        _values[l] = _lbField.getDensity(_lbField.getFOut(),
                                         _offset[0] + stencil[l][0] * _flip[0],
                                         _offset[1] + stencil[l][1] * _flip[1],
                                         _offset[2] + stencil[l][2] * _flip[2]);
    }
}

void LBNSInterpolator::loadVelocityComponent (const int & component){
    // This function is far from being efficient. It loads the whole velocity vector to get only
    // one of its components, but it avoids rewriting all the velocity functions only for this
    // operation.
    // TODO split components of velocity right in the LB field
    FLOAT temporalVelocity[3];
    FLOAT density;
    for (int l = 0; l < stencilSize; l++){
        density = _lbField.getDensity(_lbField.getFOut(),
                                      _offset[0] + stencil[l][0] * _flip[0],
                                      _offset[1] + stencil[l][1] * _flip[1],
                                      _offset[2] + stencil[l][2] * _flip[2]);
        _lbField.getVelocity(density, temporalVelocity, _lbField.getFOut(),
                             _offset[0] + stencil[l][0] * _flip[0],
                             _offset[1] + stencil[l][1] * _flip[1],
                             _offset[2] + stencil[l][2] * _flip[2]);
        _values[l] = temporalVelocity[component];
    }
}

bool LBNSInterpolator::checkIfValid (const int * const lbPosition, const int * const middle) {
    return true;
}

void LBNSInterpolator::setArrays (const int * const lbPosition, const int * const middle){
    // First, set the flip array. If the point required doesn't have enough valid points in the
    // upper side, flip it to take them from the lower side.
    if (lbPosition[0] < _lbField.getCellsX() / 2){
        _flip[0] = 1;
    } else {
        _flip[0] = -1;
    }
    if (lbPosition[1] < _lbField.getCellsY() / 2){
        _flip[1] = 1;
    } else {
        _flip[1] = -1;
    }
    if (lbPosition[2] < _lbField.getCellsZ() / 2){
        _flip[2] = 1;
    } else {
        _flip[2] = -1;
    }

    // With the flip set, we proceed to compute offsets and regularized positions.
    for (int l = 0; l < 3; l++){
        if (_flip[l] == 1) {
            _offset[l] = lbPosition[l] - 1 + middle[l];
        } else {    // If the stencil was flipped in this direction
            _offset[l] = lbPosition[l];
        }
        // This one is easy to see. If the point is not sitting directly on one of the cells in one
        // direction, it has to be in the position 0.5
        _regularizedPosition[l] = 0.5 * (double)(1 - middle[l]);
    }
}

FLOAT LBNSInterpolator::interpolateVelocityComponent (int ins, int jns, int kns, int component){
    int lbPosition[3], middle[3];
    locateInLBGrid (lbPosition, middle, ins, jns, kns, component);
    if (!checkIfValid (lbPosition, middle)){
        std::cerr << "Trying to interpolate position " << ins << ", " << jns << ", " << kns <<
            std::endl;
        handleError (1,"Position cannot be interpolated");
    }

    // The velocities will never lie in the very center of a LB cell, so there's no need to check.

    setArrays (lbPosition, middle);
    loadVelocityComponent (component);
    getLocationVector (_locationVector, _regularizedPosition);
    matrix_vector(barycentricBasis, _locationVector, _weights, stencilSize, stencilSize);
    return dot(_values, _weights, stencilSize) * _referenceVelocity;
}


FLOAT LBNSInterpolator::interpolatePressure (int ins, int jns, int kns) {
    int lbPosition[3], middle[3];
    locateInLBGrid (lbPosition, middle, ins, jns, kns, 3);
    std::cout << lbPosition[0] << ", " << lbPosition[1] << ", " << lbPosition[2] << std::endl;
    if (!checkIfValid (lbPosition, middle)){
        std::cerr << "Trying to interpolate position " << ins << ", " << jns << ", " << kns <<
            std::endl;
        handleError (1,"Position cannot be interpolated");
    }

    if (middle[0] == 1 && middle[1] == 1 && middle[2] == 1) {   // If we're standing on a LB cell
        // there is no need to interpolate. Can only happen for pressure
        return _lbField.getDensity (_lbField.getFOut(), lbPosition[0], lbPosition[1],lbPosition[2]);
    }

    setArrays (lbPosition, middle);
    loadDensity();
    getLocationVector (_locationVector, _regularizedPosition);
    matrix_vector(barycentricBasis, _locationVector, _weights, stencilSize, stencilSize);
    return dot(_values, _weights, stencilSize);
}
