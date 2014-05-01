#include "LBNSRemoteInterpolator.h"
#include "math.h"
#include <sstream>
#include <hash_map>
void LBNSRemoteInterpolator::printParameters() {
	std::cout << "LB -> NS coupling parameters" << std::endl;
	std::cout << "LowerX: " << _lowerX << std::endl;
	std::cout << "UpperX: " << _upperX << std::endl;
	std::cout << "LowerY: " << _lowerY << std::endl;
	std::cout << "UpperY: " << _upperY << std::endl;
	std::cout << "LowerZ: " << _lowerZ << std::endl;
	std::cout << "UpperZ: " << _upperZ << std::endl;
	std::cout << "Ratio: " << _M << std::endl;
	std::cout << "Half M: " << _halfM << std::endl;
	std::cout << "Modulo: " << _modulo << std::endl;
	std::cout << "Reciprocal ratio: " << _reciprocalRatio << std::endl << std::endl;
}


LBNSRemoteInterpolator::LBNSRemoteInterpolator (const Parameters & parameters):
    														_parameters (parameters),
    														// Add 2 to refer to fluid cells and not to the boundaries
    														// The upper limits refer to the last cell inside the overlap region
    														_lowerX (parameters.coupling.offsetNS[0]),
    														_upperX (_lowerX + parameters.coupling.sizeNS[0] - 1),
    														_lowerY (parameters.coupling.offsetNS[1]),
    														_upperY (_lowerY + parameters.coupling.sizeNS[1] - 1),
    														_lowerZ (parameters.coupling.offsetNS[2]),
    														_upperZ (_lowerZ + parameters.coupling.sizeNS[2] - 1),
    														_M (parameters.coupling.ratio),
    														_halfM (_M / 2),    // Should return the floor of the float operation if operating with ints
    														_modulo (_M % 2),
    														_reciprocalRatio (1.0 / _M),
    														_dx (parameters.coupling.refLength / _M),
    														_dt (parameters.lb.viscosity * parameters.flow.Re * _dx * _dx),
    														_referenceVelocity (_dx / _dt)
{
	printParameters();
	for(int i=0;i<3;i++){
		_localVelocitiesCounters[i]=0;
	}
	_open=false;
}

// Location will be provided by two integer arrays. One will define the LB cell where the point is
// contained, and the other will tell if, in each direction, the position of the point is in the
// beginning or the middle. The possible position for points in the grid for this problem is a
// discrete set of points anyway, so, out of preference, I will not use floating point numbers.

void LBNSRemoteInterpolator::locateInLBGrid (int * const lbPosition, int * const middle,
		int ins, int jns, int kns, int component) {

	// At first, locate the point in the center of the NS cell. We will correct later
	lbPosition[0] = _M * (ins - _lowerX) + _halfM + _modulo;
	lbPosition[1] = _M * (jns - _lowerY) + _halfM + _modulo;
	lbPosition[2] = _M * (kns - _lowerZ) + _halfM + _modulo;

	// In this case, the modulo tells if the value is the middle of the cell
	middle[0] = 1 - _modulo;
	middle[1] = 1 - _modulo;
	middle[2] = 1 - _modulo;

	if (component < 3) {    // If we are dealing with a velocity component, there are more steps
		lbPosition[component] += _halfM;    // Move it to the upper end
		middle[component] = 1;  // In this direction, it will always lie on the edge
	} // Notice that we might rewrite values. This kills performance, right?
}

void LBNSRemoteInterpolator::setVelocity(
		const int key,
		const int offsetX,
		const int offsetY,
		const int offsetZ,
		const int flipsX,
		const int flipsY,
		const int flipsZ,
		const double value){
	LBNSData data;
	data.value=value;
	data.offset[0]=offsetX;
	data.offset[1]=offsetY;
	data.offset[2]=offsetZ;
	data.flip[0]=flipsX;
	data.flip[1]=flipsY;
	data.flip[2]=flipsZ;
	_velocities[key].push_back(data);
}
void LBNSRemoteInterpolator::clear(){
	_velocities.clear();
//	for(int i=0;i<3;i++){
//		_localVelocities[i].clear();
//		_localVelocitiesCounters[i]=0;
//	}
}
inline int LBNSRemoteInterpolator::index2array ( int i, int j, int k, int component, int stencil ) const {

	// Check that the indexes are within bounds
	int sizeX=_parameters.geometry.sizeX+3;
	int sizeY=_parameters.geometry.sizeY+3;
	int sizeZ=_parameters.geometry.sizeZ+3;
	assertion ( ( i < sizeX ) && ( j < sizeY ) && ( k < sizeZ ) );
	assertion ( ( i >= 0 ) && ( j >= 0 ) && ( k >= 0 )  );

	return  (3*stencilSize * ( i + ( j * sizeX ) + ( k * sizeY * sizeX ) ))+component*stencilSize+stencil;
}
void LBNSRemoteInterpolator::loadVelocityComponent (
		int i,int j,int k,const int & component){
	for (int l = 0; l < stencilSize; l++){
		_values[l] = getVelocity(i,j,k,l,component,_offset,_flip,index2array(i,j,k,component,l));
	}
}



const double  LBNSRemoteInterpolator::getVelocity(
		const int i, const int j, const int k,const int l,
		const int component,
		const int* offset,
		const int* flip,
		const int index){
	//if(!_velocities[component].empty()){
		__gnu_cxx::hash_map<int,std::vector<LBNSData> >::iterator it=_velocities.find(index);
		if(it!=_velocities.end()){

			for(unsigned int i=0;i<(*it).second.size();i++){
				if(
						offset[0]==(*it).second[i].offset[0]&&
						offset[1]==(*it).second[i].offset[1]&&
						offset[2]==(*it).second[i].offset[2]&&
						flip[0]==(*it).second[i].flip[0]&&
						flip[1]==(*it).second[i].flip[1]&&
						flip[2]==(*it).second[i].flip[2]
				){
					//_localVelocities[component].push_back((*it).second[i].value);

					return (*it).second[i].value;
				}
			}

		}
//		open();
		//	open();
		//
//		_logComm<<"i_j_k_index:"<<i
//				<<" "<<j<<" "<<k
//				<<" stencil:"<<l
//				<<" component:"<<component
//				<<" index:"<<index<<std::endl;

		//std::cout<<"index not found"<<std::endl;
		return 0.0;
	//}
//	else{
//		return _localVelocities[component][_localVelocitiesCounters[component]++];
//	}
}
bool LBNSRemoteInterpolator::checkIfValid (const int * const lbPosition, const int * const middle) {
	return true;
}

void LBNSRemoteInterpolator::setArrays (const int * const lbPosition, const int * const middle){
	int cellX= _parameters.coupling.sizeNS[0] * _parameters.coupling.ratio + 1;
	int cellY= _parameters.coupling.sizeNS[1] * _parameters.coupling.ratio + 1;
	int cellZ= _parameters.coupling.sizeNS[2] * _parameters.coupling.ratio + 1;

	if (lbPosition[0] < cellX / 2){
		_flip[0] = 1;
	} else {
		_flip[0] = -1;
	}
	if (lbPosition[1] < cellY / 2){
		_flip[1] = 1;
	} else {
		_flip[1] = -1;
	}
	if (lbPosition[2] < cellZ / 2){
		_flip[2] = 1;
	} else {
		_flip[2] = -1;
	}


	// With the flip set, we proceed to compute offsets and regularized positions.
	for (int l = 0; l < 3; l++){
		if (_flip[l] == 1) {
			_offset[l] = lbPosition[l] - 1 + middle[l];
		} else {    // If the stencil was flipped in this direction
			_offset[l] = lbPosition[l];
		}
		// This one is easy to see. If the point is not sitting directly on one of the cells in one
		// direction, it has to be in the position 0.5
		_regularizedPosition[l] = 0.5 * (double)(1 - middle[l]);
	}
}
void LBNSRemoteInterpolator::open(){
//	if(!_open){
//		std::stringstream fileName;
//		fileName<<"log_lbns_receiver."<<_parameters.parallel.rank<<".txt";
//		_logComm.open(fileName.str().c_str());
//	}
//	_open=true;
}
void LBNSRemoteInterpolator::switchToLocalVelocities(){
//	for(int i=0;i<3;i++){
//		if(_localVelocities[i].size()==0)
//				_localVelocities[i].reserve(_velocities[i].size());
//			else
//				_velocities[i].clear();
//		_localVelocitiesCounters[i]=0;
//	}
}
FLOAT LBNSRemoteInterpolator::interpolateVelocityComponent (int ins, int jns, int kns, int component){
	int lbPosition[3], middle[3];
	locateInLBGrid (lbPosition, middle, ins, jns, kns, component);
	if (!checkIfValid (lbPosition, middle)){
		std::cerr << "Trying to interpolate position " << ins << ", " << jns << ", " << kns <<
				std::endl;
		handleError (1,"Position cannot be interpolated");
	}

	// The velocities will never lie in the very center of a LB cell, so there's no need to check.

	setArrays (lbPosition, middle);
	loadVelocityComponent (ins,jns,kns,component);
	getLocationVector (_locationVector, _regularizedPosition);
	matrix_vector(barycentricBasis, _locationVector, _weights, stencilSize, stencilSize);
	return dot(_values, _weights, stencilSize) * _referenceVelocity;
}



/*FLOAT LBNSRemoteInterpolator::interpolatePressure (int ins, int jns, int kns) {
	int lbPosition[3], middle[3];
	locateInLBGrid (lbPosition, middle, ins, jns, kns, 3);
	std::cout << lbPosition[0] << ", " << lbPosition[1] << ", " << lbPosition[2] << std::endl;
	if (!checkIfValid (lbPosition, middle)){
		std::cerr << "Trying to interpolate position " << ins << ", " << jns << ", " << kns <<
				std::endl;
		handleError (1,"Position cannot be interpolated");
	}

	if (middle[0] == 1 && middle[1] == 1 && middle[2] == 1) {   // If we're standing on a LB cell
		// there is no need to interpolate. Can only happen for pressure
		return _lbField.getDensity (_lbField.getFOut(), lbPosition[0], lbPosition[1],lbPosition[2]);
	}

	setArrays (lbPosition, middle);
	loadDensity(ins,jns,kns);
	getLocationVector (_locationVector, _regularizedPosition);
	matrix_vector(barycentricBasis, _locationVector, _weights, stencilSize, stencilSize);
	return dot(_values, _weights, stencilSize);
}*/
