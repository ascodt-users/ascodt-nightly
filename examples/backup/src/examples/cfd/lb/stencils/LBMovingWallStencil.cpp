#include "LBMovingWallStencil.h"

// These represent the indices of the lattice velocities that have components in the named
// direction and corresponding dimension. They depend on what is stated in the LB Definitions

#ifdef D3Q19
const int velocitiesLeft3D[5] =   {1, 5, 8, 11, 15};
const int velocitiesRight3D[5] =  {3, 7, 10, 13, 17};
const int velocitiesBottom3D[5] = {0, 5, 6, 7, 14};
const int velocitiesTop3D[5] =    {4, 11, 12, 13, 18};
const int velocitiesFront3D[5] =  {0, 1, 2, 3, 4};
const int velocitiesBack3D[5] =   {14, 15, 16, 17, 18};
const int wallVelocityCount = 5;
#endif

#ifdef D3Q27
const int velocitiesLeft3D  [9] = {0, 3, 6, 9, 12, 15, 18, 21, 24};
const int velocitiesRight3D [9] = {2, 5, 8, 11, 14, 17, 20, 23, 26};
const int velocitiesBottom3D[9] = {0, 1, 2, 9, 10, 11, 18, 19, 20};
const int velocitiesTop3D   [9] = {6, 7, 8, 15, 16, 17, 24, 25, 26};
const int velocitiesFront3D [9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const int velocitiesBack3D  [9] = {18, 19, 20, 21, 22, 23, 24, 25, 25};
const int wallVelocityCount = 9;
#endif

#ifdef D3Q15
const int velocitiesLeft3D  [5] = {0, 3, 6, 10, 13};
const int velocitiesRight3D [5] = {1, 4, 8, 11, 14};
const int velocitiesBottom3D[5] = {0, 1, 5, 10, 11};
const int velocitiesTop3D   [5] = {3, 4, 9, 13, 14};
const int velocitiesFront3D [5] = {0, 1, 2, 3, 4};
const int velocitiesBack3D  [5] = {10, 11, 12, 13, 14};
const int wallVelocityCount = 5;
#endif

const int velocitiesLeft2D[3] = {6, 7, 8};
const int velocitiesRight2D[3] = {0, 1, 2};
const int velocitiesBottom2D[3] = {2, 3, 8};
const int velocitiesTop2D[3] = {0, 5, 6};

const FLOAT factor = 2 * reciprocalC * reciprocalC;

void prepareBoundaries(const int* indices, LBField & field, const FLOAT* const wallVelocity, int i, int j, int k = 0){
    // These values depend on the set of velocities used
    const int velocityCount = field.getDim() == 2 ? 3 : wallVelocityCount;
    const FLOAT density = field.getDensity(field.getFIn(), i, j, k);
    FLOAT product;
    int velocity[3];

    for (int n = 0; n < velocityCount; n++){
        product = 0;

        velocity[0] = field.getLatticeVelocities()[indices[n]][0];
        velocity[1] = field.getLatticeVelocities()[indices[n]][1];
        velocity[2] = field.getLatticeVelocities()[indices[n]][2];

        for (int l = 0; l < field.getDim(); l++){
            product -= velocity[l] * wallVelocity[l];
        }

        field.getFIn()[field.getIndexF(field.getInverse(indices[n]), i+velocity[0], j+velocity[1], k+velocity[2])] =
            field.getFIn()[field.getIndexF(indices[n], i, j, k)] +
            factor * field.getLatticeWeights()[indices[n]] * density * product;
    }
}


LBMovingWallStencil::LBMovingWallStencil(const Parameters & parameters):
    GlobalBoundaryStencil<LBField> (parameters) {}

void LBMovingWallStencil::applyLeftWall   ( LBField & field, int i, int j ){
    prepareBoundaries(velocitiesLeft2D, field, _parameters.walls.vectorLeft, i, j);
}

void LBMovingWallStencil::applyRightWall  ( LBField & field, int i, int j ){
    prepareBoundaries(velocitiesRight2D, field, _parameters.walls.vectorRight, i, j);
}

void LBMovingWallStencil::applyBottomWall ( LBField & field, int i, int j ){
    prepareBoundaries(velocitiesBottom2D, field, _parameters.walls.vectorBottom, i, j);
}

void LBMovingWallStencil::applyTopWall    ( LBField & field, int i, int j ){
    prepareBoundaries(velocitiesTop2D, field, _parameters.walls.vectorTop, i, j);
}


void LBMovingWallStencil::applyLeftWall   ( LBField & field, int i, int j, int k ){
    prepareBoundaries(velocitiesLeft3D, field, _parameters.walls.vectorLeft, i, j, k);
}

void LBMovingWallStencil::applyRightWall  ( LBField & field, int i, int j, int k ){
    prepareBoundaries(velocitiesRight3D, field, _parameters.walls.vectorRight, i, j, k);
}

void LBMovingWallStencil::applyBottomWall ( LBField & field, int i, int j, int k ){
    prepareBoundaries(velocitiesBottom3D, field, _parameters.walls.vectorBottom, i, j, k);
}

void LBMovingWallStencil::applyTopWall    ( LBField & field, int i, int j, int k ){
    prepareBoundaries(velocitiesTop3D, field, _parameters.walls.vectorTop, i, j, k);
}

void LBMovingWallStencil::applyFrontWall  ( LBField & field, int i, int j, int k ){
    prepareBoundaries(velocitiesFront3D, field, _parameters.walls.vectorFront, i, j, k);
}

void LBMovingWallStencil::applyBackWall   ( LBField & field, int i, int j, int k ){
    prepareBoundaries(velocitiesBack3D, field, _parameters.walls.vectorBack, i, j, k);
}
