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
{


}
inline bool LBNSInitFlagsIterator::toLocalIndex(const int i,const int j, const int k,int& i_out,int& j_out, int& k_out) const{
	i_out=i-_parameters.parallel.firstCorner[0];
	j_out=j-_parameters.parallel.firstCorner[1];
	k_out=k-_parameters.parallel.firstCorner[2];
	return i_out-2>=0&&j_out-2>=0&&k_out-2>=0&&
		   i_out-2<_parameters.parallel.localSize[0]&&
		   j_out-2<_parameters.parallel.localSize[1]&&
		   k_out-2<_parameters.parallel.localSize[2];
}
void LBNSInitFlagsIterator::iterate(){
	IntScalarField & flags = _flowField.getFlags();
	std::cout<<"boundary init flags on rank:"<<_parameters.parallel.rank<<
				"corner:"<<_parameters.parallel.firstCorner[0]<<","<<_parameters.parallel.firstCorner[1]<<","<<_parameters.parallel.firstCorner[2]<<
				std::endl;

	std::cout<<"flags:"<<_parameters.parallel.rank<<
					"lower:"<<_lowerX<<","<<_lowerY<<","<<_lowerZ<<
					"upper:"<<_upperX<<","<<_upperY<<","<<_upperZ<<std::endl;


	//	// Left and right faces
	int k,j,i;

	for (int globalK = _lowerZ-1; globalK<=_upperZ+1; globalK++)
		for (int globalJ = _lowerY-1; globalJ <= _upperY+1; globalJ++)
			for(int globalI = _lowerX-1; globalI<=_upperX+1; globalI++){
				if(toLocalIndex(globalI,globalJ,globalK,i,j,k)){
					if( globalK>=_lowerZ&&globalK<=_upperZ &&
							globalJ>=_lowerY&&globalJ<=_upperY&&
							globalI>=_lowerX&&globalI<=_upperX){

						flags.getValue(i, j, k) = OBSTACLE_SELF;

						if(
								globalK>_lowerZ&&globalK<_upperZ &&
								globalJ>_lowerY&&globalJ<_upperY&&
								globalI>_lowerX&&globalI<_upperX){
							flags.getValue(i, j, k) += OBSTACLE_LEFT;
							flags.getValue(i, j, k) += OBSTACLE_RIGHT;
							flags.getValue(i, j, k) += OBSTACLE_TOP;
							flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
							flags.getValue(i, j, k) += OBSTACLE_FRONT;
							flags.getValue(i, j, k) += OBSTACLE_BACK;
						}else{
							if(globalI-1>=_lowerX)
								flags.getValue(i, j, k) += OBSTACLE_LEFT;
							if(globalI+1<=_upperX)
								flags.getValue(i, j, k) += OBSTACLE_RIGHT;
							if(globalJ-1>=_lowerY)
								flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
							if(globalJ+1<=_upperY)
								flags.getValue(i, j, k) += OBSTACLE_TOP;
							if(globalK-1>=_lowerZ)
								flags.getValue(i, j, k) += OBSTACLE_FRONT;
							if(globalK+1<=_upperZ)
								flags.getValue(i, j, k) += OBSTACLE_BACK;

						}

					}else{
//						if(globalI-1>=_lowerX)
//							flags.getValue(i, j, k) += OBSTACLE_LEFT;
//						if(globalI+1<=_upperX)
//							flags.getValue(i, j, k) += OBSTACLE_RIGHT;
//						if(globalJ-1>=_lowerY)
//							flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
//						if(globalJ+1<=_upperY)
//							flags.getValue(i, j, k) += OBSTACLE_TOP;
//						if(globalK-1>=_lowerZ)
//							flags.getValue(i, j, k) += OBSTACLE_FRONT;
//						if(globalK+1<=_upperZ)
//							flags.getValue(i, j, k) += OBSTACLE_BACK;
					}
				}
			}

//	for (int k = _lowerZ-1; k<=_upperZ+1; k++)
//			for (int j = _lowerY-1; j <= _upperY+1; j++)
//				for(int i = _lowerX-1; i<=_upperX+1; i++){
//					if(k>=_lowerZ&&k<=_upperZ &&
//							j>=_lowerY&&j<=_upperY&&
//							i>=_lowerX&&i<=_upperX){
//						flags.getValue(i, j, k) = OBSTACLE_SELF;
//
//						if(k>_lowerZ&&k<_upperZ &&
//								j>_lowerY&&j<_upperY&&
//								i>_lowerX&&i<_upperX){
//							flags.getValue(i, j, k) += OBSTACLE_LEFT;
//							flags.getValue(i, j, k) += OBSTACLE_RIGHT;
//							flags.getValue(i, j, k) += OBSTACLE_TOP;
//							flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
//							flags.getValue(i, j, k) += OBSTACLE_FRONT;
//							flags.getValue(i, j, k) += OBSTACLE_BACK;
//						}else{
//							if(i-1>=_lowerX)
//								flags.getValue(i, j, k) += OBSTACLE_LEFT;
//							if(i+1<=_upperX)
//								flags.getValue(i, j, k) += OBSTACLE_RIGHT;
//							if(j-1>=_lowerY)
//								flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
//							if(j+1<=_upperY)
//								flags.getValue(i, j, k) += OBSTACLE_TOP;
//							if(k-1>=_lowerZ)
//								flags.getValue(i, j, k) += OBSTACLE_FRONT;
//							if(k+1<=_upperZ)
//								flags.getValue(i, j, k) += OBSTACLE_BACK;
//
//						}
//					}else{
//						/*if(i-1>=_lowerX)
//							flags.getValue(i, j, k) += OBSTACLE_LEFT;
//						if(i+1<=_upperX)
//							flags.getValue(i, j, k) += OBSTACLE_RIGHT;
//						if(j-1>=_lowerY)
//							flags.getValue(i, j, k) += OBSTACLE_BOTTOM;
//						if(j+1<=_upperY)
//							flags.getValue(i, j, k) += OBSTACLE_TOP;
//						if(k-1>=_lowerZ)
//							flags.getValue(i, j, k) += OBSTACLE_FRONT;
//						if(k+1<=_upperZ)
//							flags.getValue(i, j, k) += OBSTACLE_BACK;*/
//					}
//				}



}
