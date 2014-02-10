#include "examples/heat/MeshImplementation.h"

examples::heat::MeshImplementation::MeshImplementation(){
	_data = NULL;
}

examples::heat::MeshImplementation::~MeshImplementation(){
	if(_data){
		delete []_data;
		_data = NULL;
	}
}

void examples::heat::MeshImplementation::allocate(const int* dim, const int dim_len){
    _dims[0] = dim[0];
    _dims[1] = dim[1];

	_data = new double [dim[0]*dim[1]];
	for(int i=0;i<dim[0]*dim[1];i++)
		_data[i]=0.0;
	for(int i=1;i<dim[1]-1;i++)
		for(int j=1;j<dim[0]-1;j++)
			_data[i*dim[0]+j]=1.0;
}
void examples::heat::MeshImplementation::copyData(double* data, const int data_len){
    for(int i=0;i<data_len;i++)
    	data[i]=_data[i];
}
void examples::heat::MeshImplementation::getData(void*& handle){
	handle=_data;
}
