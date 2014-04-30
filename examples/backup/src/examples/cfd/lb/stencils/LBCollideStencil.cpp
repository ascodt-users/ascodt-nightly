#include "LBCollideStencil.h"


LBCollideStencil::LBCollideStencil(const Parameters & parameters):
FieldStencil<LBField>(parameters){

	if (parameters.geometry.dim == 2){
		handleError (1, "There's no implementation for 2D grids.")
	}
}

void LBCollideStencil::apply(LBField & field, int i, int j){
	LBCollideStencil::apply(field, i, j, 0);
}

void LBCollideStencil::apply(LBField & field, int i, int j, int k){

	// The plan is to work with stream and then collide in the timestep. Therefore, the collision
	// is applied to f_out, which contains the already streamed information.
	if(field.getFlags()[field.getIndexCell(i,j,k)]==0){
		field.getPressureAndVelocity(_density, _velocity, i, j, k);

		computeEquilibrium(_equilibrium, _density, _velocity);

		for (int a = 0; a < Q; a++){
			field.getFOut()[field.getIndexF(a, i, j, k)] -=
					_parameters.lb.reciprocalTau *
					(field.getFOut()[field.getIndexF(a, i, j, k)] - _equilibrium[a]);
		}
	}
}
