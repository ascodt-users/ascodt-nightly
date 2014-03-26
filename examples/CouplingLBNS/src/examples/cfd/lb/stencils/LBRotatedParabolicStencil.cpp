#include "LBRotatedParabolicStencil.h"
#include "LBFunctions.h"
#include <math.h>

LBRotatedParabolicStencil::LBRotatedParabolicStencil (const Parameters & parameters,

        FLOAT gradRhoX, FLOAT gradRhoY, FLOAT gradRhoZ,
        FLOAT plateNormalX, FLOAT plateNormalY, FLOAT plateNormalZ):
    GlobalBoundaryStencil<LBField>(parameters){

    _gradRho[0] = gradRhoX;
    _gradRho[1] = gradRhoY;
    _gradRho[2] = gradRhoZ;

    // First, normalize the density gradient, to extract the direction.

    _gradNorm = sqrt(gradRhoX * gradRhoX + gradRhoY * gradRhoY + gradRhoZ * gradRhoZ);
    _speedFactor = (0.5 / (parameters.lb.tau - 0.5) * _gradNorm);

    _unitaryGradRho[0] = gradRhoX / _gradNorm;
    _unitaryGradRho[1] = gradRhoY / _gradNorm;
    _unitaryGradRho[2] = gradRhoZ / _gradNorm;

    // Project the given plate normal vector to the plane normal to gradRho, in case that the given
    // value is not there. Normalize afterwards

    _plateNormal[0] = plateNormalX;
    _plateNormal[1] = plateNormalY;
    _plateNormal[2] = plateNormalZ;

    const FLOAT component = getGradRhoComponent (_plateNormal);

    _plateNormal[0] -= component * _unitaryGradRho[0];
    _plateNormal[1] -= component * _unitaryGradRho[1];
    _plateNormal[2] -= component * _unitaryGradRho[2];

    const FLOAT plateNormalMagnitude = sqrt(_plateNormal[0] * _plateNormal[0] +
                                            _plateNormal[1] * _plateNormal[1] +
                                            _plateNormal[2] * _plateNormal[2]);

    _plateNormal[0] /= plateNormalMagnitude;
    _plateNormal[1] /= plateNormalMagnitude;
    _plateNormal[2] /= plateNormalMagnitude;

    // Identify one of the support points, and then compute the distance between the planes

    const FLOAT halfDomainPlate = 0.5 * (double)(parameters.geometry.sizeX + 2);
    FLOAT support[3] = {halfDomainPlate, halfDomainPlate, halfDomainPlate};
    _pivot[0] = 0.0;
    _pivot[1] = 0.0;
    _pivot[2] = 0.0;

    if (_plateNormal[0] < 0){
        support[0] = -halfDomainPlate;
        _pivot[0] = (double)(parameters.geometry.sizeX + 2);
    }

    if (_plateNormal[1] < 0){
        support[1] = -halfDomainPlate;
        _pivot[1] = (double)(parameters.geometry.sizeX + 2);
    }

    if (_plateNormal[2] < 0){
        support[2] = -halfDomainPlate;
        _pivot[2] = (double)(parameters.geometry.sizeX + 2);
    }

    _halfPlateSeparation = getPlateNormalComponent (support);
    _plateSeparation = 2 * _halfPlateSeparation;
    assertion (plateSeparation > 0);

    // Set the densities on the reference points

    const FLOAT halfDomainCenter = 0.5 * (double)(parameters.geometry.sizeX + 1);
    FLOAT temporalCorner[3] = {-halfDomainCenter, -halfDomainCenter, -halfDomainCenter}; // Temporal relative location of corners
    _firstDensity0 = 1.0 + _gradNorm * getGradRhoComponent (temporalCorner);

    temporalCorner[0] = halfDomainCenter;
    _firstDensityX = 1.0 + _gradNorm * getGradRhoComponent (temporalCorner);

    temporalCorner[0] = -halfDomainCenter;
    temporalCorner[1] = halfDomainCenter;
    _firstDensityY = 1.0 + _gradNorm * getGradRhoComponent (temporalCorner);

    temporalCorner[1] = -halfDomainCenter;
    temporalCorner[2] = halfDomainCenter;
    _firstDensityZ = 1.0 + _gradNorm * getGradRhoComponent (temporalCorner);
}

FLOAT LBRotatedParabolicStencil::getGradRhoComponent (const FLOAT * const vector) const {
    return vector[0] * _unitaryGradRho[0] +
           vector[1] * _unitaryGradRho[1] +
           vector[2] * _unitaryGradRho[2];
}

FLOAT LBRotatedParabolicStencil::getPlateNormalComponent (const FLOAT * const vector) const {
    return vector[0] * _plateNormal[0] +
           vector[1] * _plateNormal[1] +
           vector[2] * _plateNormal[2];
}

void setDistribution (LBField & field, FLOAT tau, FLOAT density, FLOAT sValue, FLOAT speedFactor,
                      const FLOAT * const unitaryGradRho, const FLOAT * const plateNormal,
                      FLOAT plateSeparation, int i, int j, int k){

    assertion (sValue > 0);
    const FLOAT speed = speedFactor * sValue * (sValue - plateSeparation);

    FLOAT velocity[3] = {speed * unitaryGradRho[0],
                         speed * unitaryGradRho[1],
                         speed * unitaryGradRho[2]};

    FLOAT equilibrium[Q], nequilibrium[Q];
    computeEquilibrium (equilibrium, density, velocity);

    // Find the stress value in the plates system of coordinates. d u^hat / d z^hat.
    const FLOAT derivativeFactor = speedFactor * (2 * sValue - plateSeparation);
    computeMinimumNonEquilibrium (nequilibrium, tau, density,

            // The nine components of the velocity Jacobian
            unitaryGradRho[0] * plateNormal[0] * derivativeFactor,
            unitaryGradRho[0] * plateNormal[1] * derivativeFactor,
            unitaryGradRho[0] * plateNormal[2] * derivativeFactor,

            unitaryGradRho[1] * plateNormal[0] * derivativeFactor,
            unitaryGradRho[1] * plateNormal[1] * derivativeFactor,
            unitaryGradRho[1] * plateNormal[2] * derivativeFactor,

            unitaryGradRho[2] * plateNormal[0] * derivativeFactor,
            unitaryGradRho[2] * plateNormal[1] * derivativeFactor,
            unitaryGradRho[2] * plateNormal[2] * derivativeFactor
            );

    for (int l = 0; l < Q; l++){
        field.getFIn() [field.getIndexF(l, i, j, k)] = equilibrium[l] + (1.0 - 1.0/tau) * nequilibrium[l];
        field.getFOut()[field.getIndexF(l, i, j, k)] = equilibrium[l] + (1.0 - 1.0/tau) * nequilibrium[l];
    }
}

// 2D versions not used
void LBRotatedParabolicStencil::applyLeftWall   (LBField & field, int i, int j){}
void LBRotatedParabolicStencil::applyRightWall  (LBField & field, int i, int j){}
void LBRotatedParabolicStencil::applyBottomWall (LBField & field, int i, int j){}
void LBRotatedParabolicStencil::applyTopWall    (LBField & field, int i, int j){}

void LBRotatedParabolicStencil::applyLeftWall   (LBField & field, int i, int j, int k){
    const FLOAT density = _firstDensity0 + j * _gradRho[1] + k * _gradRho[2];
    FLOAT relativePosition[3] = {(double)i - _pivot[0] + 0.5, (double)j - _pivot[1] + 0.5, (double)k - _pivot[2] + 0.5};

    // Notice that here and after, sValue is computed as increasing with the selection of plate
    // normal. It is important to be consistent here with the rotation
    const FLOAT sValue = getPlateNormalComponent (relativePosition);

    setDistribution (field, _parameters.lb.tau, density, sValue, _speedFactor, _unitaryGradRho,
                     _plateNormal, _plateSeparation, i, j, k);
}

void LBRotatedParabolicStencil::applyRightWall  (LBField & field, int i, int j, int k){
    const FLOAT density = _firstDensityX + j * _gradRho[1] + k * _gradRho[2];
    FLOAT relativePosition[3] = {(double)i - _pivot[0] + 0.5, (double)j - _pivot[1] + 0.5, (double)k - _pivot[2] + 0.5};
    const FLOAT sValue = getPlateNormalComponent (relativePosition);

    setDistribution (field, _parameters.lb.tau, density, sValue, _speedFactor, _unitaryGradRho,
                     _plateNormal, _plateSeparation, i, j, k);
}

void LBRotatedParabolicStencil::applyBottomWall (LBField & field, int i, int j, int k){
    const FLOAT density = _firstDensity0 + i * _gradRho[0] + k * _gradRho[2];
    FLOAT relativePosition[3] = {(double)i - _pivot[0] + 0.5, (double)j - _pivot[1] + 0.5, (double)k - _pivot[2] + 0.5};
    const FLOAT sValue = getPlateNormalComponent (relativePosition);

    setDistribution (field, _parameters.lb.tau, density, sValue, _speedFactor, _unitaryGradRho,
                     _plateNormal, _plateSeparation, i, j, k);
}

void LBRotatedParabolicStencil::applyTopWall    (LBField & field, int i, int j, int k){
    const FLOAT density = _firstDensityY + i * _gradRho[0] + k * _gradRho[2];
    FLOAT relativePosition[3] = {(double)i - _pivot[0] + 0.5, (double)j - _pivot[1] + 0.5, (double)k - _pivot[2] + 0.5};
    const FLOAT sValue = getPlateNormalComponent (relativePosition);

    setDistribution (field, _parameters.lb.tau, density, sValue, _speedFactor, _unitaryGradRho,
                     _plateNormal, _plateSeparation, i, j, k);
}

void LBRotatedParabolicStencil::applyFrontWall  (LBField & field, int i, int j, int k){
    const FLOAT density = _firstDensity0 + i * _gradRho[0] + j * _gradRho[1];
    FLOAT relativePosition[3] = {(double)i - _pivot[0] + 0.5, (double)j - _pivot[1] + 0.5, (double)k - _pivot[2] + 0.5};
    const FLOAT sValue = getPlateNormalComponent (relativePosition);

    setDistribution (field, _parameters.lb.tau, density, sValue, _speedFactor, _unitaryGradRho,
                     _plateNormal, _plateSeparation, i, j, k);
}

void LBRotatedParabolicStencil::applyBackWall   (LBField & field, int i, int j, int k){
    const FLOAT density = _firstDensityZ + i * _gradRho[0] + j * _gradRho[1];
    FLOAT relativePosition[3] = {(double)i - _pivot[0] + 0.5, (double)j - _pivot[1] + 0.5, (double)k - _pivot[2] + 0.5};
    const FLOAT sValue = getPlateNormalComponent (relativePosition);

    setDistribution (field, _parameters.lb.tau, density, sValue, _speedFactor, _unitaryGradRho,
                     _plateNormal, _plateSeparation, i, j, k);
}

const FLOAT * const LBRotatedParabolicStencil::getPlateNormal() const {
    return _plateNormal;
}

const FLOAT * const LBRotatedParabolicStencil::getUnitaryGradRho() const {
    return _unitaryGradRho;
}

const FLOAT * const LBRotatedParabolicStencil::getPivot() const {
    return _pivot;
}

const FLOAT LBRotatedParabolicStencil::getGradientMagnitude () const {
    return _gradNorm;
}

const FLOAT LBRotatedParabolicStencil::getPlateSeparation () const {
    return _plateSeparation;
}
