#include "examples/heat/ImplicitEulerImplementation.h"

examples::heat::ImplicitEulerImplementation::ImplicitEulerImplementation(){

}

examples::heat::ImplicitEulerImplementation::~ImplicitEulerImplementation(){
	std::cout<<"destroy implicit euler"<<std::endl;
}

void examples::heat::ImplicitEulerImplementation::step(
		const int* dims,
		const int dims_len,
		const double dt,
		const double* rhs,
		const int rhs_len,
		const double* stencil,
		const int stencil_len,
		const void* dof){
	double scale_factor=(double)(dims[0]-1)*(dims[1]-1);
	_stencil[0]=-dt*stencil[0]*scale_factor;

	_stencil[1]=-dt*stencil[1]*scale_factor;

	_stencil[2]=1.0-dt*stencil[2]*scale_factor;

	_stencil[3]=-dt*stencil[3]*scale_factor;

	_stencil[4]=-dt*stencil[4]*scale_factor;

	_solver->solve(
			dims,dims_len,
			_stencil,stencil_len,
			rhs,rhs_len,
			dof);

}
