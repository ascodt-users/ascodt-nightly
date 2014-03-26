#include "Functions.h"

void setTimeStep(const MaxUStencil & maxUStencil, Parameters & parameters, int dim){
    assertion(dim == 2 || dim == 3);
    FLOAT factor = 1/(parameters.geometry.dx * parameters.geometry.dx) +
                   1/(parameters.geometry.dy * parameters.geometry.dy);
    if (dim == 3) {
        factor += 1/(parameters.geometry.dz * parameters.geometry.dz);
        parameters.timestep.dt = parameters.geometry.dz / maxUStencil.getMaxValues()[2];
    } else {
        parameters.timestep.dt = parameters.flow.Re / 2 / factor;
    }

    parameters.timestep.dt = std::min(parameters.timestep.dt,
                                      std::min(std::min(parameters.flow.Re/(2*factor),
                                      parameters.geometry.dx / maxUStencil.getMaxValues()[0]),
                                      parameters.geometry.dy / maxUStencil.getMaxValues()[1]));
    parameters.timestep.dt *= parameters.timestep.tau;
}
