#include "LBNSCouplingIterator.h"
#include "CouplingFunctions.h"
// Required right before the call to interpolate on boundary
void LBNSCouplingIterator::setNormalVector(int nx, int ny, int nz){
	_normalVector[0] = nx;
	_normalVector[1] = ny;
	_normalVector[2] = nz;
}


void LBNSCouplingIterator::interpolateComponentX (int i, int j, int k, int component,int velocityCounter) {
	_flowField.getVelocity().getVector(i, j, k)[0] =
			_lbVelocityX[velocityCounter];
	//std::cout<<"nx:"<<_lbVelocityX[velocityCounter]<<std::endl;
}


void LBNSCouplingIterator::interpolateComponentY (int i, int j, int k, int component,int velocityCounter) {
	_flowField.getVelocity().getVector(i, j, k)[1] =
			_lbVelocityY[velocityCounter];

	//std::cout<<"ny:"<<_lbVelocityY[velocityCounter]<<std::endl;
}


void LBNSCouplingIterator::interpolateComponentZ (int i, int j, int k, int component,int velocityCounter) {
	_flowField.getVelocity().getVector(i, j, k)[2] =
			_lbVelocityZ[velocityCounter];

	//std::cout<<"nz:"<<_lbVelocityZ[velocityCounter]<<std::endl;
}


LBNSCouplingIterator::LBNSCouplingIterator(const Parameters & parameters,
		FlowField & flowField):
				_flowField (flowField), _parameters (parameters),
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
	int velocity_counterX=0;
	int velocity_counterY=0;
	int velocity_counterZ=0;
	std::cout<<"x:"<<_lowerX<<","<<_upperX<<","
			<<"y:"<<_lowerY<<","<<_upperY<<","
			<<"z:"<<_lowerZ<<","<<_upperZ<<","
			<<std::endl;
	for (int i = _lowerZ; i < _upperZ; i++)
		for (int j = _lowerY; j <_upperY; j++)
			for (int k = _lowerX; k < _upperX ; k++){

//								_flowField.getVelocity().getVector(k, j, i)[0]=0.0;
//
//								_flowField.getVelocity().getVector(k, j, i)[1]=0.0;
//
//								_flowField.getVelocity().getVector(k, j, i)[2]=0.0;
				interpolateComponentX (k, j, i, 0,velocity_counterX++);
				interpolateComponentY (k, j, i, 1,velocity_counterY++);
				interpolateComponentZ (k, j, i, 2,velocity_counterZ++);
			}
}
void LBNSCouplingIterator::iterateBoundary(){

	// Left and right faces
	int velocity_counterX=0;
	int velocity_counterY=0;
	int velocity_counterZ=0;
	for (int j = _lowerY; j <= _upperY - 1; j++){
		for (int k = _lowerZ; k <= _upperZ - 1; k++){
			// Left face
			interpolateComponentX (_lowerX-1, j, k, 0,velocity_counterX++);
			interpolateComponentY (_lowerX, j, k, 1,velocity_counterY++);
			interpolateComponentZ (_lowerX, j, k, 2,velocity_counterZ++);

			// Right face
			interpolateComponentX (_upperX, j, k, 0,velocity_counterX++);
			interpolateComponentY (_upperX, j, k, 1,velocity_counterY++);
			interpolateComponentZ (_upperX, j, k, 2,velocity_counterZ++);
		}
		// The line not included in the upper side
		interpolateComponentX (_lowerX-1, j, _upperZ, 0,velocity_counterX++);
		interpolateComponentY (_lowerX, j, _upperZ, 1,velocity_counterY++);

		interpolateComponentX (_upperX, j, _upperZ, 0,velocity_counterX++);
		interpolateComponentY (_upperX, j, _upperZ, 1,velocity_counterY++);
	}
	// The line in the other direction
	for (int k = _lowerZ; k <= _upperZ - 1; k++){
		interpolateComponentX (_lowerX-1, _upperY, k, 0,velocity_counterX++);
		interpolateComponentZ (_lowerX, _upperY, k, 2,velocity_counterZ++);

		interpolateComponentX (_upperX, _upperY, k, 0,velocity_counterX++);
		interpolateComponentZ (_upperX, _upperY, k, 2,velocity_counterZ++);
	}
	interpolateComponentX (_lowerX-1, _upperY, _upperZ, 0,velocity_counterX++);
	interpolateComponentX (_upperX, _upperY, _upperZ, 0,velocity_counterX++);
	// There's a point that is written two times. I don't care

	// Top and bottom faces
	for (int k = _lowerZ; k <= _upperZ - 1; k++){
		for (int i = _lowerX + 1; i <= _upperX - 1; i++){
			// Bottom face
			interpolateComponentX (i, _lowerY, k, 0,velocity_counterX++);
			interpolateComponentY (i, _lowerY-1, k, 1,velocity_counterY++);
			interpolateComponentZ (i, _lowerY, k, 2,velocity_counterZ++);

			// Top face
			interpolateComponentX (i, _upperY, k, 0,velocity_counterX++);
			interpolateComponentY (i, _upperY, k, 1,velocity_counterY++);
			interpolateComponentZ (i, _upperY, k, 2,velocity_counterZ++);
		}
	}
	for (int i = _lowerX + 1; i <= _upperX - 1; i++){
		interpolateComponentX (i, _lowerY, _upperZ, 0,velocity_counterX++);
		interpolateComponentY (i, _lowerY-1, _upperZ, 1,velocity_counterY++);

		interpolateComponentX (i, _upperY, _upperZ, 0,velocity_counterX++);
		interpolateComponentY (i, _upperY, _upperZ, 1,velocity_counterY++);
	}

	// Front and back method
	for (int j = _lowerY + 1; j <= _upperY - 1; j++){
		for (int i = _lowerX + 1; i <= _upperX - 1; i++){
			// Front wall
			interpolateComponentX (i, j, _lowerZ, 0,velocity_counterX++);
			interpolateComponentY (i, j, _lowerZ, 1,velocity_counterY++);
			interpolateComponentZ (i, j, _lowerZ-1, 2,velocity_counterZ++);

			// Back wall
			interpolateComponentX (i, j, _upperZ, 0,velocity_counterX++);
			interpolateComponentY (i, j, _upperZ, 1,velocity_counterY++);
			interpolateComponentZ (i, j, _upperZ, 2,velocity_counterZ++);
		}
	}

}

void LBNSCouplingIterator::setLBVelocities(double* velocityX,double* velocityY, double* velocityZ,
		int sizeX,int sizeY,int sizeZ){
	_lbVelocityX.resize(sizeX);
	_lbVelocityY.resize(sizeY);
	_lbVelocityZ.resize(sizeZ);
	for(int i=0;i<sizeX;i++){
		_lbVelocityX[i]=velocityX[i];
	}
	for(int i=0;i<sizeY;i++){
		_lbVelocityY[i]=velocityY[i];
	}
	for(int i=0;i<sizeZ;i++){
		_lbVelocityZ[i]=velocityZ[i];
	}
}
