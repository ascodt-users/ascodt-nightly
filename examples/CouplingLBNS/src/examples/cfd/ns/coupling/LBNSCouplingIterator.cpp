#include "LBNSCouplingIterator.h"
#include "CouplingFunctions.h"
// Required right before the call to interpolate on boundary
void LBNSCouplingIterator::setNormalVector(int nx, int ny, int nz){
	_normalVector[0] = nx;
	_normalVector[1] = ny;
	_normalVector[2] = nz;
}


void LBNSCouplingIterator::interpolateComponent (int i, int j, int k, int component) {
	int localI,localJ,localK;
	if(toLocalIndex(i,j,k,localI,localJ,localK))
		_flowField.getVelocity().getVector(localI,localJ,localK)[component] =
				_interpolator.interpolateVelocityComponent(i, j, k, component);

}


LBNSCouplingIterator::LBNSCouplingIterator(const Parameters & parameters,FlowField & flowField):
						_interpolator(parameters),
						_flowField (flowField), _parameters (parameters),
						_offset (getOverlapWidth (parameters)),

						_lowerX (parameters.coupling.offsetNS[0] + _offset),
						_upperX (parameters.coupling.offsetNS[0] + parameters.coupling.sizeNS[0] - _offset - 1),
						_lowerY (parameters.coupling.offsetNS[1] + _offset),
						_upperY (parameters.coupling.offsetNS[1] + parameters.coupling.sizeNS[1] - _offset - 1),
						_lowerZ (parameters.coupling.offsetNS[2] + _offset),
						_upperZ (parameters.coupling.offsetNS[2] + parameters.coupling.sizeNS[2] - _offset - 1)
{}

inline bool LBNSCouplingIterator::toLocalIndex(const int i,const int j, const int k,int& i_out,int& j_out, int& k_out) const{
	i_out=i-_parameters.parallel.firstCorner[0];
	j_out=j-_parameters.parallel.firstCorner[1];
	k_out=k-_parameters.parallel.firstCorner[2];
	return i_out-2>=0&&j_out-2>=0&&k_out-2>=0&&
			i_out-2<_parameters.parallel.localSize[0]&&
			j_out-2<_parameters.parallel.localSize[1]&&
			k_out-2<_parameters.parallel.localSize[2];
}

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
				interpolateComponent (k, j, i, 0);
				interpolateComponent (k, j, i, 1);
				interpolateComponent (k, j, i, 2);
			}
}

void LBNSCouplingIterator::setVelocity(
		const int key,
		const int offsetX,
		const int offsetY,
		const int offsetZ,
		const int flipsX,
		const int flipsY,
		const int flipsZ,
		const double value){
	_interpolator.setVelocity(
			key,
			offsetX,
			offsetY,
			offsetZ,
			flipsX,
			flipsY,
			flipsZ,
			value);
}
void LBNSCouplingIterator::clear(){
	_interpolator.clear();
}
void LBNSCouplingIterator::iterateBoundary(){

	_interpolator.switchToLocalVelocities();
	for (int j = _lowerY; j <= _upperY - 1; j++){
		for (int k = _lowerZ; k <= _upperZ - 1; k++){
			// Left face
			interpolateComponent (_lowerX-1, j, k,0);
			interpolateComponent (_lowerX, j, k,1);
			interpolateComponent (_lowerX, j, k,2);

			// Right face
			interpolateComponent (_upperX, j, k,0);
			interpolateComponent (_upperX, j, k,1);
			interpolateComponent (_upperX, j, k,2);
		}
		// The line not included in the upper side
		interpolateComponent (_lowerX-1, j, _upperZ,0);
		interpolateComponent (_lowerX, j, _upperZ,1);

		interpolateComponent (_upperX, j, _upperZ,0);
		interpolateComponent (_upperX, j, _upperZ,1);
	}
	// The line in the other direction
	for (int k = _lowerZ; k <= _upperZ - 1; k++){
		interpolateComponent (_lowerX-1, _upperY, k,0);
		interpolateComponent (_lowerX, _upperY, k,2);

		interpolateComponent (_upperX, _upperY, k,0);
		interpolateComponent(_upperX, _upperY, k,2);
	}
	interpolateComponent (_lowerX-1, _upperY, _upperZ,0);
	interpolateComponent (_upperX, _upperY, _upperZ,0);
	// There's a point that is written two times. I don't care

	// Top and bottom faces
	for (int k = _lowerZ; k <= _upperZ - 1; k++){
		for (int i = _lowerX ; i <= _upperX - 1; i++){
			// Bottom face
			interpolateComponent (i, _lowerY, k,0);
			interpolateComponent (i, _lowerY-1, k,1);
			interpolateComponent (i, _lowerY, k,2);

			// Top face
			interpolateComponent (i, _upperY, k,0);
			interpolateComponent (i, _upperY, k,1);
			interpolateComponent(i, _upperY, k,2);
		}
	}
	for (int i = _lowerX ; i <= _upperX - 1; i++){
		interpolateComponent (i, _lowerY, _upperZ,0);
		interpolateComponent (i, _lowerY-1, _upperZ,1);

		interpolateComponent (i, _upperY, _upperZ,0);
		interpolateComponent (i, _upperY, _upperZ,1);
	}
	for (int i = _lowerZ; i <= _upperZ - 1; i++){
		interpolateComponent (_upperX, _lowerY,i,2);
		interpolateComponent (_upperX, _lowerY-1, i,1);

		interpolateComponent (_upperX, _upperY, i,2);
		interpolateComponent (_upperX, _upperY, i,1);
	}

	interpolateComponent (_upperX, _lowerY-1, _upperZ,1);
	interpolateComponent (_upperX, _upperY, _upperZ,1);
	// Front and back method
	for (int j = _lowerY ; j <= _upperY - 1; j++){
		for (int i = _lowerX ; i <= _upperX - 1; i++){
			// Front wall
			interpolateComponent (i, j, _lowerZ,0);
			interpolateComponent (i, j, _lowerZ,1);
			interpolateComponent (i, j, _lowerZ-1,2);

			// Back wall
			interpolateComponent (i, j, _upperZ,0);
			interpolateComponent (i, j, _upperZ,1);
			interpolateComponent (i, j, _upperZ,2);
		}
	}

	for (int i = _lowerY ; i <= _upperY - 1; i++){
		interpolateComponent (_upperX,i, _lowerZ,1);
		interpolateComponent (_upperX, i, _lowerZ-1,2);

		interpolateComponent (_upperX, i, _upperZ,1);
		interpolateComponent (_upperX, i, _upperZ,2);
	}

	for (int i = _lowerX ; i <= _upperX - 1; i++){
		interpolateComponent (i,_upperY, _lowerZ,0);
		interpolateComponent (i,_upperY, _lowerZ-1,2);

		interpolateComponent (i, _upperY, _upperZ,0);
		interpolateComponent (i, _upperY, _upperZ,2);
	}
	interpolateComponent (_upperX, _upperY, _lowerZ-1,2);
	interpolateComponent (_upperX, _upperY, _upperZ,2);




}

void LBNSCouplingIterator::setLBVelocities(double* velocityX,double* velocityY, double* velocityZ,
		int sizeX,int sizeY,int sizeZ){
	//	_lbVelocityX.resize(sizeX);
	//	_lbVelocityY.resize(sizeY);
	//	_lbVelocityZ.resize(sizeZ);
	//	for(int i=0;i<sizeX;i++){
	//		_lbVelocityX[i]=velocityX[i];
	//	}
	//	for(int i=0;i<sizeY;i++){
	//		_lbVelocityY[i]=velocityY[i];
	//	}
	//	for(int i=0;i<sizeZ;i++){
	//		_lbVelocityZ[i]=velocityZ[i];
	//	}
}
