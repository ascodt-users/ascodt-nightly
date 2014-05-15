#include "BufferStencils.h"
#include <assert.h>
#ifdef D3Q19
const int velocitiesLeft3D[5] =   {1, 5, 8, 11, 15};
const int velocitiesRight3D[5] =  {3, 7, 10, 13, 17};
const int velocitiesBottom3D[5] = {0, 5, 6, 7, 14};
const int velocitiesTop3D[5] =    {4, 11, 12, 13, 18};
const int velocitiesFront3D[5] =  {0, 1, 2, 3, 4};
const int velocitiesBack3D[5] =   {14, 15, 16, 17, 18};
const int wallVelocityCount = 5;
#endif

#ifdef D3Q27
const int velocitiesLeft3D  [9] = {0, 3, 6, 9, 12, 15, 18, 21, 24};
const int velocitiesRight3D [9] = {2, 5, 8, 11, 14, 17, 20, 23, 26};
const int velocitiesBottom3D[9] = {0, 1, 2, 9, 10, 11, 18, 19, 20};
const int velocitiesTop3D   [9] = {6, 7, 8, 15, 16, 17, 24, 25, 26};
const int velocitiesFront3D [9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const int velocitiesBack3D  [9] = {18, 19, 20, 21, 22, 23, 24, 25, 25};
const int wallVelocityCount = 9;
#endif

#ifdef D3Q15
const int velocitiesLeft3D  [5] = {0, 3, 6, 10, 13};
const int velocitiesRight3D [5] = {1, 4, 8, 11, 14};
const int velocitiesBottom3D[5] = {0, 1, 5, 10, 11};
const int velocitiesTop3D   [5] = {3, 4, 9, 13, 14};
const int velocitiesFront3D [5] = {0, 1, 2, 3, 4};
const int velocitiesBack3D  [5] = {10, 11, 12, 13, 14};
const int wallVelocityCount = 5;
#endif

const int velocitiesLeft2D[3] = {6, 7, 8};
const int velocitiesRight2D[3] = {0, 1, 2};
const int velocitiesBottom2D[3] = {2, 3, 8};
const int velocitiesTop2D[3] = {0, 5, 6};
LBBufferFillStencil::LBBufferFillStencil (const Parameters & parameters,
                                                      FLOAT * & leftBufferOut,
                                                      FLOAT * & rightBufferOut,
                                                      FLOAT * & bottomBufferOut,
                                                      FLOAT * & topBufferOut,
                                                      FLOAT * & frontBufferOut,
                                                      FLOAT * & backBufferOut) :
    ParallelBoundaryStencil<LBField>(parameters),
    _leftBufferOut   (leftBufferOut),
    _rightBufferOut  (rightBufferOut),
    _bottomBufferOut (bottomBufferOut),
    _topBufferOut    (topBufferOut),
    _frontBufferOut  (frontBufferOut),
    _backBufferOut   (backBufferOut),
    _leftBufferIndex(0),
    _rightBufferIndex(0),
    _bottomBufferIndex(0),
    _topBufferIndex(0),
    _frontBufferIndex(0),
    _backBufferIndex(0)
{}
void LBBufferFillStencil::reset(){
	  _leftBufferIndex=0;
	  _rightBufferIndex=0;
	  _bottomBufferIndex=0;
	  _topBufferIndex=0;
	  _frontBufferIndex=0;
	  _backBufferIndex=0;
}
void LBBufferFillStencil::extract(LBField& field,FLOAT* buffer,const int* faceIndex,int& bufferIndex, int i,int j,int k){
	if(field.getFlags()[field.getIndexCell(i,j,k)]==(char)(0)){
		buffer[bufferIndex + 0] = field.getFOut()[field.getIndexF(faceIndex[0], i, j, k)];
		buffer[bufferIndex + 1] = field.getFOut()[field.getIndexF(faceIndex[1], i, j, k)];
		buffer[bufferIndex + 2] = field.getFOut()[field.getIndexF(faceIndex[2], i, j, k)];
		buffer[bufferIndex + 3] = field.getFOut()[field.getIndexF(faceIndex[3], i, j, k)];
		buffer[bufferIndex + 4] = field.getFOut()[field.getIndexF(faceIndex[4], i, j, k)];
		bufferIndex+=5;
	}
}

void LBBufferFillStencil::extract(LBField& field,FLOAT* buffer,const int* faceIndex,int& bufferIndex, int i,int j){
	//TODO
}

void LBBufferReadStencil::inject(LBField& field,FLOAT* buffer,const int* faceIndex,int& bufferIndex, int i,int j,int k){
	if(field.getFlags()[field.getIndexCell(i,j,k)]==(char)(0)){
		 field.getFOut()[field.getIndexF(faceIndex[0], i, j, k)] = buffer[bufferIndex + 0];
		 field.getFOut()[field.getIndexF(faceIndex[1], i, j, k)] = buffer[bufferIndex + 1];
		 field.getFOut()[field.getIndexF(faceIndex[2], i, j, k)] = buffer[bufferIndex + 2];
		 field.getFOut()[field.getIndexF(faceIndex[3], i, j, k)] = buffer[bufferIndex + 3];
		 field.getFOut()[field.getIndexF(faceIndex[4], i, j, k)] = buffer[bufferIndex + 4];
         bufferIndex += 5;
    }
}
void LBBufferReadStencil::inject(LBField& field,FLOAT* buffer,const int* faceIndex,int& bufferIndex, int i,int j){
	//TODO
}
void LBBufferFillStencil::applyLeftWall (LBField & flowField, int i, int j){
//    _leftBufferOut[ 2*j ] = flowField.getVelocity().getVector(2, j)[0];
//    _leftBufferOut[2*j+1] = flowField.getVelocity().getVector(2, j)[1];
}

void LBBufferFillStencil::applyRightWall (LBField & flowField, int i, int j){
//    _rightBufferOut[ 2*j ] = flowField.getVelocity().getVector(flowField.getNx()  , j)[0];
//    _rightBufferOut[2*j+1] = flowField.getVelocity().getVector(flowField.getNx()+1, j)[1];
}

void LBBufferFillStencil::applyBottomWall (LBField & flowField, int i, int j){
//    _bottomBufferOut[ 2*i ] = flowField.getVelocity().getVector(i, 2)[0];
//    _bottomBufferOut[2*i+1] = flowField.getVelocity().getVector(i, 2)[1];
}

void LBBufferFillStencil::applyTopWall (LBField & flowField, int i, int j){
//    _topBufferOut[ 2*i ] = flowField.getVelocity().getVector(i, flowField.getNy()+1)[0];
//    _topBufferOut[2*i+1] = flowField.getVelocity().getVector(i, flowField.getNy()  )[1];
}

void LBBufferFillStencil::applyLeftWall   (LBField & flowField, int i, int j, int k){
	extract(flowField,_leftBufferOut,velocitiesLeft3D,_leftBufferIndex,i,j,k);
}

void LBBufferFillStencil::applyRightWall  (LBField & flowField, int i, int j, int k){
	extract(flowField,_rightBufferOut,velocitiesRight3D,_rightBufferIndex,i,j,k);
}

void LBBufferFillStencil::applyBottomWall (LBField & flowField, int i, int j, int k){
	extract(flowField,_bottomBufferOut,velocitiesBottom3D,_bottomBufferIndex,i,j,k);
}

void LBBufferFillStencil::applyTopWall    (LBField & flowField, int i, int j, int k){
	extract(flowField,_topBufferOut,velocitiesTop3D,_topBufferIndex,i,j,k);
}

void LBBufferFillStencil::applyFrontWall  (LBField & flowField, int i, int j, int k){
	extract(flowField,_frontBufferOut,velocitiesFront3D,_frontBufferIndex,i,j,k);
}

void LBBufferFillStencil::applyBackWall   (LBField & flowField, int i, int j, int k){
	extract(flowField,_backBufferOut,velocitiesBack3D,_backBufferIndex,i,j,k);
}



LBBufferReadStencil::LBBufferReadStencil (const Parameters & parameters,
                                                      FLOAT * & leftBufferIn,
                                                      FLOAT * & rightBufferIn,
                                                      FLOAT * & bottomBufferIn,
                                                      FLOAT * & topBufferIn,
                                                      FLOAT * & frontBufferIn,
                                                      FLOAT * & backBufferIn) :
    ParallelBoundaryStencil<LBField>(parameters),
    _leftBufferIn   (leftBufferIn),
    _rightBufferIn  (rightBufferIn),
    _bottomBufferIn (bottomBufferIn),
    _topBufferIn    (topBufferIn),
    _frontBufferIn  (frontBufferIn),
    _backBufferIn   (backBufferIn),
    _leftBufferIndex(0),
    _rightBufferIndex(0),
    _bottomBufferIndex(0),
    _topBufferIndex(0),
    _frontBufferIndex(0),
    _backBufferIndex(0)
{}
void LBBufferReadStencil::reset(){
	  _leftBufferIndex=0;
	  _rightBufferIndex=0;
	  _bottomBufferIndex=0;
	  _topBufferIndex=0;
	  _frontBufferIndex=0;
	  _backBufferIndex=0;
}
void LBBufferReadStencil::applyLeftWall (LBField & flowField, int i, int j){
//    flowField.getVelocity().getVector(0, j)[0] = _leftBufferIn[ 2*j ];
//    flowField.getVelocity().getVector(1, j)[1] = _leftBufferIn[2*j+1];
}

void LBBufferReadStencil::applyRightWall (LBField & flowField, int i, int j){
//    flowField.getVelocity().getVector(flowField.getNx()+2, j)[0] = _rightBufferIn[ 2*j ];
//    flowField.getVelocity().getVector(flowField.getNx()+2, j)[1] = _rightBufferIn[2*j+1];
}

void LBBufferReadStencil::applyBottomWall (LBField & flowField, int i, int j){
//    flowField.getVelocity().getVector(i, 1)[0] = _bottomBufferIn[ 2*i ];
//    flowField.getVelocity().getVector(i, 0)[1] = _bottomBufferIn[2*i+1];
}

void LBBufferReadStencil::applyTopWall (LBField & flowField, int i, int j){
//    flowField.getVelocity().getVector(i, flowField.getNy()+2)[0] = _topBufferIn[ 2*i ];
//    flowField.getVelocity().getVector(i, flowField.getNy()+2)[1] = _topBufferIn[2*i+1];
}

void LBBufferReadStencil::applyLeftWall   (LBField & flowField, int i, int j, int k){
	inject(flowField,_leftBufferIn,velocitiesRight3D,_leftBufferIndex,i,j,k);
}

void LBBufferReadStencil::applyRightWall  (LBField & flowField, int i, int j, int k){
	inject(flowField,_rightBufferIn,velocitiesLeft3D,_rightBufferIndex,i,j,k);
}

void LBBufferReadStencil::applyBottomWall (LBField & flowField, int i, int j, int k){
	inject(flowField,_bottomBufferIn,velocitiesTop3D,_bottomBufferIndex,i,j,k);
}

void LBBufferReadStencil::applyTopWall    (LBField & flowField, int i, int j, int k){
	inject(flowField,_topBufferIn,velocitiesBottom3D,_topBufferIndex,i,j,k);
}

void LBBufferReadStencil::applyFrontWall  (LBField & flowField, int i, int j, int k){
	inject(flowField,_frontBufferIn,velocitiesBack3D,_frontBufferIndex,i,j,k);
}

void LBBufferReadStencil::applyBackWall   (LBField & flowField, int i, int j, int k){
	inject(flowField,_backBufferIn,velocitiesFront3D,_backBufferIndex,i,j,k);
}

