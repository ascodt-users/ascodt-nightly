#ifndef _BUFFER_STENCILS_H_
#define _BUFFER_STENCILS_H_

#include "Stencil.h"
#include "../LBField.h"

// This class should not be called global

class LBBufferFillStencil : public ParallelBoundaryStencil<LBField> {

private:

	FLOAT * & _leftBufferOut;
	FLOAT * & _rightBufferOut;
	FLOAT * & _bottomBufferOut;
	FLOAT * & _topBufferOut;
	FLOAT * & _frontBufferOut;
	FLOAT * & _backBufferOut;
	int _leftBufferIndex;
	int _rightBufferIndex;
	int _bottomBufferIndex;
	int _topBufferIndex;
	int _frontBufferIndex;
	int _backBufferIndex;
	void extract(LBField& field,FLOAT* buffer,const int* faceIndex,int& bufferIndex, int i,int j,int k);
	void extract(LBField& field,FLOAT* buffer,const int* faceIndex,int& bufferIndex, int i,int j);

public:

	LBBufferFillStencil (const Parameters & parameters,
			FLOAT * & leftBufferOut,
			FLOAT * & rightBufferOut,
			FLOAT * & bottomBufferOut,
			FLOAT * & topBufferOut,
			FLOAT * & frontBufferOut,
			FLOAT * & backBufferOut);
	void reset();
	void applyLeftWall   (LBField & flowField, int i, int j);
	void applyRightWall  (LBField & flowField, int i, int j);
	void applyBottomWall (LBField & flowField, int i, int j);
	void applyTopWall    (LBField & flowField, int i, int j);

	void applyLeftWall   (LBField & flowField, int i, int j, int k);
	void applyRightWall  (LBField & flowField, int i, int j, int k);
	void applyBottomWall (LBField & flowField, int i, int j, int k);
	void applyTopWall    (LBField & flowField, int i, int j, int k);
	void applyFrontWall  (LBField & flowField, int i, int j, int k);
	void applyBackWall   (LBField & flowField, int i, int j, int k);
};


class LBBufferReadStencil : public ParallelBoundaryStencil<LBField> {

private:

	FLOAT * & _leftBufferIn;
	FLOAT * & _rightBufferIn;
	FLOAT * & _bottomBufferIn;
	FLOAT * & _topBufferIn;
	FLOAT * & _frontBufferIn;
	FLOAT * & _backBufferIn;
	int _leftBufferIndex;
	int _rightBufferIndex;
	int _bottomBufferIndex;
	int _topBufferIndex;
	int _frontBufferIndex;
	int _backBufferIndex;
	void inject(LBField& field,FLOAT* buffer,const int* faceIndex,int& bufferIndex, int i,int j,int k);
	void inject(LBField& field,FLOAT* buffer,const int* faceIndex,int& bufferIndex, int i,int j);
public:

	LBBufferReadStencil (const Parameters & parameters,
			FLOAT * & leftBufferIn,
			FLOAT * & rightBufferIn,
			FLOAT * & bottomBufferIn,
			FLOAT * & topBufferIn,
			FLOAT * & frontBufferIn,
			FLOAT * & backBufferIn);
	void reset();
	void applyLeftWall   (LBField & flowField, int i, int j);
	void applyRightWall  (LBField & flowField, int i, int j);
	void applyBottomWall (LBField & flowField, int i, int j);
	void applyTopWall    (LBField & flowField, int i, int j);

	void applyLeftWall   (LBField & flowField, int i, int j, int k);
	void applyRightWall  (LBField & flowField, int i, int j, int k);
	void applyBottomWall (LBField & flowField, int i, int j, int k);
	void applyTopWall    (LBField & flowField, int i, int j, int k);
	void applyFrontWall  (LBField & flowField, int i, int j, int k);
	void applyBackWall   (LBField & flowField, int i, int j, int k);
};



#endif
