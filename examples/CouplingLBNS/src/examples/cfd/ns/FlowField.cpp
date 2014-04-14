#include "FlowField.h"

FlowField::FlowField ( int Nx, int Ny ) :
    _size_x ( Nx ), _size_y ( Ny ), _size_z ( 1 ),
    _cellsX (Nx+3), _cellsY(Ny+3), _cellsZ(1),
    _dim ( 2 ),

    // Pressure field doesn't need to have an extra layer, but this allows to address the same
    // positions with the same iterator for both pressures and velocities.
    _pressure ( ScalarField ( Nx + 3, Ny + 3 ) ),
    _velocity ( VectorField ( Nx + 3, Ny + 3 ) ), _flags ( IntScalarField ( Nx + 3, Ny + 3 ) ),
    _cellIdsX ( IntScalarField ( Nx + 3, Ny + 3 ) ),
    _cellIdsY ( IntScalarField ( Nx + 3, Ny + 3 ) ),
    _cellIdsZ ( IntScalarField ( Nx + 3, Ny + 3 ) ),
    _FGH ( VectorField ( Nx + 3, Ny + 3 ) ), _RHS ( ScalarField (Nx + 3, Ny + 3) ) {

    assertion ( Nx > 0 );
    assertion ( Ny > 0 );
}


FlowField::FlowField ( int Nx, int Ny, int Nz ) :
    _size_x ( Nx ), _size_y ( Ny ), _size_z ( Nz ),
    _cellsX (Nx+3), _cellsY(Ny+3), _cellsZ(Nz+3),
    _dim (3),
    _pressure ( ScalarField ( Nx + 3, Ny + 3, Nz + 3 ) ),
    _velocity  ( VectorField ( Nx + 3, Ny + 3, Nz + 3 ) ),
    _flags  ( IntScalarField ( Nx + 3, Ny + 3, Nz +3 ) ),
    _cellIdsX(IntScalarField ( Nx + 3, Ny + 3, Nz +3 ) ),
    _cellIdsY(IntScalarField ( Nx + 3, Ny + 3, Nz +3 ) ),
    _cellIdsZ(IntScalarField ( Nx + 3, Ny + 3, Nz +3 ) ),
    _FGH ( VectorField ( Nx + 3, Ny + 3, Nz + 3 ) ),
    _RHS ( ScalarField ( Nx + 3, Ny + 3, Nz + 3 ) ) {


    // Check that the provided data makes sense
    assertion ( Nx > 0 );
    assertion ( Ny > 0 );
    assertion ( Nz > 0 );
}


FlowField::FlowField (const Parameters & parameters):
    _size_x(parameters.parallel.localSize[0]),
    _size_y(parameters.parallel.localSize[1]),
    _size_z(parameters.parallel.localSize[2]),
    _cellsX(_size_x+3),
    _cellsY(_size_y+3),
    _cellsZ(_size_z+3),
    _dim(parameters.geometry.dim),
    // Probably far from the best way to write this
    _pressure(_dim==2?ScalarField(_size_x + 3, _size_y + 3):
                      ScalarField(_size_x + 3, _size_y + 3, _size_z + 3)),
    _velocity(_dim==2?VectorField(_size_x + 3, _size_y + 3):
                      VectorField(_size_x + 3, _size_y + 3, _size_z + 3)),
    _flags(_dim==2?IntScalarField(_size_x + 3, _size_y + 3):
                   IntScalarField(_size_x + 3, _size_y + 3, _size_z + 3)),
    _cellIdsX(_dim==2?IntScalarField(_size_x + 3, _size_y + 3):
    IntScalarField(_size_x + 3, _size_y + 3, _size_z + 3)),
    _cellIdsY(_dim==2?IntScalarField(_size_x + 3, _size_y + 3):
	IntScalarField(_size_x + 3, _size_y + 3, _size_z + 3)),
	_cellIdsZ(_dim==2?IntScalarField(_size_x + 3, _size_y + 3):
    IntScalarField(_size_x + 3, _size_y + 3, _size_z + 3)),
    _FGH(_dim==2?VectorField(_size_x + 3, _size_y + 3):
                 VectorField(_size_x + 3, _size_y + 3, _size_z + 3)),
    _RHS(_dim==2?ScalarField(_size_x + 3, _size_y + 3):
                 ScalarField(_size_x + 3, _size_y + 3, _size_z + 3))
{}

void FlowField::copyToField(FlowField & dest){
    FLOAT *vDest, *vSource;
    // Consider only the 3D case
    for (int k = 0; k < _cellsZ; k++){
        for (int j = 0; j < _cellsY; j++){
            for (int i = 0; i < _cellsX; i++){

                // Copy pressure
                dest.getPressure().getScalar(i, j, k) =
                    _pressure.getScalar(i, j, k);

                // Copy velocity
                vSource = _velocity.getVector(i, j, k);
                vDest = dest.getVelocity().getVector(i, j, k);
                vDest[0] = vSource[0];
                vDest[1] = vSource[1];
                vDest[2] = vSource[2];
            }
        }
    }
}

void FlowField::interpolate(FlowField & past, FlowField & future, FLOAT t){
    FLOAT *vPast, *vFuture, *vThis;
    for (int k = 0; k < _cellsZ; k++){
        for (int j = 0; j < _cellsY; j++){
            for (int i = 0; i < _cellsX; i++){
                _pressure.getScalar(i, j, k) =
                    (1.0 - t) * past.getPressure().getScalar(i, j, k) +
                           t  * future.getPressure().getScalar(i, j, k);

                vThis = _velocity.getVector(i, j, k);
                vPast =     past.getVelocity().getVector(i, j, k);
                vFuture = future.getVelocity().getVector(i, j, k);
                vThis[0] = (1.0 - t) * vPast[0] + t * vFuture[0];
                vThis[1] = (1.0 - t) * vPast[1] + t * vFuture[1];
                vThis[2] = (1.0 - t) * vPast[2] + t * vFuture[2];
            }
        }
    }
}

int FlowField::getDim () const{
    return _dim;
}


int FlowField::getNx () const{
    return _size_x;
}


int FlowField::getNy () const{
    return _size_y;
}


int FlowField::getNz () const{
    return _size_z;
}


int FlowField::getCellsX() const{
    return _cellsX;
}

int FlowField::getCellsY() const{
    return _cellsY;
}

int FlowField::getCellsZ() const{
    return _cellsZ;
}


ScalarField & FlowField::getPressure () {
    return _pressure;
}


VectorField & FlowField::getVelocity () {
    return _velocity;
}


IntScalarField & FlowField::getFlags () {
    return _flags;
}
IntScalarField & FlowField::getCellIdsX () {
    return _cellIdsX;
}

IntScalarField & FlowField::getCellIdsY () {
    return _cellIdsY;
}
IntScalarField & FlowField::getCellIdsZ () {
    return _cellIdsZ;
}

VectorField & FlowField::getFGH () {
    return _FGH;
}


ScalarField & FlowField::getRHS () {
    return _RHS;
}

void FlowField::getPressureAndVelocity(FLOAT &pressure, FLOAT* &velocity, int i, int j){
    FLOAT * v_here = getVelocity().getVector(i, j);
    FLOAT * v_left = getVelocity().getVector(i-1, j);
    FLOAT * v_down = getVelocity().getVector(i, j-1);

    _localVelocity[0] = ( v_here[0] + v_left[0] ) / 2;
    _localVelocity[1] = ( v_here[1] + v_down[1] ) / 2;

    pressure = getPressure().getScalar(i,j);
    velocity = _localVelocity;
}

void FlowField::getPressureAndVelocity(FLOAT &pressure, FLOAT* &velocity, int i, int j, int k){
    FLOAT * v_here = getVelocity().getVector(i, j, k);
    FLOAT * v_left = getVelocity().getVector(i-1, j, k);
    FLOAT * v_down = getVelocity().getVector(i, j-1, k);
    FLOAT * v_back = getVelocity().getVector(i, j, k-1);

    _localVelocity[0] = ( v_here[0] + v_left[0] ) / 2;
    _localVelocity[1] = ( v_here[1] + v_down[1] ) / 2;
    _localVelocity[2] = ( v_here[2] + v_back[2] ) / 2;

    pressure = getPressure().getScalar(i,j,k);
    velocity = _localVelocity;
}
