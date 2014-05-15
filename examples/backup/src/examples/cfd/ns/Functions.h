#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <algorithm>
#include "stencils/MaxUStencil.h"

/** Sets the timestep.
 *
 * A function that sets the timestep in the parameters.
 * @param maxUStencil Maximal speed stencil for the convection stability condition.
 * @param parameters Parameters, containing the Reynolds number for diffusion stability.\\
 * Also stores the resulting timestep.
 */
void setTimeStep(const MaxUStencil & maxUStencil, Parameters & parameters, int dim);

#endif
