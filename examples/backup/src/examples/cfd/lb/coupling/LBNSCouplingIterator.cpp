#include "LBNSCouplingIterator.h"
#include "CouplingFunctions.h"
#include "LBNSCommunicator.h"
// Required right before the call to interpolate on boundary
void LBNSCouplingIterator::setNormalVector(int nx, int ny, int nz){
	_normalVector[0] = nx;
	_normalVector[1] = ny;
	_normalVector[2] = nz;
}



void LBNSCouplingIterator::interpolateComponentX (int i, int j, int k) {
	//_lbVelocityX.push_back(
	_interpolator.interpolateVelocityComponent(i, j, k, 0);
	//);

}

void LBNSCouplingIterator::interpolateComponentY (int i, int j, int k) {
	//_lbVelocityY.push_back(
	_interpolator.interpolateVelocityComponent(i, j, k, 1);
	//);


}

void LBNSCouplingIterator::interpolateComponentZ (int i, int j, int k) {
	//_lbVelocityZ.push_back(
	_interpolator.interpolateVelocityComponent(i, j, k, 2);
	//);
}


LBNSCouplingIterator::LBNSCouplingIterator(const Parameters & parameters,
		LBField & lbField):
    						_lbField (lbField), _parameters (parameters),
    						_interpolator (parameters, lbField),
    						_offset (getOverlapWidth (parameters)),

    						_lowerX (parameters.coupling.offsetNS[0] + _offset),
    						_upperX (parameters.coupling.offsetNS[0] + parameters.coupling.sizeNS[0] - _offset - 1),
    						_lowerY (parameters.coupling.offsetNS[1] + _offset),
    						_upperY (parameters.coupling.offsetNS[1] + parameters.coupling.sizeNS[1] - _offset - 1),
    						_lowerZ (parameters.coupling.offsetNS[2] + _offset),
    						_upperZ (parameters.coupling.offsetNS[2] + parameters.coupling.sizeNS[2] - _offset - 1)
{}

void LBNSCouplingIterator::iterateInner(){
	// Left and right faces
	/*_lbVelocityX.clear();
	_lbVelocityY.clear();
	_lbVelocityZ.clear();*/
	for (int i = _lowerZ; i < _upperZ; i++)
		for (int j = _lowerY; j <_upperY; j++)
			for (int k = _lowerX; k < _upperX; k++){
				interpolateComponentX (k, j, i);
				interpolateComponentY (k, j, i);
				interpolateComponentZ (k, j, i);
			}
}

void LBNSCouplingIterator::registerNSRegion(
		LBNSCommunicator* com){
	_interpolator.registerNSRegion(com);
}
void LBNSCouplingIterator::iterateBoundary(){
	/*_lbVelocityX.clear();
		_lbVelocityY.clear();
		_lbVelocityZ.clear();*/

	std::cout<<"starting boundary iteration on rank:"<<_parameters.parallel.rank<<std::endl;
	std::cout<<"boundary iteration on rank:"<<_parameters.parallel.rank<<
			"lower:"<<_lowerX<<","<<_lowerY<<","<<_lowerZ<<
			"upper:"<<_upperX<<","<<_upperY<<","<<_upperZ<<std::endl;



	for (int j = _lowerY; j <= _upperY - 1; j++){
		for (int k = _lowerZ; k <= _upperZ - 1; k++){
			// Left face
			interpolateComponentX (_lowerX-1, j, k);
			interpolateComponentY (_lowerX, j, k);
			interpolateComponentZ (_lowerX, j, k);

			// Right face
			interpolateComponentX (_upperX, j, k);
			interpolateComponentY (_upperX, j, k);
			interpolateComponentZ (_upperX, j, k);
		}
		// The line not included in the upper side
		interpolateComponentX (_lowerX-1, j, _upperZ);
		interpolateComponentY (_lowerX, j, _upperZ);

		interpolateComponentX (_upperX, j, _upperZ);
		interpolateComponentY (_upperX, j, _upperZ);
	}
	// The line in the other direction
	for (int k = _lowerZ; k <= _upperZ - 1; k++){
		interpolateComponentX (_lowerX-1, _upperY, k);
		interpolateComponentZ (_lowerX, _upperY, k);

		interpolateComponentX (_upperX, _upperY, k);
		interpolateComponentZ(_upperX, _upperY, k);
	}
	interpolateComponentX (_lowerX-1, _upperY, _upperZ);
	interpolateComponentX (_upperX, _upperY, _upperZ);
	// There's a point that is written two times. I don't care

	// Top and bottom faces
	for (int k = _lowerZ; k <= _upperZ - 1; k++){
		for (int i = _lowerX ; i <= _upperX - 1; i++){
			// Bottom face
			interpolateComponentX (i, _lowerY, k);
			interpolateComponentY (i, _lowerY-1, k);
			interpolateComponentZ (i, _lowerY, k);

			// Top face
			interpolateComponentX (i, _upperY, k);
			interpolateComponentY (i, _upperY, k);
			interpolateComponentZ(i, _upperY, k);
		}
	}
	for (int i = _lowerX ; i <= _upperX - 1; i++){
		interpolateComponentX (i, _lowerY, _upperZ);
		interpolateComponentY (i, _lowerY-1, _upperZ);

		interpolateComponentX (i, _upperY, _upperZ);
		interpolateComponentY (i, _upperY, _upperZ);
	}
	for (int i = _lowerZ; i <= _upperZ - 1; i++){
		interpolateComponentZ (_upperX, _lowerY,i);
		interpolateComponentY (_upperX, _lowerY-1, i);

		interpolateComponentZ (_upperX, _upperY, i);
		interpolateComponentY (_upperX, _upperY, i);
	}

	interpolateComponentY (_upperX, _lowerY-1, _upperZ);
	interpolateComponentY (_upperX, _upperY, _upperZ);
	// Front and back method
	for (int j = _lowerY ; j <= _upperY - 1; j++){
		for (int i = _lowerX ; i <= _upperX - 1; i++){
			// Front wall
			interpolateComponentX (i, j, _lowerZ);
			interpolateComponentY (i, j, _lowerZ);
			interpolateComponentZ (i, j, _lowerZ-1);

			// Back wall
			interpolateComponentX (i, j, _upperZ);
			interpolateComponentY (i, j, _upperZ);
			interpolateComponentZ (i, j, _upperZ);
		}
	}

	for (int i = _lowerY ; i <= _upperY - 1; i++){
		interpolateComponentY (_upperX,i, _lowerZ);
		interpolateComponentZ (_upperX, i, _lowerZ-1);

		interpolateComponentY (_upperX, i, _upperZ);
		interpolateComponentZ (_upperX, i, _upperZ);
	}

	for (int i = _lowerX ; i <= _upperX - 1; i++){
		interpolateComponentX (i,_upperY, _lowerZ);
		interpolateComponentZ (i,_upperY, _lowerZ-1);

		interpolateComponentX (i, _upperY, _upperZ);
		interpolateComponentZ (i, _upperY, _upperZ);
	}
	interpolateComponentZ (_upperX, _upperY, _lowerZ-1);
	interpolateComponentZ (_upperX, _upperY, _upperZ);
	_interpolator.flush();

}
int LBNSCouplingIterator::getVelocitySizeX(){
	return _lbVelocityX.size();
}
int LBNSCouplingIterator::getVelocitySizeY(){
	return _lbVelocityY.size();
}
int LBNSCouplingIterator::getVelocitySizeZ(){
	return _lbVelocityZ.size();
}
double* LBNSCouplingIterator::getVelocityX(){
	return &_lbVelocityX[0];
}
double* LBNSCouplingIterator::getVelocityY(){
	return &_lbVelocityY[0];
}
double* LBNSCouplingIterator::getVelocityZ(){
	return &_lbVelocityZ[0];
}
