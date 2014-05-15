#ifndef _LB_FUNCTIONS_H_
#define _LB_FUNCTIONS_H_

#include "Definitions.h"

void computeMinimumNonEquilibrium (FLOAT * const fneq, FLOAT tau, FLOAT desity,
                                   FLOAT dudx, FLOAT dudy, FLOAT dudz,
                                   FLOAT dvdx, FLOAT dvdy, FLOAT dvdz,
                                   FLOAT dwdx, FLOAT dwdy, FLOAT dwdz);

void computeEquilibrium(FLOAT * const equilibrium, FLOAT density, const FLOAT * const velocity);

#endif
