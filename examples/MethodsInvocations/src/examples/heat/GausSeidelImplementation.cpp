#include "examples/heat/GausSeidelImplementation.h"
#include <math.h>
examples::heat::GausSeidelImplementation::GausSeidelImplementation(){
	_precision=0.000006;
	_iterations=20000;
}

examples::heat::GausSeidelImplementation::~GausSeidelImplementation(){

}

void examples::heat::GausSeidelImplementation::setup(const double precision,const int iterations){
     // @todo Insert your code here
	_precision=precision;
	_iterations=iterations;
}
void examples::heat::GausSeidelImplementation::solve(
		const int* dims, const int dims_len,
		const double* stencil, const int stencil_len,
		const double* rhs, const int rhs_len,
		const void* dof_handle){
    double residual = 2000.0;
	double temp=0.0;
	int index=0;
	int index_left=0;
	int index_right=0;
	int index_bottom=0;
	int index_top=0;
	double* dof= (double*)dof_handle;
	_iterations=0;
	while(residual>_precision){
		_iterations++;
		residual=0.0;
		for(int i=1;i<dims[1]-1;i++)
			for(int j=1;j<dims[0]-1;j++){
				index = i*(dims[0])+j;
				index_left = i*(dims[0])+j-1;
				index_right = i*(dims[0])+j+1;
				index_bottom = (i-1)*(dims[0])+j;
				index_top= (i+1)*(dims[0])+j;
				dof[index]=(rhs[index]-stencil[1]*dof[index_bottom]
				                      -stencil[3]*dof[index_top]
				                      -stencil[0]*dof[index_left]
				                      -stencil[4]*dof[index_right])/stencil[2];
			}

		for(int i=1;i<dims[1]-1;i++)
					for(int j=1;j<dims[0]-1;j++){
						index = i*(dims[0])+j;
						index_left = i*(dims[0])+j-1;
						index_right = i*(dims[0])+j+1;
						index_bottom = (i-1)*(dims[0])+j;
						index_top = (i+1)*(dims[0])+j;

						temp= (rhs[index]
											  -stencil[2]*dof[index]
						                      -stencil[1]*dof[index_bottom]
						                      -stencil[3]*dof[index_top]
						                      -stencil[0]*dof[index_left]
						                      -stencil[4]*dof[index_right]);
						residual += (temp*temp);
					}
		residual = sqrt(residual/(((double)dims[0]-2.0)*((double)dims[1]-2.0)));

	}
}
