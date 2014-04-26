#include "LBParallelManager.h"
#include <iostream>

int max( int a, int b)
{
    if( a > b ) return a;
    return b;
}
LBParallelManager::LBParallelManager(LBField & flowField, const Parameters & parameters):

    ParallelManager<LBField> (flowField, parameters),

    _extractPdfsStencil(parameters, _leftBufferOut, _rightBufferOut, _bottomBufferOut,
                                     _topBufferOut, _frontBufferOut, _backBufferOut),
    _injectPdfsStencil(parameters, _leftBufferIn, _rightBufferIn, _bottomBufferIn,
                                     _topBufferIn, _frontBufferIn, _backBufferIn),

    _extractPdfsIteratorX(_flowField, parameters, _extractPdfsStencil, 1,-1,1,-1,1,-1),
    _extractPdfsIteratorY(_flowField, parameters, _extractPdfsStencil, 0, 0,1,-1,1,-1),
    _extractPdfsIteratorZ(_flowField, parameters, _extractPdfsStencil, 0, 0,0,0,1,-1),
	_injectPdfsIteratorX(_flowField, parameters, _injectPdfsStencil, 0, 0,1,-1,1,-1),
	_injectPdfsIteratorY(_flowField, parameters, _injectPdfsStencil, 0, 0,0,0,1,-1),
	_injectPdfsIteratorZ(_flowField, parameters, _injectPdfsStencil, 0, 0,0,0,0,0)

{

    // Allocate buffers and set number of pressure values
    if (flowField.getDim() == 2){
//  TODO
//        _bufferSize[0] = 2 * (flowField.getNy() + 3); // Allocate space for all values
//        _bufferSize[1] = 2 * (flowField.getNx() + 3);
//
//
//        _leftBufferIn  = new FLOAT[_bufferSize[0]];
//        _leftBufferOut = new FLOAT[_bufferSize[0]];
//
//        _rightBufferIn  = new FLOAT[_bufferSize[0]];
//        _rightBufferOut = new FLOAT[_bufferSize[0]];
//
//        _bottomBufferIn  = new FLOAT[_bufferSize[1]];
//        _bottomBufferOut = new FLOAT[_bufferSize[1]];
//
//        _topBufferIn  = new FLOAT[_bufferSize[1]];
//        _topBufferOut = new FLOAT[_bufferSize[1]];

    } else if (flowField.getDim() == 3) {

    	int max_size = 0;
    	const int xy_plane_size = flowField.getCellsX()*flowField.getCellsY();
    	const int yz_plane_size = flowField.getCellsY()*flowField.getCellsZ();
    	const int xz_plane_size = flowField.getCellsX()*flowField.getCellsZ();
    	max_size = max(max(xy_plane_size, yz_plane_size), xz_plane_size);
    	_bufferSize =max_size * 5;


        _leftBufferIn  = new FLOAT[_bufferSize];
        _leftBufferOut = new FLOAT[_bufferSize];

        _rightBufferIn  = new FLOAT[_bufferSize];
        _rightBufferOut = new FLOAT[_bufferSize];

        _bottomBufferIn  = new FLOAT[_bufferSize];
        _bottomBufferOut = new FLOAT[_bufferSize];

        _topBufferIn  = new FLOAT[_bufferSize];
        _topBufferOut = new FLOAT[_bufferSize];

        _frontBufferIn  = new FLOAT[_bufferSize];
        _frontBufferOut = new FLOAT[_bufferSize];

        _backBufferIn  = new FLOAT[_bufferSize];
        _backBufferOut = new FLOAT[_bufferSize];
        std::cout<<"buffers:"<<_bufferSize<<std::endl;
    }
}
void LBParallelManager::communicatePdfs(){
	_extractPdfsStencil.reset();
	_extractPdfsIteratorX.iterate();

	MPI_Sendrecv(_leftBufferOut, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.leftNb, 0,
	 _rightBufferIn, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.rightNb, 0,
	 PETSC_COMM_WORLD, &_mpiStatus);
	MPI_Sendrecv(_rightBufferOut, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.rightNb, 1,
	 _leftBufferIn, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.leftNb, 1,
	 PETSC_COMM_WORLD, &_mpiStatus);
	_injectPdfsStencil.reset();
	_injectPdfsIteratorX.iterate();

	_extractPdfsStencil.reset();
	_extractPdfsIteratorY.iterate();
	MPI_Sendrecv(_bottomBufferOut, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.bottomNb, 2,
	 _topBufferIn, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.topNb, 2,
	 PETSC_COMM_WORLD, &_mpiStatus);
	MPI_Sendrecv(_topBufferOut, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.topNb, 3,
	 _bottomBufferIn, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.bottomNb, 3,
	 PETSC_COMM_WORLD, &_mpiStatus);
	_injectPdfsStencil.reset();
	_injectPdfsIteratorY.iterate();

	_extractPdfsStencil.reset();
	_extractPdfsIteratorZ.iterate();
	MPI_Sendrecv(_frontBufferOut, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.frontNb, 4,
	 _backBufferIn, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.backNb, 4,
	 PETSC_COMM_WORLD, &_mpiStatus);
	MPI_Sendrecv(_backBufferOut, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.backNb, 5,
	 _frontBufferIn, _bufferSize, MY_MPI_FLOAT, _parameters.parallel.frontNb, 5,
	 PETSC_COMM_WORLD, &_mpiStatus);
	_injectPdfsStencil.reset();
	_injectPdfsIteratorZ.iterate();
}
LBParallelManager::~LBParallelManager(){

    delete[] _leftBufferIn;
    delete[] _rightBufferIn;
    delete[] _bottomBufferIn;
    delete[] _topBufferIn;
    delete[] _leftBufferOut;
    delete[] _rightBufferOut;
    delete[] _bottomBufferOut;
    delete[] _topBufferOut;

    if (_flowField.getDim() == 3){
        delete[] _frontBufferIn;
        delete[] _frontBufferOut;
        delete[] _backBufferIn;
        delete[] _backBufferOut;
    }
}
