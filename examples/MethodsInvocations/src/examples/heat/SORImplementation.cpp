#include "examples/heat/SORImplementation.h"
#include <math.h>
examples::heat::SORImplementation::SORImplementation(){
	std::cout<<"SOR created"<<std::endl;
		_precision=0.000006;
		_iterations=20000;

}

examples::heat::SORImplementation::~SORImplementation(){

}

void examples::heat::SORImplementation::setup(const double precision,const int iterations){
     // @todo Insert your code here
}
void examples::heat::SORImplementation::solve(const int* dims, const int dims_len,const double* stencil, const int stencil_len,const double* rhs, const int rhs_len,const void* dof_handle){
	double* dof= (double*)dof_handle;
	std::cout<<"solving LSE SOR:"<<dof[0]<<","<<dof[1]<<","<<dof[2]<<std::endl;
		/*double w=1.1;
		double residual = 20000.0;
		double temp=0.0;
		int index=0;
		int index_left=0;
		int index_right=0;
		int index_bottom=0;
		int index_top=0;
		double* dof= (double*)dof_handle;

		while(residual>_precision){
			residual=0.0;
			for(int i=1;i<dims[1]-1;i++)
				for(int j=1;j<dims[0]-1;j++){
					index = i*(dims[0])+j;
					index_left = i*(dims[0])+j-1;
					index_right = i*(dims[0])+j+1;
					index_bottom = (i-1)*(dims[0])+j;
					index_top= (i+1)*(dims[0])+j;
					dof[index]=(1.0-w)*rhs[index]+w*(rhs[index]-stencil[1]*dof[index_bottom]
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
		}*/
		//std::cout<<"res:"<<residual<<std::endl;
	}
