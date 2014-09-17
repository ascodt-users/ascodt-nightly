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
		//field.getPressureAndVelocity(_density, _velocity, i, j, k);
#ifdef D3Q19
// These are parts for the computation of the velocity, but will also be used for computation
// of the pressure to reduce the number of operations. At the end, velocity is found as linear
		// combinations of the distributions with coefficients 1 or -1, so we can add up all the
		// positive and negative parts. Taken from somewhere else in the code.

		const FLOAT x_add = _f[3] + _f[7] + _f[10] + _f[13] + _f[17];
		const FLOAT x_sub = _f[1] + _f[5] + _f[8] + _f[11] + _f[15];

		const FLOAT z_add = _f[14] + _f[15] + _f[16] + _f[17] + _f[18];
		const FLOAT z_sub = _f[0] + _f[1] + _f[2] + _f[3] + _f[4];

		FLOAT y_add = _f[11] + _f[12] + _f[13];
		FLOAT y_sub = _f[5] + _f[6] + _f[7];

		_density = _f[8] + _f[9] + _f[10] + y_add + y_sub + z_add + z_sub;

		y_add += _f[4] + _f[18];
		y_sub += _f[0] + _f[14];

		_velocity[0] = (x_add - x_sub) / _density;
		_velocity[1] = (y_add - y_sub) / _density;
		_velocity[2] = (z_add - z_sub) / _density;
#endif

#if (defined (D3Q15)) or (defined (D3Q27))
		_density = 0.0;
		_velocity[0] = 0.0;
		_velocity[1] = 0.0;
		_velocity[2] = 0.0;
		for (int a = 0; a < Q; a++){
			_density += _f[a];
			_velocity[0] += latticeVelocities3D[a][0] * _f[a];
			_velocity[1] += latticeVelocities3D[a][1] * _f[a];
			_velocity[2] += latticeVelocities3D[a][2] * _f[a];
		}
		_velocity[0] /= _density;
		_velocity[1] /= _density;
		_velocity[2] /= _density;
#endif

		computeEquilibrium(_equilibrium, _density, _velocity);

		for (int a = 0; a < Q; a++){
			field.getFOut()[field.getIndexF(a, i, j, k)] -=
					_parameters.lb.reciprocalTau *
					(field.getFOut()[field.getIndexF(a, i, j, k)] - _equilibrium[a]);
		}
	}
}
