#include "LBParabolicStencil.h"
#include "LBFunctions.h"
#include <math.h>

LBParabolicStencil::LBParabolicStencil (const Parameters & parameters, FLOAT angle, FLOAT gradRho):
    GlobalBoundaryStencil <LBField> (parameters), _angle(angle), _gradRho(gradRho),
    _cosAngle (cos(angle)), _sinAngle (sin(angle)),

    _speedFactor(0.5 / (parameters.lb.tau - 0.5) * gradRho),

    // Four factors have to be computed. These are trigonometric functions, so it might be easier
    // to just write them here

    _al (gradRho * sin(angle)),
    _ar (gradRho * sin(angle)),
    _ab (gradRho * cos(angle)),
    _at (gradRho * cos(angle)),

    _bl (1.0 - sqrt(2) * 0.5 * gradRho * sin(0.25 * M_PI + angle) * (parameters.geometry.sizeX + 1)),
    _br (1.0 + sqrt(2) * 0.5 * gradRho * cos(0.25 * M_PI + angle) * (parameters.geometry.sizeX + 1)),
    _bb (1.0 - sqrt(2) * 0.5 * gradRho * sin(0.25 * M_PI + angle) * (parameters.geometry.sizeX + 1)),
    _bt (1.0 - sqrt(2) * 0.5 * gradRho * cos(0.25 * M_PI + angle) * (parameters.geometry.sizeX + 1))
{
    _velocity[2] = 0.0;
}


void LBParabolicStencil::applyLeftWall   (LBField & field, int i, int j){}
void LBParabolicStencil::applyRightWall  (LBField & field, int i, int j){}
void LBParabolicStencil::applyBottomWall (LBField & field, int i, int j){}
void LBParabolicStencil::applyTopWall    (LBField & field, int i, int j){}


// Auxiliary function to set the boundaries
void setDistribution (LBField & field, FLOAT tau, FLOAT density, FLOAT zValue, FLOAT cosAngle,
                      FLOAT sinAngle, FLOAT speedFactor, FLOAT plateSeparation,
                      int i, int j, int k) {
    FLOAT velocity[3] = { cosAngle * speedFactor * zValue * (zValue - plateSeparation),
                          sinAngle * speedFactor * zValue * (zValue - plateSeparation),
                          0};

    FLOAT equilibrium[Q], nequilibrium[Q];

    computeEquilibrium (equilibrium, density, velocity);
    computeMinimumNonEquilibrium (nequilibrium, tau, density,
                      0, 0, speedFactor * (2*zValue - plateSeparation) * cosAngle,
                      0, 0, speedFactor * (2*zValue - plateSeparation) * sinAngle,
                      0, 0, 0);

    for (int l = 0; l < Q; l++) {
        // TODO replace 1/tau for something less expensive than a quotient
        field.getFIn() [field.getIndexF(l, i, j, k)] = equilibrium[l] + (1 - 1/tau) * nequilibrium[l];
        field.getFOut()[field.getIndexF(l, i, j, k)] = equilibrium[l] + (1 - 1/tau) * nequilibrium[l];
    }
}


void LBParabolicStencil::applyLeftWall   (LBField & field, int i, int j, int k){
    const FLOAT density = _al * (double)j + _bl;
    const FLOAT zValue = (double)k + 0.5;

    setDistribution(field, _parameters.lb.tau, density, zValue, _cosAngle, _sinAngle, _speedFactor,
                    (double)(_parameters.geometry.sizeZ + 2), i, j, k);
}

void LBParabolicStencil::applyRightWall  (LBField & field, int i, int j, int k){
    const FLOAT density = _ar * (double)j + _br;
    const FLOAT zValue = (double)k + 0.5;

    setDistribution(field, _parameters.lb.tau, density, zValue, _cosAngle, _sinAngle, _speedFactor,
                    (double)(_parameters.geometry.sizeZ + 2), i, j, k);
}

void LBParabolicStencil::applyBottomWall (LBField & field, int i, int j, int k){
    const FLOAT density = _ab * (double)i + _bb;
    const FLOAT zValue = (double)k + 0.5;

    setDistribution(field, _parameters.lb.tau, density, zValue, _cosAngle, _sinAngle, _speedFactor,
                    (double)(_parameters.geometry.sizeZ + 2), i, j, k);
}

void LBParabolicStencil::applyTopWall    (LBField & field, int i, int j, int k){
    const FLOAT density = _at * (double)i + _bt;
    const FLOAT zValue = (double)k + 0.5;

    setDistribution(field, _parameters.lb.tau, density, zValue, _cosAngle, _sinAngle, _speedFactor,
                    (double)(_parameters.geometry.sizeZ + 2), i, j, k);
}

void LBParabolicStencil::applyFrontWall  (LBField & field, int i, int j, int k){
    const FLOAT density = 1 + _gradRho *
        (((double)i + 0.5 - 0.5 * (double)(_parameters.geometry.sizeX + 2)) * _cosAngle +
         ((double)j + 0.5 - 0.5 * (double)(_parameters.geometry.sizeY + 2)) * _sinAngle);
    const FLOAT zValue = (double)k + 0.5;

    setDistribution(field, _parameters.lb.tau, density, zValue, _cosAngle, _sinAngle, _speedFactor,
                    (double)(_parameters.geometry.sizeZ + 2), i, j, k);
}

void LBParabolicStencil::applyBackWall   (LBField & field, int i, int j, int k){
    // Identical to the other wall
    applyFrontWall(field, i, j, k);
}
