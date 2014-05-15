#include "LBFunctions.h"
#include "../LBDefinitions.h"

static const FLOAT * const weights = latticeWeights3D;

/** In case that blas is not available, like now. Only for square matrices */
static void matrix_vector(const FLOAT matrix[][6], const FLOAT * const vector,
                          FLOAT * const result, int rows, int columns){
    for (int i = 0; i < rows; i++){
        result[i] = 0;
        for (int j = 0; j < columns; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

// Matrix for approximate squared Knudsen norm

#ifdef D3Q19
static const FLOAT inverseE[100] =
{17.5135135135135016, 0., 0., 0., -11.6756756756756701, 0., -11.6756756756756701, 0., 0., -11.6756756756756701,
 0., 162., 0., 0., 0., 0., 0., 0., 0., 0.,
 0., 0., 162., 0., 0., 0., 0., 0., 0., 0.,
 0., 0., 0., 162., 0., 0., 0., 0., 0., 0.,
 -11.6756756756756701, 0., 0., 0., 187.7837837837838038, 0., -28.2162162162162247, 0., 0., -28.2162162162162247,
 0., 0., 0., 0., 0., 648., 0., 0., 0., 0.,
 -11.6756756756756683, 0., 0., 0., -28.2162162162162211, 0., 187.7837837837838038, 0., 0., -28.2162162162162282,
  0., 0., 0., 0., 0., 0., 0., 648., 0., 0.,
  0., 0., 0., 0., 0., 0., 0., 0., 648., 0.,
  -11.6756756756756701, 0., 0., 0., -28.2162162162162282, 0., -28.2162162162162318, 0., 0., 187.7837837837838038};

static const int A[10][19] =
{{ 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
 { 0, -1,  0,  1,  0, -1,  0,  1, -1,  0,  1, -1,  0,  1,  0, -1,  0,  1,  0},
 {-1,  0,  0,  0,  1, -1, -1, -1,  0,  0,  0,  1,  1,  1, -1,  0,  0,  0,  1},
 {-1, -1, -1, -1, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1},
 { 0,  1,  0,  1,  0,  1,  0,  1,  1,  0,  1,  1,  0,  1,  0,  1,  0,  1,  0},
 { 0,  0,  0,  0,  0,  1,  0, -1,  0,  0,  0, -1,  0,  1,  0,  0,  0,  0,  0},
 { 1,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  1,  1,  1,  1,  0,  0,  0,  1},
 { 0,  1,  0, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  0,  1,  0},
 { 1,  0,  0,  0, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1,  0,  0,  0,  1},
 { 1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1}};

static const FLOAT B[19][6] =
{{-0.0262762762762763,  0.  ,  0.0570570570570571,  0.  ,  0.25,  0.0570570570570571},
 { 0.0570570570570571,  0.  , -0.0262762762762763,  0.25,  0.  ,  0.0570570570570571},
 {-0.0615615615615616,  0.  , -0.0615615615615616,  0.  ,  0.  ,  0.2717717717717718},
 { 0.0570570570570571,  0.  , -0.0262762762762763, -0.25,  0.  ,  0.0570570570570571},
 {-0.0262762762762763,  0.  ,  0.0570570570570571,  0.  , -0.25,  0.0570570570570571},
 { 0.0570570570570571,  0.25,  0.0570570570570571,  0.  ,  0.  , -0.0262762762762763},
 {-0.0615615615615616,  0.  ,  0.2717717717717718,  0.  ,  0.  , -0.0615615615615616},
 { 0.0570570570570571, -0.25,  0.0570570570570571,  0.  ,  0.  , -0.0262762762762763},
 { 0.2717717717717718,  0.  , -0.0615615615615616,  0.  ,  0.  , -0.0615615615615616},
 {-0.6486486486486484,  0.  , -0.6486486486486484,  0.  ,  0.  , -0.6486486486486484},
 { 0.2717717717717718,  0.  , -0.0615615615615616,  0.  ,  0.  , -0.0615615615615616},
 { 0.0570570570570571, -0.25,  0.0570570570570571,  0.  ,  0.  , -0.0262762762762763},
 {-0.0615615615615616,  0.  ,  0.2717717717717718,  0.  ,  0.  , -0.0615615615615616},
 { 0.0570570570570571,  0.25,  0.0570570570570571,  0.  ,  0.  , -0.0262762762762763},
 {-0.0262762762762763,  0.  ,  0.0570570570570571,  0.  , -0.25,  0.0570570570570571},
 { 0.0570570570570571,  0.  , -0.0262762762762763, -0.25,  0.  ,  0.0570570570570571},
 {-0.0615615615615616,  0.  , -0.0615615615615616,  0.  ,  0.  ,  0.2717717717717718},
 { 0.0570570570570571,  0.  , -0.0262762762762763,  0.25,  0.  ,  0.0570570570570571},
 {-0.0262762762762763,  0.  ,  0.0570570570570571,  0.  ,  0.25,  0.0570570570570571}};

#elif defined(D3Q27)
static const FLOAT B[27][6] = {
{ 0.00154320987654 ,   0.0138888888889 ,  0.00154320987654 ,  0.0138888888889 ,  0.0138888888889 ,  0.00154320987654 },
{ -0.00308641975309 ,  0.0 ,              0.0246913580247 ,   0.0 ,              0.222222222222 ,   0.0246913580247 },
{ 0.00154320987654 ,  -0.0138888888889 ,  0.00154320987654 , -0.0138888888889 ,  0.0138888888889 ,  0.00154320987654 },
{ 0.0246913580247 ,    0.0 ,             -0.00308641975309 ,  0.222222222222 ,   0.0 ,              0.0246913580247 },
{ -0.0493827160494 ,   0.0 ,             -0.0493827160494 ,   0.0 ,              0.0 ,              0.395061728395 },
{ 0.0246913580247 ,    0.0 ,             -0.00308641975309 , -0.222222222222 ,   0.0 ,              0.0246913580247 },
{ 0.00154320987654 ,  -0.0138888888889 ,  0.00154320987654 ,  0.0138888888889 , -0.0138888888889 ,  0.00154320987654 },
{ -0.00308641975309 ,  0.0 ,              0.0246913580247 ,   0.0 ,             -0.222222222222 ,   0.0246913580247 },
{ 0.00154320987654 ,   0.0138888888889 ,  0.00154320987654 , -0.0138888888889 , -0.0138888888889 ,  0.00154320987654 },
{ 0.0246913580247 ,    0.222222222222 ,   0.0246913580247 ,  0.0 ,               0.0 ,             -0.00308641975309 },
{ -0.0493827160494 ,   0.0 ,              0.395061728395 ,   0.0 ,               0.0 ,             -0.0493827160494 },
{ 0.0246913580247 ,   -0.222222222222 ,   0.0246913580247 ,  0.0 ,               0.0 ,             -0.00308641975309 },
{ 0.395061728395 ,     0.0 ,             -0.0493827160494 ,  0.0 ,               0.0 ,             -0.0493827160494 },
{ -0.79012345679 ,     0.0 ,             -0.79012345679 ,    0.0 ,               0.0 ,             -0.79012345679 },
{ 0.395061728395 ,     0.0 ,             -0.0493827160494 ,  0.0 ,               0.0 ,             -0.0493827160494 },
{ 0.0246913580247 ,   -0.222222222222 ,   0.0246913580247 ,  0.0 ,               0.0 ,             -0.00308641975309 },
{ -0.0493827160494 ,   0.0 ,              0.395061728395 ,   0.0 ,               0.0 ,             -0.0493827160494 },
{ 0.0246913580247 ,    0.222222222222 ,   0.0246913580247 ,  0.0 ,               0.0 ,             -0.00308641975309 },
{ 0.00154320987654 ,   0.0138888888889 ,  0.00154320987654 ,-0.0138888888889 ,  -0.0138888888889 ,  0.00154320987654 },
{ -0.00308641975309 ,  0.0 ,              0.0246913580247 ,  0.0 ,              -0.222222222222 ,   0.0246913580247 },
{ 0.00154320987654 ,  -0.0138888888889 ,  0.00154320987654 , 0.0138888888889 ,  -0.0138888888889 ,  0.00154320987654 },
{ 0.0246913580247 ,    0.0 ,             -0.00308641975309 ,-0.222222222222 ,    0.0 ,              0.0246913580247 },
{ -0.0493827160494 ,   0.0 ,             -0.0493827160494 ,  0.0 ,               0.0 ,              0.395061728395 },
{ 0.0246913580247 ,    0.0 ,             -0.00308641975309 , 0.222222222222 ,    0.0 ,              0.0246913580247 },
{ 0.00154320987654 ,  -0.0138888888889 ,  0.00154320987654 ,-0.0138888888889 ,   0.0138888888889 ,  0.00154320987654 },
{ -0.00308641975309 ,  0.0 ,              0.0246913580247 ,  0.0 ,               0.222222222222 ,   0.0246913580247 },
{ 0.00154320987654 ,   0.0138888888889 ,  0.00154320987654 , 0.0138888888889 ,   0.0138888888889 ,  0.00154320987654 }};

#elif defined (D3Q15)
static const FLOAT B[15][6] = {
{ 0.0119047619048 ,  0.125 ,  0.0119047619048 ,  0.125 ,  0.125 ,  0.0119047619048 },
{ 0.0119047619048 ,  -0.125 ,  0.0119047619048 ,  -0.125 ,  0.125 ,  0.0119047619048 },
{ -0.047619047619 ,  0.0 ,  -0.047619047619 ,  0.0 ,  0.0 ,  0.452380952381 },
{ 0.0119047619048 ,  -0.125 ,  0.0119047619048 ,  0.125 ,  -0.125 ,  0.0119047619048 },
{ 0.0119047619048 ,  0.125 ,  0.0119047619048 ,  -0.125 ,  -0.125 ,  0.0119047619048 },
{ -0.047619047619 ,  0.0 ,  0.452380952381 ,  0.0 ,  0.0 ,  -0.047619047619 },
{ 0.452380952381 ,  0.0 ,  -0.047619047619 ,  0.0 ,  0.0 ,  -0.047619047619 },
{ -0.809523809524 ,  0.0 ,  -0.809523809524 ,  0.0 ,  0.0 ,  -0.809523809524 },
{ 0.452380952381 ,  0.0 ,  -0.047619047619 ,  0.0 ,  0.0 ,  -0.047619047619 },
{ -0.047619047619 ,  0.0 ,  0.452380952381 ,  0.0 ,  0.0 ,  -0.047619047619 },
{ 0.0119047619048 ,  0.125 ,  0.0119047619048 ,  -0.125 ,  -0.125 ,  0.0119047619048 },
{ 0.0119047619048 ,  -0.125 ,  0.0119047619048 ,  0.125 ,  -0.125 ,  0.0119047619048 },
{ -0.047619047619 ,  0.0 ,  -0.047619047619 ,  0.0 ,  0.0 ,  0.452380952381 },
{ 0.0119047619048 ,  -0.125 ,  0.0119047619048 ,  -0.125 ,  0.125 ,  0.0119047619048 },
{ 0.0119047619048 ,  0.125 ,  0.0119047619048 ,  0.125 ,  0.125 ,  0.0119047619048 }
};

#endif

/*
 * The equation for the non equilibrium part solves 10 restrictions, these are ordered as follows:
 *
 * change of density
 * change of momentum, x, y and z
 * crossed components: xx, xy, yy, xz, yz, zz
 *
 * The right hand side is constructed following this order
 */
void computeMinimumNonEquilibrium (FLOAT * const fneq, FLOAT tau, FLOAT density,
                                   FLOAT dudx, FLOAT dudy, FLOAT dudz,
                                   FLOAT dvdx, FLOAT dvdy, FLOAT dvdz,
                                   FLOAT dwdx, FLOAT dwdy, FLOAT dwdz){
    FLOAT rhs[6];

    // Density added according to results of Latt dissertation.
    const FLOAT factor = -tau * density / 3;

    rhs[0] = 2. * factor * dudx;
    rhs[1] = factor * (dudy + dvdx);
    rhs[2] = 2. * factor * dvdy;
    rhs[3] = factor * (dudz + dwdx);
    rhs[4] = factor * (dvdz + dwdy);
    rhs[5] = 2. * factor * dwdz;

    matrix_vector (B, rhs, fneq, Q, 6);
}

static const FLOAT factor1 = reciprocalC * reciprocalC;
static const FLOAT factor2 = 0.5 * factor1 * factor1;
static const FLOAT factor3 = 0.5 * factor1;

void computeEquilibrium(FLOAT * const equilibrium, FLOAT density, const FLOAT * const velocity){

    FLOAT product;
    const FLOAT velocityNormFactor = factor3 * (velocity[0] * velocity[0] + velocity[1] * velocity[1] +
                       velocity[2] * velocity[2]);

#ifdef D3Q19
    // Center component
    equilibrium[9] = weights[9] * density * (1.0 - velocityNormFactor);

    // the rest
    product = velocity[1] + velocity[2];
    equilibrium[18] = weights[0] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[0] = weights[0] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);

    product = velocity[0] + velocity[2];
    equilibrium[17] = weights[1] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[1] = weights[1] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);

    product = velocity[2];
    equilibrium[16] = weights[2] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[2] = weights[2] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);

    product = velocity[2] - velocity[0];
    equilibrium[15] = weights[3] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[3] = weights[3] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);

    product = velocity[2] - velocity[1];
    equilibrium[14] = weights[4] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[4] = weights[4] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);

    product = velocity[0] + velocity[1];
    equilibrium[13] = weights[5] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[5] = weights[5] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);

    product = velocity[1];
    equilibrium[12] = weights[6] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[6] = weights[6] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);

    product = velocity[1] - velocity[0];
    equilibrium[11] = weights[7] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[7] = weights[7] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);

    product = velocity[0];
    equilibrium[10] = weights[8] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    equilibrium[8] = weights[8] * density * (1.0 - factor1 * product + factor2 * product * product - velocityNormFactor);
#endif

#if (defined (D3Q15)) or (defined (D3Q27))
    for (int l = 0; l < Q; l++){
        product = latticeVelocities3D[l][0] * velocity[0] +
                  latticeVelocities3D[l][1] * velocity[1] +
                  latticeVelocities3D[l][2] * velocity[2];
        equilibrium[l] = weights[l] * density * (1.0 + factor1 * product + factor2 * product * product - velocityNormFactor);
    }
#endif
}

