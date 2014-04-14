#include "LBNSFGHCorrectionIterator.h"
inline bool LBNSFGHCorrectionIterator::toLocalIndex(const int i,const int j, const int k,int& i_out,int& j_out, int& k_out) const{
	i_out=i-_parameters.parallel.firstCorner[0];
	j_out=j-_parameters.parallel.firstCorner[1];
	k_out=k-_parameters.parallel.firstCorner[2];
	return i_out-2>=0&&j_out-2>=0&&k_out-2>=0&&
			i_out-2<_parameters.parallel.localSize[0]&&
			j_out-2<_parameters.parallel.localSize[1]&&
			k_out-2<_parameters.parallel.localSize[2];
}

void LBNSFGHCorrectionIterator::setComponent (int i, int j, int k, int component) {
	int localIndexI,localIndexJ,localIndexK;
	if(toLocalIndex(i,j,k,localIndexI,localIndexJ,localIndexK))
	_flowField.getFGH().getVector(localIndexI,localIndexJ,localIndexK)[component] =
        _flowField.getVelocity().getVector(localIndexI,localIndexJ,localIndexK)[component];
}

LBNSFGHCorrectionIterator::LBNSFGHCorrectionIterator(const Parameters & parameters,
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

void LBNSFGHCorrectionIterator::iterate(){
if(
_lowerX<_upperX &&
_lowerY<_upperY &&
_lowerZ<_upperZ

){
    // Left and right faces
    for (int j = _lowerY; j <= _upperY; j++){
        for (int k = _lowerZ; k <= _upperZ; k++){
            setComponent(_lowerX-1, j, k, 0);
            setComponent(_upperX  , j, k, 0);
        }
    }

    // Top and bottom faces
    for (int i = _lowerX; i <= _upperX; i++){
        for (int k = _lowerZ; k <= _upperZ; k++){
            setComponent(i, _lowerY-1, k, 1);
            setComponent(i, _upperY  , k, 1);
        }
    }

    // Front and back walls
    for (int i = _lowerX; i <= _upperX; i++){
        for (int j = _lowerY; j <= _upperY; j++){
            setComponent(i, j, _lowerZ-1, 2);
            setComponent(i, j, _upperZ  , 2);
        }
    }
}
}
