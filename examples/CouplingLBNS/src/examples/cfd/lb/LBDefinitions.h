#ifndef _LBDEFINITIONS_H_
#define _LBDEFINITIONS_H_

#include <math.h>
#include "Definitions.h"

#if (not defined (D3Q19)) and (not defined (D3Q15)) and (not defined (D3Q27))
#define D3Q19
#endif

static const FLOAT centerWeight2D = 4./9.;
static const FLOAT faceWeight2D = 1./9.;
static const FLOAT diagonalWeight2D = 1./36.;

static const int Q2D = 9;

static const int latticeVelocities2D[9][3] = {
{1, 1, 0},{1, 0, 0},{1, -1, 0}, {0, -1, 0},
{0, 0, 0},
{0, 1, 0},{-1, 1, 0},{-1, 0, 0},{-1, -1, 0}
};

static const FLOAT latticeWeights2D[9] = {
diagonalWeight2D, faceWeight2D, diagonalWeight2D, faceWeight2D,
centerWeight2D,
faceWeight2D, diagonalWeight2D, faceWeight2D, diagonalWeight2D
};


#ifdef D3Q19
#define Q 19
static const int Q3D = 19;
static const int latticeVelocities3D[19][3] = {
{0,-1,-1},{-1,0,-1},{0,0,-1},{1,0,-1},{0,1,-1},
{-1,-1,0},{0,-1,0},{1,-1,0},{-1,0,0},{0,0,0},
{1,0,0},{-1,1,0},{0,1,0},{1,1,0},{0,-1,1},
{-1,0,1},{0,0,1},{1,0,1},{0,1,1}
};
static const FLOAT latticeWeights3D[19] = {
1./36., 1./36., 1./18., 1./36., 1./36.,
1./36., 1./18., 1./36., 1./18., 1./3.,
1./18., 1./36., 1./18., 1./36., 1./36.,
1./36., 1./18., 1./36., 1./36.
};
#endif

#ifdef D3Q27
#define Q 27
static const int Q3D = 27;
static const int latticeVelocities3D[27][3] = {
{-1, -1, -1}, {0, -1, -1}, {1, -1, -1},
{-1,  0, -1}, {0,  0, -1}, {1,  0, -1},
{-1,  1, -1}, {0,  1, -1}, {1,  1, -1},
{-1, -1,  0}, {0, -1,  0}, {1, -1,  0},
{-1,  0,  0}, {0,  0,  0}, {1,  0,  0},
{-1,  1,  0}, {0,  1,  0}, {1,  1,  0},
{-1, -1,  1}, {0, -1,  1}, {1, -1,  1},
{-1,  0,  1}, {0,  0,  1}, {1,  0,  1},
{-1,  1,  1}, {0,  1,  1}, {1,  1,  1}
};
static const FLOAT latticeWeights3D[27] = {
1./216., 1./54., 1./216.,
1./54., 2./27., 1./54.,
1./216., 1./54., 1./216.,

1./54., 2./27., 1./54.,
2./27., 8./27., 2./27.,
1./54., 2./27., 1./54.,

1./216., 1./54., 1./216.,
1./54., 2./27., 1./54.,
1./216., 1./54., 1./216.
};
#endif

#ifdef D3Q15
#define Q 15
static const int Q3D = 15;
static const int latticeVelocities3D[15][3] = {
{-1, -1, -1}, {1, -1, -1},
{0, 0, -1},
{-1,  1, -1}, {1,  1, -1},

{0, -1, 0},
{-1, 0, 0}, {0, 0, 0}, {1, 0, 0},
{0,  1, 0},

{-1, -1, 1}, {1, -1, 1},
{0, 0, 1},
{-1,  1, 1}, {1,  1, 1}
};
static const FLOAT latticeWeights3D[15] = {
1./72., 1./72.,
1./9.,
1./72., 1./72.,

1./9.,
1./9., 2./9., 1./9.,
1./9.,

1./72., 1./72.,
1./9.,
1./72., 1./72.
};
#endif


static const FLOAT C_S = 1 / 1.73205080756887729352;
static const FLOAT reciprocalC = 1.73205080756887729352;

#endif

