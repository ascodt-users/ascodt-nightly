#ifndef _COUPLING_DEFINITIONS_H_
#define _COUPLING_DEFINITIONS_H_

#include "Definitions.h"

// These are the definitions for the interpolation stencil. Selection is controled by a macro.
// There are three cases, which are depicted as an appendix in the thesis of Pachajoa.
//
// The barycentric basis matrix is the inverse of the construction matrix for the interpolation.
// The stencil matrix contains the points used in the stencil.

#if (not defined(ODDSTENCIL)) and (not defined(THIRDORDERSTENCIL)) and (not defined(DQUADRATICSTENCIL))
#define ODDSTENCIL
#endif

#if defined (ODDSTENCIL)
static const FLOAT barycentricBasis[10][10] =
{{ 1.0 ,  0.0 , -1.5 , -1.5 , -1.0 ,  1.0 ,  1.0 ,  0.5 ,  1.0 ,  0.5 },
 { 0.0 ,  0.0 ,  0.0 ,  0.0 ,  1.0 , -1.0 , -1.0 ,  0.0 ,  0.0 ,  0.0 },
 { 0.0 , -1.0 ,  2.0 ,  0.0 ,  1.0 , -1.0 ,  0.0 , -1.0 , -1.0 ,  0.0 },
 { 0.0 ,  1.0 ,  0.0 ,  0.0 , -1.0 ,  1.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 },
 { 0.0 ,  0.0 , -0.5 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  0.0 },
 { 0.0 , -1.0 ,  0.0 ,  2.0 ,  1.0 ,  0.0 , -1.0 ,  0.0 , -1.0 , -1.0 },
 { 0.0 ,  1.0 ,  0.0 ,  0.0 , -1.0 ,  0.0 ,  1.0 ,  0.0 ,  0.0 ,  0.0 },
 { 0.0 ,  0.5 ,  0.0 ,  0.0 , -0.5 ,  0.0 ,  0.0 ,  0.0 ,  1.0 ,  0.0 },
 { 0.0 , -0.5 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 },
 { 0.0 ,  0.0 ,  0.0 , -0.5 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.5 }};

static const int stencil[10][3] =
{{0,0,0},
 {1,0,0},
 {0,1,0},
 {1,1,0},
 {0,2,0},
 {0,0,1},
 {1,0,1},
 {0,1,1},
 {2,1,1},
 {0,0,2}};

static const int stencilSize = 10;

#elif defined (THIRDORDERSTENCIL)

static const FLOAT barycentricBasis[20][20] =
// As taken from the python script
{ { 1.0 ,  -1.33333333333 ,  -1.33333333333 ,  -1.33333333333 ,  0.25 ,  1.5 ,  1.5 ,  0.25 ,  1.5 ,  0.25 ,  0.0833333333333 ,  0.0833333333333 ,  0.0833333333333 ,  -0.25 ,  -0.25 ,  -0.25 ,  -0.25 ,  -0.25 ,  -0.25 ,  -1.0 },
{ 0.0 ,  0.333333333333 ,  0.333333333333 ,  1.66666666667 ,  -0.5 ,  -1.0 ,  -1.0 ,  -0.5 ,  -1.0 ,  -0.5 ,  0.166666666667 ,  0.166666666667 ,  -0.166666666667 ,  0.5 ,  -0.5 ,  0.5 ,  -0.5 ,  0.5 ,  0.5 ,  1.0 },
{ 0.0 ,  0.333333333333 ,  1.66666666667 ,  0.333333333333 ,  -0.5 ,  -1.0 ,  -1.0 ,  -0.5 ,  -1.0 ,  -0.5 ,  0.166666666667 ,  -0.166666666667 ,  0.166666666667 ,  -0.5 ,  0.5 ,  0.5 ,  0.5 ,  0.5 ,  -0.5 ,  1.0 },
{ 0.0 ,  0.166666666667 ,  -0.166666666667 ,  -0.166666666667 ,  -0.25 ,  0.0 ,  0.0 ,  0.25 ,  0.5 ,  0.25 ,  0.0833333333333 ,  -0.0833333333333 ,  -0.0833333333333 ,  0.25 ,  0.25 ,  -0.25 ,  0.25 ,  -0.25 ,  0.25 ,  -1.0 },
{ 0.0 ,  1.66666666667 ,  0.333333333333 ,  0.333333333333 ,  -0.5 ,  -1.0 ,  -1.0 ,  -0.5 ,  -1.0 ,  -0.5 ,  -0.166666666667 ,  0.166666666667 ,  0.166666666667 ,  0.5 ,  0.5 ,  -0.5 ,  0.5 ,  -0.5 ,  0.5 ,  1.0 },
{ 0.0 ,  -0.166666666667 ,  0.166666666667 ,  -0.166666666667 ,  0.25 ,  0.0 ,  0.5 ,  -0.25 ,  0.0 ,  0.25 ,  -0.0833333333333 ,  0.0833333333333 ,  -0.0833333333333 ,  -0.25 ,  0.25 ,  0.25 ,  0.25 ,  0.25 ,  -0.25 ,  -1.0 },
{ 0.0 ,  -0.166666666667 ,  -0.166666666667 ,  0.166666666667 ,  0.25 ,  0.5 ,  0.0 ,  0.25 ,  0.0 ,  -0.25 ,  -0.0833333333333 ,  -0.0833333333333 ,  0.0833333333333 ,  0.25 ,  -0.25 ,  0.25 ,  -0.25 ,  0.25 ,  0.25 ,  -1.0 },
{ 0.0 ,  -0.333333333333 ,  -0.333333333333 ,  -0.333333333333 ,  0.5 ,  1.0 ,  1.0 ,  0.5 ,  1.0 ,  0.5 ,  -0.166666666667 ,  -0.166666666667 ,  -0.166666666667 ,  -0.5 ,  -0.5 ,  -0.5 ,  -0.5 ,  -0.5 ,  -0.5 ,  1.0 },
{ 0.0 ,  -0.166666666667 ,  0.0 ,  0.0 ,  0.25 ,  -0.25 ,  0.25 ,  0.0 ,  0.0 ,  0.0 ,  -0.0833333333333 ,  0.0 ,  0.0 ,  0.25 ,  -0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 },
{ 0.0 ,  -0.166666666667 ,  0.0 ,  0.0 ,  0.25 ,  0.25 ,  -0.25 ,  0.0 ,  0.0 ,  0.0 ,  -0.0833333333333 ,  0.0 ,  0.0 ,  -0.25 ,  0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 },
{ 0.0 ,  0.166666666667 ,  0.0 ,  0.0 ,  -0.25 ,  -0.25 ,  -0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0833333333333 ,  0.0 ,  0.0 ,  0.25 ,  0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 },
{ 0.0 ,  -0.333333333333 ,  0.0 ,  0.0 ,  0.25 ,  0.25 ,  0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0833333333333 ,  0.0 ,  0.0 ,  -0.25 ,  -0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 },
{ 0.0 ,  0.0 ,  -0.166666666667 ,  0.0 ,  0.0 ,  0.25 ,  0.0 ,  0.25 ,  -0.25 ,  0.0 ,  0.0 ,  -0.0833333333333 ,  0.0 ,  0.0 ,  0.0 ,  -0.25 ,  0.25 ,  0.0 ,  0.0 ,  0.0 },
{ 0.0 ,  0.0 ,  -0.166666666667 ,  0.0 ,  0.0 ,  -0.25 ,  0.0 ,  0.25 ,  0.25 ,  0.0 ,  0.0 ,  -0.0833333333333 ,  0.0 ,  0.0 ,  0.0 ,  0.25 ,  -0.25 ,  0.0 ,  0.0 ,  0.0 },
{ 0.0 ,  0.0 ,  -0.333333333333 ,  0.0 ,  0.0 ,  0.25 ,  0.0 ,  0.25 ,  0.25 ,  0.0 ,  0.0 ,  0.0833333333333 ,  0.0 ,  0.0 ,  0.0 ,  -0.25 ,  -0.25 ,  0.0 ,  0.0 ,  0.0 },
{ 0.0 ,  0.0 ,  0.166666666667 ,  0.0 ,  0.0 ,  -0.25 ,  0.0 ,  -0.25 ,  -0.25 ,  0.0 ,  0.0 ,  0.0833333333333 ,  0.0 ,  0.0 ,  0.0 ,  0.25 ,  0.25 ,  0.0 ,  0.0 ,  0.0 },
{ 0.0 ,  0.0 ,  0.0 ,  -0.166666666667 ,  0.0 ,  0.0 ,  -0.25 ,  0.0 ,  0.25 ,  0.25 ,  0.0 ,  0.0 ,  -0.0833333333333 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.25 ,  -0.25 ,  0.0 },
{ 0.0 ,  0.0 ,  0.0 ,  -0.166666666667 ,  0.0 ,  0.0 ,  0.25 ,  0.0 ,  -0.25 ,  0.25 ,  0.0 ,  0.0 ,  -0.0833333333333 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -0.25 ,  0.25 ,  0.0 },
{ 0.0 ,  0.0 ,  0.0 ,  -0.333333333333 ,  0.0 ,  0.0 ,  0.25 ,  0.0 ,  0.25 ,  0.25 ,  0.0 ,  0.0 ,  0.0833333333333 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -0.25 ,  -0.25 ,  0.0 },
{ 0.0 ,  0.0 ,  0.0 ,  0.166666666667 ,  0.0 ,  0.0 ,  -0.25 ,  0.0 ,  -0.25 ,  -0.25 ,  0.0 ,  0.0 ,  0.0833333333333 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.25 ,  0.25 ,  0.0 } };

static const int stencil[20][3] =
{{0,0,0},
 {0,0,1},
 {0,1,0},
 {0,1,1},
 {1,0,0},
 {1,0,1},
 {1,1,0},
 {1,1,1},
 {-1,1,0},
 {-1,0,1},
 {2,1,1},
 {2,0,0},
 {0,-1,1},
 {1,-1,0},
 {0,2,0},
 {1,2,1},
 {1,0,-1},
 {0,1,-1},
 {0,0,2},
 {1,1,2}};

static const int stencilSize = 20;

#elif defined(DQUADRATICSTENCIL)

static const FLOAT barycentricBasis[27][27] =

{ { 1.0 ,  -1.5 ,  -1.5 ,  -1.5 ,  0.5 ,  2.25 ,  2.25 ,  0.5 ,  2.25 ,  0.5 ,  -0.75 ,  -0.75 ,  -0.75 ,  -0.75 ,  -0.75 ,  -0.75 ,  -3.375 ,  0.25 ,  1.125 ,  0.25 ,  1.125 ,  1.125 ,  0.25 ,  -0.375 ,  -0.375 ,  -0.375 ,  0.125 },
{ 0.0 ,  0.0 ,  0.0 ,  2.0 ,  0.0 ,  0.0 ,  -3.0 ,  0.0 ,  -3.0 ,  -1.0 ,  0.0 ,  1.5 ,  0.0 ,  1.5 ,  1.0 ,  1.0 ,  4.5 ,  0.0 ,  -1.5 ,  -0.5 ,  -1.5 ,  -2.25 ,  -0.5 ,  0.75 ,  0.5 ,  0.75 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  -0.5 ,  0.0 ,  0.0 ,  0.75 ,  0.0 ,  0.75 ,  0.5 ,  0.0 ,  -0.75 ,  0.0 ,  -0.75 ,  -0.25 ,  -0.25 ,  -1.125 ,  0.0 ,  0.375 ,  0.25 ,  0.375 ,  1.125 ,  0.25 ,  -0.375 ,  -0.125 ,  -0.375 ,  0.125 },
{ 0.0 ,  0.0 ,  2.0 ,  0.0 ,  0.0 ,  -3.0 ,  0.0 ,  -1.0 ,  -3.0 ,  0.0 ,  1.5 ,  0.0 ,  1.0 ,  1.0 ,  0.0 ,  1.5 ,  4.5 ,  -0.5 ,  -1.5 ,  0.0 ,  -2.25 ,  -1.5 ,  -0.5 ,  0.5 ,  0.75 ,  0.75 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  4.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -2.0 ,  0.0 ,  -2.0 ,  -6.0 ,  0.0 ,  2.0 ,  0.0 ,  3.0 ,  3.0 ,  1.0 ,  -1.0 ,  -1.0 ,  -1.5 ,  0.5 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -1.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  1.0 ,  0.0 ,  0.5 ,  1.5 ,  0.0 ,  -0.5 ,  0.0 ,  -0.75 ,  -1.5 ,  -0.5 ,  0.5 ,  0.25 ,  0.75 ,  -0.25 },
{ 0.0 ,  0.0 ,  -0.5 ,  0.0 ,  0.0 ,  0.75 ,  0.0 ,  0.5 ,  0.75 ,  0.0 ,  -0.75 ,  0.0 ,  -0.25 ,  -0.25 ,  0.0 ,  -0.75 ,  -1.125 ,  0.25 ,  0.375 ,  0.0 ,  1.125 ,  0.375 ,  0.25 ,  -0.125 ,  -0.375 ,  -0.375 ,  0.125 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -1.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  1.0 ,  1.5 ,  0.0 ,  -0.5 ,  0.0 ,  -1.5 ,  -0.75 ,  -0.5 ,  0.25 ,  0.5 ,  0.75 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -0.25 ,  0.0 ,  -0.25 ,  -0.375 ,  0.0 ,  0.125 ,  0.0 ,  0.375 ,  0.375 ,  0.25 ,  -0.125 ,  -0.125 ,  -0.375 ,  0.125 },
{ 0.0 ,  2.0 ,  0.0 ,  0.0 ,  -1.0 ,  -3.0 ,  -3.0 ,  0.0 ,  0.0 ,  0.0 ,  1.0 ,  1.0 ,  1.5 ,  0.0 ,  1.5 ,  0.0 ,  4.5 ,  -0.5 ,  -2.25 ,  -0.5 ,  -1.5 ,  -1.5 ,  0.0 ,  0.75 ,  0.75 ,  0.5 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  4.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -2.0 ,  0.0 ,  0.0 ,  -2.0 ,  0.0 ,  -6.0 ,  0.0 ,  3.0 ,  1.0 ,  2.0 ,  3.0 ,  0.0 ,  -1.5 ,  -1.0 ,  -1.0 ,  0.5 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -1.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  1.0 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  1.5 ,  0.0 ,  -0.75 ,  -0.5 ,  -0.5 ,  -1.5 ,  0.0 ,  0.75 ,  0.25 ,  0.5 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  4.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -2.0 ,  0.0 ,  -2.0 ,  0.0 ,  0.0 ,  0.0 ,  -6.0 ,  1.0 ,  3.0 ,  0.0 ,  3.0 ,  2.0 ,  0.0 ,  -1.0 ,  -1.5 ,  -1.0 ,  0.5 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  8.0 ,  0.0 ,  -4.0 ,  0.0 ,  -4.0 ,  -4.0 ,  0.0 ,  2.0 ,  2.0 ,  2.0 ,  -1.0 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -2.0 ,  0.0 ,  1.0 ,  0.0 ,  1.0 ,  2.0 ,  0.0 ,  -1.0 ,  -0.5 ,  -1.0 ,  0.5 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -1.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  1.0 ,  0.0 ,  0.5 ,  0.0 ,  0.0 ,  0.0 ,  1.5 ,  -0.5 ,  -0.75 ,  0.0 ,  -1.5 ,  -0.5 ,  0.0 ,  0.25 ,  0.75 ,  0.5 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -2.0 ,  0.0 ,  1.0 ,  0.0 ,  2.0 ,  1.0 ,  0.0 ,  -0.5 ,  -1.0 ,  -1.0 ,  0.5 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  -0.25 ,  0.0 ,  -0.5 ,  -0.5 ,  0.0 ,  0.25 ,  0.25 ,  0.5 ,  -0.25 },
{ 0.0 ,  -0.5 ,  0.0 ,  0.0 ,  0.5 ,  0.75 ,  0.75 ,  0.0 ,  0.0 ,  0.0 ,  -0.25 ,  -0.25 ,  -0.75 ,  0.0 ,  -0.75 ,  0.0 ,  -1.125 ,  0.25 ,  1.125 ,  0.25 ,  0.375 ,  0.375 ,  0.0 ,  -0.375 ,  -0.375 ,  -0.125 ,  0.125 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -1.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  0.0 ,  1.0 ,  0.0 ,  1.5 ,  0.0 ,  -1.5 ,  -0.5 ,  -0.5 ,  -0.75 ,  0.0 ,  0.75 ,  0.5 ,  0.25 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -0.25 ,  0.0 ,  0.0 ,  -0.25 ,  0.0 ,  -0.375 ,  0.0 ,  0.375 ,  0.25 ,  0.125 ,  0.375 ,  0.0 ,  -0.375 ,  -0.125 ,  -0.125 ,  0.125 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -1.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  1.0 ,  0.0 ,  0.0 ,  0.0 ,  1.5 ,  -0.5 ,  -1.5 ,  0.0 ,  -0.75 ,  -0.5 ,  0.0 ,  0.5 ,  0.75 ,  0.25 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -2.0 ,  0.0 ,  2.0 ,  0.0 ,  1.0 ,  1.0 ,  0.0 ,  -1.0 ,  -1.0 ,  -0.5 ,  0.5 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  -0.5 ,  0.0 ,  -0.25 ,  -0.5 ,  0.0 ,  0.5 ,  0.25 ,  0.25 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.25 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -0.25 ,  0.0 ,  -0.25 ,  0.0 ,  0.0 ,  0.0 ,  -0.375 ,  0.25 ,  0.375 ,  0.0 ,  0.375 ,  0.125 ,  0.0 ,  -0.125 ,  -0.375 ,  -0.125 ,  0.125 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.5 ,  0.0 ,  -0.5 ,  0.0 ,  -0.5 ,  -0.25 ,  0.0 ,  0.25 ,  0.5 ,  0.25 ,  -0.25 },
{ 0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  0.0 ,  -0.125 ,  0.0 ,  0.125 ,  0.0 ,  0.125 ,  0.125 ,  0.0 ,  -0.125 ,  -0.125 ,  -0.125 ,  0.125 } };

static const int stencil[27][3] =
{{0,0,0},
 {0,0,1},
 {0,0,2},
 {0,1,0},
 {0,1,1},
 {0,1,2},
 {0,2,0},
 {0,2,1},
 {0,2,2},
 {1,0,0},
 {1,0,1},
 {1,0,2},
 {1,1,0},
 {1,1,1},
 {1,1,2},
 {1,2,0},
 {1,2,1},
 {1,2,2},
 {2,0,0},
 {2,0,1},
 {2,0,2},
 {2,1,0},
 {2,1,1},
 {2,1,2},
 {2,2,0},
 {2,2,1},
 {2,2,2}};

static const int stencilSize = 27;

#endif

#endif