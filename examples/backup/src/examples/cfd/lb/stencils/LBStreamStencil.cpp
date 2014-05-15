#include "LBStreamStencil.h"

LBStreamStencil::LBStreamStencil(const Parameters & parameters):
    FieldStencil<LBField> (parameters){}

void LBStreamStencil::apply(LBField & field, int i, int j){
    // This could be a little faster is the code is just copied here.
    LBStreamStencil::apply(field, i, j, 0);
}

void LBStreamStencil::apply(LBField & field, int i, int j, int k){
	if(field.getFlags()[field.getIndexCell(i,j,k)]==0)
	for (int a = 0; a < Q; a++){
        // Look at a direction and copy the density of the opposite direction to the corresponding
        // local place
        field.getFOut()[field.getIndexF(field.getInverse(a), i, j, k)] =
            field.getFIn()[field.getIndexF(field.getInverse(a),
                                           i+field.getLatticeVelocities()[a][0],
                                           j+field.getLatticeVelocities()[a][1],
                                           k+field.getLatticeVelocities()[a][2])];
    }
}
