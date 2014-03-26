#include "LBNSInitFlagsIterator.h"


LBNSInitFlagsIterator::LBNSInitFlagsIterator(const Parameters & parameters,
		FlowField & flowField):
		_flowField (flowField),
		_parameters (parameters),
		_offset (getOverlapWidth (parameters)),

		_lowerX (parameters.coupling.offsetNS[0] + _offset),
		_upperX (parameters.coupling.offsetNS[0] + parameters.coupling.sizeNS[0] - _offset - 1),
		_lowerY (parameters.coupling.offsetNS[1] + _offset),
		_upperY (parameters.coupling.offsetNS[1] + parameters.coupling.sizeNS[1] - _offset - 1),
		_lowerZ (parameters.coupling.offsetNS[2] + _offset),
		_upperZ (parameters.coupling.offsetNS[2] + parameters.coupling.sizeNS[2] - _offset - 1)
{}

void LBNSInitFlagsIterator::iterate(){
	IntScalarField & flags = _flowField.getFlags();



	//	// Left and right faces

	for (int k = _lowerZ-1; k<=_upperZ+1; k++)
		for (int j = _lowerY-1; j <= _upperY+1; j++)
			for(int i = _lowerX-1; i<=_upperX+1; i++){
				if(k>=_lowerZ&&k<=_upperZ &&
						j>=_lowerY&&j<=_upperY&&
						i>=_lowerX&&i<=_upperX){
					flags.getValue(i, j, k) = OBSTACLE_SELF;

					if(k>_lowerZ&&k<_upperZ &&
							j>_lowerY&&j<_upperY&&
							i>_lowerX&&i<_upperX){
						flags.getValue(i, j, k) += OBSTACLE_LEFT;
						flags.getValue(i, j, k) += OBSTACLE_RIGHT;
						flags.getValue(i, j, k) += OBSTACLE_TOP;
						flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
						flags.getValue(i, j, k) += OBSTACLE_FRONT;
						flags.getValue(i, j, k) += OBSTACLE_BACK;
					}else{
						if(i-1>=_lowerX)
							flags.getValue(i, j, k) += OBSTACLE_LEFT;
						if(i+1<=_upperX)
							flags.getValue(i, j, k) += OBSTACLE_RIGHT;
						if(j-1>=_lowerY)
							flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
						if(j+1<=_upperY)
							flags.getValue(i, j, k) += OBSTACLE_TOP;
						if(k-1>=_lowerZ)
							flags.getValue(i, j, k) += OBSTACLE_FRONT;
						if(k+1<=_upperZ)
							flags.getValue(i, j, k) += OBSTACLE_BACK;

					}
				}else{
					if(i-1>=_lowerX)
						flags.getValue(i, j, k) += OBSTACLE_LEFT;
					if(i+1<=_upperX)
						flags.getValue(i, j, k) += OBSTACLE_RIGHT;
					if(j-1>=_lowerY)
						flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
					if(j+1<=_upperY)
						flags.getValue(i, j, k) += OBSTACLE_TOP;
					if(k-1>=_lowerZ)
						flags.getValue(i, j, k) += OBSTACLE_FRONT;
					if(k+1<=_upperZ)
						flags.getValue(i, j, k) += OBSTACLE_BACK;
				}
			}


}
