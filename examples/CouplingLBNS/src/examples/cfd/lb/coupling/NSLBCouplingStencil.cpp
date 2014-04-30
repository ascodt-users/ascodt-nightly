#include "NSLBCouplingStencil.h"
#include <math.h>
#include <sstream>
void checkConsistency (const LBField & lbField, int nsLowX, int nsHighX, int nsLowY,
		int nsHighY, int nsLowZ, int nsHighZ,
		int M){
	if ((lbField.getCellsX()-1) % (nsHighX - nsLowX + 1) ||
			(lbField.getCellsX()-1) / (nsHighX - nsLowX + 1) != M ||
			(lbField.getCellsY()-1) % (nsHighY - nsLowY + 1) ||
			(lbField.getCellsY()-1) / (nsHighY - nsLowY + 1) != M ||
			(lbField.getCellsZ()-1) % (nsHighZ - nsLowZ + 1) ||
			(lbField.getCellsZ()-1) / (nsHighZ - nsLowZ + 1) != M){
		handleError (1, "Inconsistency in the size of the region")
	}
}

inline void NSLBCouplingStencil::toGlobalIndex(const int i,const int j, const int k,int& i_out,int& j_out, int& k_out) const{
	i_out=i+_parameters.parallel.firstCorner[0];
	j_out=j+_parameters.parallel.firstCorner[1];
	k_out=k+_parameters.parallel.firstCorner[2];
}

void NSLBCouplingStencil::printParameters (){
	//	std::cout << "NS -> LB coupling parameters:" << std::endl;
	//	std::cout << "M: " << _M << std::endl;
	//	std::cout << "dx: " << _dx << std::endl;
	//	std::cout << "dt: " << _dt << std::endl;
	//	std::cout << "Low X: "  << _nsLowX  << std::endl;
	//	std::cout << "High X: " << _nsHighX << std::endl;
	//	std::cout << "Low Y: "  << _nsLowY  << std::endl;
	//	std::cout << "High Y: " << _nsHighY << std::endl;
	//	std::cout << "Low Z: "  << _nsLowZ  << std::endl;
	//	std::cout << "High Z: " << _nsHighZ << std::endl;
	//	std::cout << "velocity: " << 1.0 / _reciprocalVelocityLB << std::endl << std::endl;
}

NSLBCouplingStencil::NSLBCouplingStencil (const Parameters & parameters,
		LBField & lbField,
		int nsLowX, int nsHighX,
		int nsLowY, int nsHighY,
		int nsLowZ, int nsHighZ) :
    																																								GlobalBoundaryStencil<LBField> (parameters), _lbField (lbField),
    																																								_nsLowX (nsLowX), _nsHighX (nsHighX),
    																																								_nsLowY (nsLowY), _nsHighY (nsHighY),
    																																								_nsLowZ (nsLowZ), _nsHighZ (nsHighZ),
    																																								_nsSizeX(_nsHighX - _nsLowX + 1),
    																																								_nsSizeY(_nsHighY - _nsLowY + 1),
    																																								_nsSizeZ(_nsHighZ - _nsLowZ + 1),
    																																								_M (lbField.getCellsX() / (_nsHighX - nsLowX + 1)),
    																																								_floatM ((FLOAT)_M),
    																																								_reciprocalM (1.0 / _floatM),
    																																								_dx (parameters.coupling.refLength / _M),
    																																								_dt (parameters.lb.viscosity * parameters.flow.Re * _dx * _dx),
    																																								_reciprocalVelocityLB (_dt / _dx)

    																																								{
	// Check if the sizes selected are consistent with the ratio between LB and NS

	if (parameters.coupling.set) {  // We only care about this if the coupling is to happen
		checkConsistency (lbField, nsLowX, nsHighX, nsLowY, nsHighY, nsLowZ, nsHighZ, _M);
	}
	printParameters();
	//_open=false;
	//_logComm.open("log_nslb_receiver.txt");

    																																								}

NSLBCouplingStencil::NSLBCouplingStencil (const Parameters & parameters,
		LBField & lbField) :
																									GlobalBoundaryStencil<LBField> (parameters), _lbField (lbField),
																									_nsLowX  (parameters.coupling.offsetNS[0]),
																									_nsHighX (parameters.coupling.offsetNS[0] + parameters.coupling.sizeNS[0] - 1),
																									_nsLowY  (parameters.coupling.offsetNS[1]),
																									_nsHighY (parameters.coupling.offsetNS[1] + parameters.coupling.sizeNS[1] - 1),
																									_nsLowZ  (parameters.coupling.offsetNS[2]),
																									_nsHighZ (parameters.coupling.offsetNS[2] + parameters.coupling.sizeNS[2] - 1),
																									_nsSizeX(_nsHighX - _nsLowX + 1),
																									_nsSizeY(_nsHighY - _nsLowY + 1),
																									_nsSizeZ(_nsHighZ - _nsLowZ + 1),
																									_M (parameters.coupling.ratio),
																									_floatM ((FLOAT)_M),
																									_reciprocalM (1.0 / _floatM),
																									_dx (parameters.coupling.refLength / _M),
																									_dt (parameters.lb.viscosity * parameters.flow.Re * _dx * _dx),
																									_reciprocalVelocityLB (_dt / _dx)
																									{
	if (parameters.coupling.set) {  // We only care about this if the coupling is to happen
		checkConsistency (lbField, parameters.coupling.offsetNS[0],
				parameters.coupling.offsetNS[0] + parameters.coupling.sizeNS[0] - 1,
				parameters.coupling.offsetNS[1],
				parameters.coupling.offsetNS[1] + parameters.coupling.sizeNS[1] - 1,
				parameters.coupling.offsetNS[2],
				parameters.coupling.offsetNS[2] + parameters.coupling.sizeNS[2] - 1,
				parameters.coupling.ratio);
	}
	printParameters();
	//_open=false;
	//_logComm.open("log_nslb_receiver.txt");
																									}


NSLBCouplingStencil::~NSLBCouplingStencil() {
}

//void NSLBCouplingStencil::open(){
//	if(!_open){
//		std::stringstream fileName;
//		fileName<<"log_nslb_receiver."<<_parameters.parallel.rank<<".txt";
//		_logComm.open(fileName.str().c_str());
//	}
//
//	_open=true;
//}
const FLOAT NSLBCouplingStencil::getDx() const{
	return _dx;
}


const FLOAT NSLBCouplingStencil::getDt() const{
	return _dt;
}

const double  NSLBCouplingStencil::getVelocity(
		int i,int j,int k,int l,
		const int component,const int* offset,const int* flip,const int index){
	__gnu_cxx::hash_map<int,std::vector<NSLBData> >::iterator it=_velocities[component].find(index);
	if(it!=_velocities[component].end()){
		for(unsigned int i=0;i<(*it).second.size();i++){
			if(
					offset[0]==(*it).second[i].offset[0]&&
					offset[1]==(*it).second[i].offset[1]&&
					offset[2]==(*it).second[i].offset[2]&&
					flip[0]==(*it).second[i].flip[0]&&
					flip[1]==(*it).second[i].flip[1]&&
					flip[2]==(*it).second[i].flip[2]
			)
				return (*it).second[i].value;
		}

	}
	return 0.0;
}

const double  NSLBCouplingStencil::getPressure(
		int i,int j,int k,int l,
		const int* offset,
		const int* flip,
		const int index) {

	__gnu_cxx::hash_map<int,std::vector<NSLBData> >::iterator it=_pressure.find(index);
	if(it!=_pressure.end())
		for(unsigned int i=0;i<(*it).second.size();i++){
			if(
					offset[0]==(*it).second[i].offset[0]&&
					offset[1]==(*it).second[i].offset[1]&&
					offset[2]==(*it).second[i].offset[2]&&
					flip[0]==(*it).second[i].flip[0]&&
					flip[1]==(*it).second[i].flip[1]&&
					flip[2]==(*it).second[i].flip[2]
			)
				return (*it).second[i].value;
		}

	return 0.0;

}

inline int NSLBCouplingStencil::index2Varray ( int i, int j, int k, int component, int stencil ) const {

	// Check that the indexes are within bounds
	int sizeX=_parameters.geometry.sizeX+3;
	int sizeY=_parameters.geometry.sizeY+3;
	int sizeZ=_parameters.geometry.sizeZ+3;
	assertion ( ( i < sizeX ) && ( j < sizeY ) && ( k < sizeZ ) );
	assertion ( ( i >= 0 ) && ( j >= 0 ) && ( k >= 0 )  );

	return  (3*stencilSize * ( i + ( j * sizeX ) + ( k * sizeY * sizeX ) ))+component*stencilSize+stencil;
}
inline int NSLBCouplingStencil::index2Parray ( int i, int j, int k, int stencil ) const {

	// Check that the indexes are within bounds
	int sizeX=_parameters.geometry.sizeX+3;
	int sizeY=_parameters.geometry.sizeY+3;
	int sizeZ=_parameters.geometry.sizeZ+3;
	assertion ( ( i < sizeX ) && ( j < sizeY ) && ( k < sizeZ ) );
	assertion ( ( i >= 0 ) && ( j >= 0 ) && ( k >= 0 )  );

	return  (stencilSize * ( i + ( j * sizeX ) + ( k * sizeX * sizeY ) ))+stencil;
}
void NSLBCouplingStencil::loadVelocity(
		const int i,const int j,const int k,
		const int* offset,
		const int* flip,
		const int component){

	for (int l = 0; l < stencilSize; l++){
		//		_logComm<<"i_j_k_index:"<<i
		//					<<" "<<j<<" "<<k
		//					<<" stencil:"<<l
		//					<<" component:"<<component
		//					<<" index:"<<index2Varray(i,j,k,component,l)
		//					<<" value:"<< _velocities[component][index2Varray(i,j,k,component,l)]<<std::endl;
		_values[l] = getVelocity(i,j,k,l,component,offset,flip,index2Varray(i,j,k,component,l));

		//_velocities[component][index2Varray(i,j,k,component,l)];

	}
}


void NSLBCouplingStencil::setVelocityComponent(
		const int key,
		const int component,
		const int offsetX,
		const int offsetY,
		const int offsetZ,
		const int flipX,
		const int flipY,
		const int flipZ,
		const double value){
	NSLBData data;
	data.value=value;
	data.offset[0]=offsetX;
	data.offset[1]=offsetY;
	data.offset[2]=offsetZ;
	data.flip[0]=flipX;
	data.flip[1]=flipY;
	data.flip[2]=flipZ;
	_velocities[component][key].push_back(data);
}
void NSLBCouplingStencil::setPressure(
		const int key,
		const int offsetX,
		const int offsetY,
		const int offsetZ,
		const int flipX,
		const int flipY,
		const int flipZ,
		const double value){
	//open();
	NSLBData data;
	data.value=value;
	data.offset[0]=offsetX;
	data.offset[1]=offsetY;
	data.offset[2]=offsetZ;
	data.flip[0]=flipX;
	data.flip[1]=flipY;
	data.flip[2]=flipZ;
	_pressure[key].push_back(data);
}
void NSLBCouplingStencil::clear(){
	_velocities[0].clear();
	_velocities[1].clear();
	_velocities[2].clear();
	_pressure.clear();
	//_logComm.flush();
}


void NSLBCouplingStencil::loadPressure(
		const int i,const int j,const int k,
		const int* offset,
		const int* flip

){
	for (int l = 0; l < stencilSize; l++){
		_values[l] = getPressure(i,j,k,l,offset,flip,index2Parray(i,j,k,l));
	}
}

FLOAT NSLBCouplingStencil::interpolatePressure (int i, int j, int k, const int * const flip) {
	int ins, jns, kns,iGlobal,jGlobal,kGlobal;  // Cell in the NS solver
	int offset[3] = {0, 0, 0};    // An offset is unnecessary when dealing with the pressure
	FLOAT position[3], regularizedPosition[3], locationVector[stencilSize];

	//toGlobalIndex(i,j,k,iGlobal,jGlobal,kGlobal);
	identifyCellAndPosition(ins, jns, kns, position,i,j,k);

	FLOAT weights[stencilSize];     // Intermediate step during the interpolation

	setRPositionOffset (regularizedPosition, offset, flip, position, 0);
	setRPositionOffset (regularizedPosition, offset, flip, position, 1);
	setRPositionOffset (regularizedPosition, offset, flip, position, 2);

	getLocationVector (locationVector, regularizedPosition);
	loadPressure(i,j,k,offset,flip);

	matrix_vector(barycentricBasis, locationVector, weights, stencilSize, stencilSize);

	return dot(_values, weights, stencilSize);
}

FLOAT NSLBCouplingStencil::computeBoundaryMeanPressure (){
	FLOAT accumulator = 0;
	int cellsX= _parameters.coupling.sizeNS[0] * _parameters.coupling.ratio + 1;
	int cellsY= _parameters.coupling.sizeNS[1] * _parameters.coupling.ratio + 1;
	int cellsZ= _parameters.coupling.sizeNS[2] * _parameters.coupling.ratio + 1;

	// Left and right
	_flip[0] = -1; _flip[1] = 1; _flip[2] = 1;
	for (int j = 0; j < cellsY; j++){
		for (int k = 0; k < cellsZ; k++){
			accumulator += interpolatePressure(0, j, k, _flip);
		}
	}
	_flip[0] = 1; _flip[1] = 1; _flip[2] = 1;
	for (int j = 0; j < cellsY; j++){
		for (int k = 0; k < cellsZ; k++){
			accumulator += interpolatePressure(cellsX-1, j, k, _flip);
		}
	}

	// Top and bottom
	_flip[0] = 1; _flip[1] = -1; _flip[2] = 1;
	for (int i = 1; i < cellsX-1; i++){
		for (int k = 0; k < cellsZ; k++){
			accumulator += interpolatePressure(i, 0, k, _flip);
		}
	}
	_flip[0] = 1; _flip[1] = 1; _flip[2] = 1;
	for (int i = 1; i < cellsX-1; i++){
		for (int k = 0; k <cellsZ; k++){
			accumulator += interpolatePressure(i,cellsY-1, k, _flip);
		}
	}

	// Front and back
	_flip[0] = 1; _flip[1] = 1; _flip[2] = 1;
	for (int i = 1; i < cellsX-1; i++){
		for (int j = 1; j <cellsY-1; j++){
			accumulator += interpolatePressure(i, j, 0, _flip);
		}
	}
	_flip[0] = 1; _flip[1] = 1; _flip[2] = -1;
	for (int i = 1; i < cellsX-1; i++){
		for (int j = 1; j < cellsY-1; j++){
			accumulator += interpolatePressure(i, j, cellsZ-1, _flip);
		}
	}

	accumulator /= (2 * cellsY* cellsZ) +
			(2 * (cellsX-2) * cellsZ) +
			(2 * (cellsX-2) * (cellsY-2));

	setMeanPressure(accumulator);
	return accumulator;
}



// From the indexes of a cell in the LB grid, get the indexes and position in the NS grid
void NSLBCouplingStencil::identifyCellAndPosition (int & ins, int & jns, int & kns,
		FLOAT * const position, int i, int j, int k){

	// With this operations, the region related to a cell will be closed on the lower boundaries
	// and open on the upper boundaries.
	ins = _nsLowX + (i / _M);
	jns = _nsLowY + (j / _M);
	kns = _nsLowZ + (k / _M);

	position[0] = (i % _M) * _reciprocalM;
	position[1] = (j % _M) * _reciprocalM;
	position[2] = (k % _M) * _reciprocalM;
}

// To be used inside the next function. Sets transformed position and offset vectors.
void NSLBCouplingStencil::setRPositionOffset(FLOAT * const transformedPosition, int * const offset,
		const int * const flip, const FLOAT * const position,
		int component){
	if (flip[component] == 1){
		if (position[component] >= 0.5){
			transformedPosition[component] = position[component] - 0.5;
			offset[component] = 0;
		} else {
			transformedPosition[component] = 0.5 + position[component];
			offset[component] = -1;
		}
	} else { // Assumes that it can only be -1 and saves a comparison
		if (position[component] >= 0.5){
			transformedPosition[component] = 1.5 - position[component];
			offset[component] = 1;
		} else {
			transformedPosition[component] = 0.5 - position[component];
			offset[component] = 0;
		}
	}
}

// To use with values in the edges, that is, velocity components
void NSLBCouplingStencil::setRPositionOffsetPrincipal (FLOAT * const transformedPosition,
		int * const offset, const int * const flip,
		const FLOAT * const position,
		int component){
	// In the case of setting the same component for the arrays and the velocity, we deal with
	// values at the edges of the cell. If there is no flip, the position doesn't change, and
	// instead we take a value from the lower cell, which is the value at the lower boundary of
	// this cell. Otherwise, we take this cell as origin, and measure the location as the distance
	// to the upper edge.
	if (flip[component] == 1){
		offset[component] = -1;
		transformedPosition[component] = position[component];
	} else if (flip[component] == -1) {
		offset[component] = 0;
		transformedPosition[component] = 1.0 - position[component];
	} else {
		handleError (1, "Trying to work with an invalid flip condition");
	}
}


void NSLBCouplingStencil::setArrays (int * const offset, FLOAT * const locationVector,
		FLOAT * const dxVector, FLOAT * const dyVector, FLOAT * const dzVector,
		const int * const flip, const FLOAT * const position, int component){

	//! If a stencil is flipped, the point will have changed position with respect with to the
	// "canonical" stencil. This is the position from the point of view of the C stencil. Notice
	// that this point HAS to be in the convex shell of the stencil
	FLOAT transformedPosition[3];

	int theOtherComponents[2];  // The components of the velocity that are not being interpolated

	if (component == 3){    // If dealing with the pressure, we adjust in all directions
		setRPositionOffset (transformedPosition, offset, flip, position, 0);
		setRPositionOffset (transformedPosition, offset, flip, position, 1);
		setRPositionOffset (transformedPosition, offset, flip, position, 2);

	} else {    // If dealing with the velocities, we adjust in all directions but one

		if (component == 0){    // X. Won't bother with enumerations here
			theOtherComponents[0] = 1;
			theOtherComponents[1] = 2;
		} else if (component == 1){
			theOtherComponents[0] = 0;
			theOtherComponents[1] = 2;
		} else {    // Possibility of being the pressure eliminated
			theOtherComponents[0] = 0;
			theOtherComponents[1] = 1;
		}

		setRPositionOffsetPrincipal (transformedPosition, offset, flip, position, component);
		setRPositionOffset (transformedPosition, offset, flip, position, theOtherComponents[0]);
		setRPositionOffset (transformedPosition, offset, flip, position, theOtherComponents[1]);
	}

	// Finally, get all location information
	getLocationVector (locationVector, transformedPosition);
	getDerCoefficientVector (dxVector, dyVector, dzVector, transformedPosition, flip);
}


// 2D functions. Not used
void NSLBCouplingStencil::applyLeftWall   ( LBField & lbField, int i, int j ){}
void NSLBCouplingStencil::applyRightWall  ( LBField & lbField, int i, int j ){}
void NSLBCouplingStencil::applyBottomWall ( LBField & lbField, int i, int j ){}
void NSLBCouplingStencil::applyTopWall    ( LBField & lbField, int i, int j ){}


void NSLBCouplingStencil::interpolate (int i, int j, int k, const int * const flip){
	int ins, jns, kns,iGlobal,jGlobal,kGlobal;  // NS cell
	int offset[3];
	FLOAT position[3], locationVector[stencilSize];
	FLOAT dxVector[stencilSize], dyVector[stencilSize], dzVector[stencilSize];

	FLOAT velocity[3], jacobian[9], density;    // Storage for interpolated quantities

	FLOAT weights[stencilSize];     // Intermediate step during the interpolation
	toGlobalIndex(i,j,k,iGlobal,jGlobal,kGlobal);
	//std::cout<<"i_j_k2global:"<<i<<","<<j<<","<<k<<","<<iGlobal<<","<<jGlobal<<","<<kGlobal<<std::endl;
	identifyCellAndPosition(ins, jns, kns, position, iGlobal, jGlobal, kGlobal);

	// Pressure is represented as a fourth component with index 3

	for (int component = 0; component < 3; component++){
		setArrays (offset, locationVector, dxVector, dyVector,  dzVector,
				flip, position, component);
		loadVelocity(iGlobal,jGlobal,kGlobal,offset,flip,component);

		matrix_vector(barycentricBasis, locationVector, weights, stencilSize, stencilSize);
		velocity[component] = dot(_values, weights, stencilSize) * _reciprocalVelocityLB;

		matrix_vector(barycentricBasis, dxVector, weights, stencilSize, stencilSize);
		jacobian[3 * component] = dot(_values, weights, stencilSize) * _reciprocalVelocityLB *
				_reciprocalM;

		matrix_vector(barycentricBasis, dyVector, weights, stencilSize, stencilSize);
		jacobian[3 * component + 1] = dot(_values, weights, stencilSize) * _reciprocalVelocityLB *
				_reciprocalM;

		matrix_vector(barycentricBasis, dzVector, weights, stencilSize, stencilSize);
		jacobian[3 * component + 2] = dot(_values, weights, stencilSize) * _reciprocalVelocityLB *
				_reciprocalM;
	}

	setArrays (offset, locationVector, dxVector, dyVector,  dzVector, flip, position, 3);
	loadPressure(iGlobal,jGlobal,kGlobal,offset,flip);
	matrix_vector(barycentricBasis, locationVector, weights, stencilSize, stencilSize);
	// 0 mean pressure
	_meanPressure=0.0;
	density = (dot(_values, weights, stencilSize) - _meanPressure) *
			_reciprocalVelocityLB  * _reciprocalVelocityLB * 3.0 + 1.0;

	FLOAT eq[Q], neq[Q];
	computeEquilibrium(eq, density, velocity);
	computeMinimumNonEquilibrium(neq, _parameters.lb.tau, density,
			jacobian[0], jacobian[1], jacobian[2],
			jacobian[3], jacobian[4], jacobian[5],
			jacobian[6], jacobian[7], jacobian[8]);
	if(_parameters.parallel.rank==1)
		for (int l = 0; l < Q; l++){
			_lbField.getFIn() [_lbField.getIndexF(l, i, j, k)] = eq[l] + (1.0 - 1.0/_parameters.lb.tau) * neq[l];
			_lbField.getFOut()[_lbField.getIndexF(l, i, j, k)] = eq[l] + (1.0 - 1.0/_parameters.lb.tau) * neq[l];
		}
	else
		for (int l = 0; l < Q; l++){
			_lbField.getFIn() [_lbField.getIndexF(l, i, j, k)] = eq[l] + (1.0 - 1.0/_parameters.lb.tau) * neq[l];
			_lbField.getFOut()[_lbField.getIndexF(l, i, j, k)] = eq[l] + (1.0 - 1.0/_parameters.lb.tau) * neq[l];
		}
}

FLOAT NSLBCouplingStencil::interpolateVelocityComponent (const int * const cell,
		const FLOAT * const position,
		int component, const int * const flip){
	/*int offset[3];
	FLOAT locationVector[stencilSize];

	FLOAT dxVector[stencilSize], dyVector[stencilSize], dzVector[stencilSize];

	FLOAT weights[stencilSize];     // Intermediate step during the interpolation

	setArrays (offset, locationVector, dxVector, dyVector,  dzVector,
			flip, position, component);

	//loadVelocity(component);

	matrix_vector(barycentricBasis, locationVector, weights, stencilSize, stencilSize);
	return dot(_values, weights, stencilSize) * _reciprocalVelocityLB;
	 */
}

FLOAT NSLBCouplingStencil::getReciprocalVelocity () const {
	return _reciprocalVelocityLB;
}

void NSLBCouplingStencil::setMeanPressure (const FLOAT & pressure) {
	_meanPressure = pressure;
}


void NSLBCouplingStencil::applyLeftWall   ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns,iGlobal,jGlobal,kGlobal;
	FLOAT position[3];
	toGlobalIndex(i,j,k,iGlobal,jGlobal,kGlobal);
	identifyCellAndPosition (ins, jns, kns, position, iGlobal,jGlobal,kGlobal);
	// Enforce symmetry of the application of the stencil. It is applied in the same way in the
	// other operations
	if ((jns - _nsLowY) < _nsSizeY / 2) _flip[1] = 1;
	else                                _flip[1] = -1;
	if ((kns - _nsLowZ) < _nsSizeZ / 2) _flip[2] = 1;
	else                                _flip[2] = -1;
	_flip[0] = -1;
	interpolate(i, j, k, _flip);
}

void NSLBCouplingStencil::applyRightWall  ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns,iGlobal,jGlobal,kGlobal;
	FLOAT position[3];
	toGlobalIndex(i,j,k,iGlobal,jGlobal,kGlobal);
	identifyCellAndPosition (ins, jns, kns, position, iGlobal,jGlobal,kGlobal);
	if ((jns - _nsLowY) < _nsSizeY / 2) _flip[1] = 1;
	else                                _flip[1] = -1;
	if ((kns - _nsLowZ) < _nsSizeZ / 2) _flip[2] = 1;
	else                                _flip[2] = -1;
	_flip[0] = 1;
	interpolate(i, j, k, _flip);
}

void NSLBCouplingStencil::applyBottomWall ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns,iGlobal,jGlobal,kGlobal;
	FLOAT position[3];
	toGlobalIndex(i,j,k,iGlobal,jGlobal,kGlobal);
	identifyCellAndPosition (ins, jns, kns, position,iGlobal,jGlobal,kGlobal);
	if ((ins - _nsLowX) < _nsSizeX / 2) _flip[0] = 1;
	else                                _flip[0] = -1;
	if ((kns - _nsLowZ) < _nsSizeZ / 2) _flip[2] = 1;
	else                                _flip[2] = -1;
	_flip[1] = -1;
	//	if(_parameters.parallel.rank==1)
	//		std::cout<<"iterating bottm wall:"<<i<<","<<j<<","<<k<<std::endl;
	interpolate(i, j, k, _flip);
}

void NSLBCouplingStencil::applyTopWall    ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns,iGlobal,jGlobal,kGlobal;
	FLOAT position[3];
	toGlobalIndex(i,j,k,iGlobal,jGlobal,kGlobal);
	identifyCellAndPosition (ins, jns, kns, position, iGlobal,jGlobal,kGlobal);
	if ((ins - _nsLowX) < _nsSizeX / 2) _flip[0] = 1;
	else                                _flip[0] = -1;
	if ((kns - _nsLowZ) < _nsSizeZ / 2) _flip[2] = 1;
	else                                _flip[2] = -1;
	_flip[1] = 1;
	interpolate(i, j, k, _flip);
	//	if(_parameters.parallel.rank==1)
	//		std::cout<<"iterating top wall:"<<i<<","<<j<<","<<k<<std::endl;
}

void NSLBCouplingStencil::applyFrontWall  ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns,iGlobal,jGlobal,kGlobal;
	FLOAT position[3];
	toGlobalIndex(i,j,k,iGlobal,jGlobal,kGlobal);
	identifyCellAndPosition (ins, jns, kns, position,iGlobal,jGlobal,kGlobal);
	if ((ins - _nsLowX) < _nsSizeX / 2) _flip[0] = 1;
	else                                _flip[0] = -1;
	if ((jns - _nsLowY) < _nsSizeY / 2) _flip[1] = 1;
	else                                _flip[1] = -1;
	_flip[2] = -1;
	interpolate(i, j, k, _flip);
	//	if(_parameters.parallel.rank==1)
	//		std::cout<<"iterating front wall:"<<i<<","<<j<<","<<k<<std::endl;
}

void NSLBCouplingStencil::applyBackWall   ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns,iGlobal,jGlobal,kGlobal;
	FLOAT position[3];
	toGlobalIndex(i,j,k,iGlobal,jGlobal,kGlobal);
	identifyCellAndPosition (ins, jns, kns, position, iGlobal,jGlobal,kGlobal);
	if ((ins - _nsLowX) < _nsSizeX / 2) _flip[0] = 1;
	else                                _flip[0] = -1;
	if ((jns - _nsLowY) < _nsSizeY / 2) _flip[1] = 1;
	else                                _flip[1] = -1;
	_flip[2] = 1;
	interpolate(i, j, k, _flip);
	//	if(_parameters.parallel.rank==1)
	//		std::cout<<"iterating back wall:"<<i<<","<<j<<","<<k<<std::endl;
}
