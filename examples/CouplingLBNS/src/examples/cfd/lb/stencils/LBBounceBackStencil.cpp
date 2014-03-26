#include "LBBounceBackStencil.h"



LBBounceBackStencil::LBBounceBackStencil(const Parameters & parameters):
FieldStencil<LBField>(parameters) {}

void LBBounceBackStencil::apply(LBField & field, int i, int j){
	LBBounceBackStencil::apply(field, i, j, 0);
}

void LBBounceBackStencil::apply(LBField & field, int i, int j, int k){

	// The plan is to work with stream and then collide in the timestep. Therefore, the collision
	// is applied to f_out, which contains the already streamed information.
	if(field.getFlags()[field.getIndexCell(i,j,k)]==(char)(0)){


		for (int a = 0; a < Q; a++){
			if(field.getFlags()[field.getIndexCell(
					i+field.getLatticeVelocities()[a][0],
					j+field.getLatticeVelocities()[a][1],
					k+field.getLatticeVelocities()[a][2])]==1)
				field.getFOut()[field.getIndexF(
						field.getInverse(a),
						i+field.getLatticeVelocities()[a][0],
						j+field.getLatticeVelocities()[a][1],
						k+field.getLatticeVelocities()[a][2])] =
								field.getFOut()[field.getIndexF(
										a,
										i,
										j,
										k)];
		}
	}
}
