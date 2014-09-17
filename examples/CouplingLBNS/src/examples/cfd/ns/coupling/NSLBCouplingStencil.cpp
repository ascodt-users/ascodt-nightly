#include "NSLBCouplingStencil.h"
#include <math.h>
#include "NSLBCommunicator.h"
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

inline bool NSLBCouplingStencil::convertToLocalCoordinates(
		const int i_in,
		const int j_in,
		const int k_in,
		int& i_out,
		int& j_out,
		int& k_out) const {
	i_out=i_in-_parameters.parallel.firstCorner[0];
	j_out=j_in-_parameters.parallel.firstCorner[1];
	k_out=k_in-_parameters.parallel.firstCorner[2];
	//}
	//std::cout<<"converting:"<<i_in<<","<<j_in<<","<<k_in<<"conv:"<<i_out<<","<<j_out<<","<<k_out<<std::endl;
	return i_out-2>=0&&j_out-2>=0&&k_out-2>=0&&
			i_out-2<_parameters.parallel.localSize[0]&&
			j_out-2<_parameters.parallel.localSize[1]&&
			k_out-2<_parameters.parallel.localSize[2];
}

std::vector<double>& NSLBCouplingStencil::getCouplingData(){
	return _communicators[0]->getCouplingData();
}
std::vector<double>& NSLBCouplingStencil::getSecondaryCouplingData(){
	return _communicators[0]->getSecondaryCouplingData();
}
NSLBCouplingStencil::NSLBCouplingStencil (const Parameters & parameters,
		LBField & lbField, FlowField & nsField,
		int nsLowX, int nsHighX,
		int nsLowY, int nsHighY,
		int nsLowZ, int nsHighZ) :
									SmartGlobalBoundaryStencil<LBField> (parameters), _lbField (lbField), _nsField (nsField),
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
									//			_jacobian(jacobian),
									//			_pressure(pressure)

									{


	if (parameters.coupling.set) {  // We only care about this if the coupling is to happen
		checkConsistency (lbField, nsLowX, nsHighX, nsLowY, nsHighY, nsLowZ, nsHighZ, _M);
	}
	//	_velocities[0]=&velocityX;
	//	_velocities[1]=&velocityY;
	//	_velocities[2]=&velocityZ;
	printParameters();
									}

NSLBCouplingStencil::NSLBCouplingStencil (const Parameters & parameters,
		LBField & lbField, FlowField & nsField
) :
									SmartGlobalBoundaryStencil<LBField> (parameters), _lbField (lbField), _nsField (nsField),
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
									//			_jacobian(jacobian),
									//			_pressure(pressure)
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

	//	_velocities[0]=&velocityX;
	//	_velocities[1]=&velocityY;
	//	_velocities[2]=&velocityZ;
	printParameters();
									}


NSLBCouplingStencil::~NSLBCouplingStencil() {
}


const FLOAT NSLBCouplingStencil::getDx() const{
	return _dx;
}


const FLOAT NSLBCouplingStencil::getDt() const{
	return _dt;
}


bool NSLBCouplingStencil::loadVelocity(
		const int ins,
		const int jns,
		const int kns,
		const int ilb,
		const int jlb,
		const int klb,
		const int component,
		const int *  const offset, const int * const flip){
	int localCoordinatesX;
	int localCoordinatesY;
	int localCoordinatesZ;
	bool res=false;
	for (int l = 0; l < stencilSize; l++){
		if(convertToLocalCoordinates(
				ins + offset[0] + stencil[l][0] * flip[0],
				jns + offset[1] + stencil[l][1] * flip[1],
				kns + offset[2] + stencil[l][2] * flip[2],
				localCoordinatesX,
				localCoordinatesY,
				localCoordinatesZ)
		){
			//std::cout<<"i_local:"<<(ins + offset[0] + stencil[l][0] * flip[0])<<","<<localCoordinatesX<<std::endl;
			res=true;
			std::vector<NSLBCommunicator*> coms;
			getCommunicators(ilb,jlb,klb,coms);
			if(coms.size()==0)
				std::cout<<"com not found:"<<ilb<<","<<jlb<<","<<klb<<std::endl;
			for(unsigned int i=0;i<coms.size();i++)
			coms[i]->setVelocityComponent(
					ilb,jlb,klb,l,component,offset,flip,
					_nsField.getVelocity().getVector(
							localCoordinatesX,
							localCoordinatesY,
							localCoordinatesZ)
							[component]);
		}else{

		}
		//		_values[l] = _nsField.getVelocity().getVector(
		//				i + offset[0] + stencil[l][0] * flip[0],
		//				j + offset[1] + stencil[l][1] * flip[1],
		//				k + offset[2] + stencil[l][2] * flip[2])
		//				[component];
	}
	return res;
}

void NSLBCouplingStencil::getCommunicators(
		const int i,const int j, const int k,
		std::vector<NSLBCommunicator*>& coms){
	int index=-1;
	for(unsigned int  comm_i = 0 ;comm_i<_communicators.size(); comm_i++)
		if(_communicators[comm_i]->isInside(i,j,k))
			coms.push_back(_communicators[comm_i]);


}

void NSLBCouplingStencil::loadPressure(
		const int ins,
		const int jns,
		const int kns,
		const int ilb,
		const int jlb,
		const int klb,
		const int *  const offset, const int * const flip){
	int localCoordinatesX;
	int localCoordinatesY;
	int localCoordinatesZ;
	for (int l = 0; l < stencilSize; l++){
		if(convertToLocalCoordinates(
				ins + offset[0] + stencil[l][0] * flip[0],
				jns + offset[1] + stencil[l][1] * flip[1],
				kns + offset[2] + stencil[l][2] * flip[2],
				localCoordinatesX,
				localCoordinatesY,
				localCoordinatesZ)
		){
			std::vector<NSLBCommunicator*> coms;
			getCommunicators(ilb,jlb,klb,coms);
			if(coms.size()==0)
				std::cout<<"com not found:"<<ilb<<","<<jlb<<","<<klb<<std::endl;
			for(unsigned int i=0;i<coms.size();i++)
			coms[i]->setPressure(
					ilb,jlb,klb,l,
					offset,flip,
					_nsField.getPressure().getScalar(
							localCoordinatesX,
							localCoordinatesY,
							localCoordinatesZ));
		}
	}
}

FLOAT NSLBCouplingStencil::interpolatePressure (int i, int j, int k, const int * const flip) {
	int ins, jns, kns;  // Cell in the NS solver
	int offset[3] = {0, 0, 0};    // An offset is unnecessary when dealing with the pressure
	FLOAT position[3], regularizedPosition[3], locationVector[stencilSize];

	identifyCellAndPosition(ins, jns, kns, position, i, j, k);

	FLOAT weights[stencilSize];     // Intermediate step during the interpolation

	setRPositionOffset (regularizedPosition, offset, flip, position, 0);
	setRPositionOffset (regularizedPosition, offset, flip, position, 1);
	setRPositionOffset (regularizedPosition, offset, flip, position, 2);

	getLocationVector (locationVector, regularizedPosition);
	loadPressure(ins, jns, kns,i,j,k,offset, flip);
	//
	//	matrix_vector(barycentricBasis, locationVector, weights, stencilSize, stencilSize);
	//
	//	return dot(_values, weights, stencilSize);
	return 0.0;
}

FLOAT NSLBCouplingStencil::computeBoundaryMeanPressure (){
	FLOAT accumulator = 0;

	// Left and right
	_flip[0] = -1; _flip[1] = 1; _flip[2] = 1;
	for (int j = 0; j < _lbField.getCellsY(); j++){
		for (int k = 0; k < _lbField.getCellsZ(); k++){
			accumulator += interpolatePressure(0, j, k, _flip);
		}
	}
	_flip[0] = 1; _flip[1] = 1; _flip[2] = 1;
	for (int j = 0; j < _lbField.getCellsY(); j++){
		for (int k = 0; k < _lbField.getCellsZ(); k++){
			accumulator += interpolatePressure(_lbField.getCellsX()-1, j, k, _flip);
		}
	}

	// Top and bottom
	_flip[0] = 1; _flip[1] = -1; _flip[2] = 1;
	for (int i = 1; i < _lbField.getCellsX()-1; i++){
		for (int k = 0; k < _lbField.getCellsZ(); k++){
			accumulator += interpolatePressure(i, 0, k, _flip);
		}
	}
	_flip[0] = 1; _flip[1] = 1; _flip[2] = 1;
	for (int i = 1; i < _lbField.getCellsX()-1; i++){
		for (int k = 0; k < _lbField.getCellsZ(); k++){
			accumulator += interpolatePressure(i, _lbField.getCellsY()-1, k, _flip);
		}
	}

	// Front and back
	_flip[0] = 1; _flip[1] = 1; _flip[2] = 1;
	for (int i = 1; i < _lbField.getCellsX()-1; i++){
		for (int j = 1; j < _lbField.getCellsY()-1; j++){
			accumulator += interpolatePressure(i, j, 0, _flip);
		}
	}
	_flip[0] = 1; _flip[1] = 1; _flip[2] = -1;
	for (int i = 1; i < _lbField.getCellsX()-1; i++){
		for (int j = 1; j < _lbField.getCellsY()-1; j++){
			accumulator += interpolatePressure(i, j, _lbField.getCellsZ()-1, _flip);
		}
	}

	accumulator /= (2 * _lbField.getCellsY() * _lbField.getCellsZ()) +
			(2 * (_lbField.getCellsX()-2) * _lbField.getCellsZ()) +
			(2 * (_lbField.getCellsX()-2) * (_lbField.getCellsY()-2));

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


bool NSLBCouplingStencil::interpolate (int i, int j, int k, const int * const flip){
	int ins, jns, kns;  // NS cell
	int offset[3];
	FLOAT position[3], locationVector[stencilSize];
	FLOAT dxVector[stencilSize], dyVector[stencilSize], dzVector[stencilSize];

	FLOAT velocity[3], jacobian[9], density;    // Storage for interpolated quantities

	FLOAT weights[stencilSize];     // Intermediate step during the interpolation

	identifyCellAndPosition(ins, jns, kns, position, i, j, k);

	// Pressure is represented as a fourth component with index 3

	bool res=false;
	for (int component = 0; component < 3; component++){
		setArrays (offset, locationVector, dxVector, dyVector,  dzVector,
				flip, position, component);
		bool temp=loadVelocity(ins, jns, kns,i,j,k, component, offset, flip);
		res=res||temp;

		//		matrix_vector(barycentricBasis, locationVector, weights, stencilSize, stencilSize);
		//		velocity[component] = dot(_values, weights, stencilSize) * _reciprocalVelocityLB;
		//
		//		matrix_vector(barycentricBasis, dxVector, weights, stencilSize, stencilSize);
		//		jacobian[3 * component] = dot(_values, weights, stencilSize) * _reciprocalVelocityLB *
		//				_reciprocalM;
		//
		//		matrix_vector(barycentricBasis, dyVector, weights, stencilSize, stencilSize);
		//		jacobian[3 * component + 1] = dot(_values, weights, stencilSize) * _reciprocalVelocityLB *
		//				_reciprocalM;
		//
		//		matrix_vector(barycentricBasis, dzVector, weights, stencilSize, stencilSize);
		//		jacobian[3 * component + 2] = dot(_values, weights, stencilSize) * _reciprocalVelocityLB *
		//				_reciprocalM;
		//		_velocities[component]->push_back(velocity[component]);
		//		_jacobian.push_back(jacobian[3 * component]);
		//		_jacobian.push_back(jacobian[3 * component+1]);
		//		_jacobian.push_back(jacobian[3 * component+2]);
	}

	setArrays (offset, locationVector, dxVector, dyVector,  dzVector, flip, position, 3);
	loadPressure(ins, jns, kns, i,j,k, offset, flip);
	//	matrix_vector(barycentricBasis, locationVector, weights, stencilSize, stencilSize);
	//	density = (dot(_values, weights, stencilSize) - _meanPressure) *
	//			_reciprocalVelocityLB  * _reciprocalVelocityLB * 3.0 + 1.0;

	//_pressure.push_back(density);

	//    FLOAT eq[Q], neq[Q];
	//    computeEquilibrium(eq, density, velocity);
	//    computeMinimumNonEquilibrium(neq, _parameters.lb.tau, density,
	//                                 jacobian[0], jacobian[1], jacobian[2],
	//                                 jacobian[3], jacobian[4], jacobian[5],
	//                                 jacobian[6], jacobian[7], jacobian[8]);
	//    for (int l = 0; l < Q; l++){
	//        _lbField.getFIn() [_lbField.getIndexF(l, i, j, k)] = eq[l] + (1.0 - 1.0/_parameters.lb.tau) * neq[l];
	//        _lbField.getFOut()[_lbField.getIndexF(l, i, j, k)] = eq[l] + (1.0 - 1.0/_parameters.lb.tau) * neq[l];
	//    }
	return res;
}
void NSLBCouplingStencil::flush(){
	for(unsigned int i=0;i<_communicators.size();i++){

			_communicators[i]->gather();
		}
	for(unsigned int i=0;i<_communicators.size();i++){

		_communicators[i]->flush();
	}
}

void NSLBCouplingStencil::initGather(){
	for(unsigned int i=0;i<_communicators.size();i++){

			_communicators[i]->gather_init();
	}
}
FLOAT NSLBCouplingStencil::interpolateVelocityComponent (const int * const cell,
		const FLOAT * const position,
		int component, const int * const flip){
	int offset[3];
	//	FLOAT locationVector[stencilSize];
	//
	//	FLOAT dxVector[stencilSize], dyVector[stencilSize], dzVector[stencilSize];
	//
	//	FLOAT weights[stencilSize];     // Intermediate step during the interpolation
	//
	//	setArrays (offset, locationVector, dxVector, dyVector,  dzVector,
	//			flip, position, component);
	//
	//	loadVelocity(cell[0], cell[1], cell[2], component, offset, flip);
	//
	//	matrix_vector(barycentricBasis, locationVector, weights, stencilSize, stencilSize);
	//	return dot(_values, weights, stencilSize) * _reciprocalVelocityLB;
	return 0.0;
}

FLOAT NSLBCouplingStencil::getReciprocalVelocity () const {
	return _reciprocalVelocityLB;
}

void NSLBCouplingStencil::setMeanPressure (const FLOAT & pressure) {
	_meanPressure = pressure;
}

void  NSLBCouplingStencil::registerLBRegion(NSLBCommunicator* com){
	_communicators.push_back(com);
}

bool NSLBCouplingStencil::applyLeftWall   ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns;
	FLOAT position[3];
	identifyCellAndPosition (ins, jns, kns, position, i, j, k);
	// Enforce symmetry of the application of the stencil. It is applied in the same way in the
	// other operations
	if ((jns - _nsLowY) < _nsSizeY / 2) _flip[1] = 1;
	else                                _flip[1] = -1;
	if ((kns - _nsLowZ) < _nsSizeZ / 2) _flip[2] = 1;
	else                                _flip[2] = -1;
	_flip[0] = -1;
	return interpolate(i, j, k, _flip);
}

bool NSLBCouplingStencil::applyRightWall  ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns;
	FLOAT position[3];
	identifyCellAndPosition (ins, jns, kns, position, i, j, k);
	if ((jns - _nsLowY) < _nsSizeY / 2) _flip[1] = 1;
	else                                _flip[1] = -1;
	if ((kns - _nsLowZ) < _nsSizeZ / 2) _flip[2] = 1;
	else                                _flip[2] = -1;
	_flip[0] = 1;
	return interpolate(i, j, k, _flip);
}

bool NSLBCouplingStencil::applyBottomWall ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns;
	FLOAT position[3];
	identifyCellAndPosition (ins, jns, kns, position, i, j, k);
	if ((ins - _nsLowX) < _nsSizeX / 2) _flip[0] = 1;
	else                                _flip[0] = -1;
	if ((kns - _nsLowZ) < _nsSizeZ / 2) _flip[2] = 1;
	else                                _flip[2] = -1;
	_flip[1] = -1;
	return interpolate(i, j, k, _flip);
}

bool NSLBCouplingStencil::applyTopWall    ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns;
	FLOAT position[3];
	identifyCellAndPosition (ins, jns, kns, position, i, j, k);
	if ((ins - _nsLowX) < _nsSizeX / 2) _flip[0] = 1;
	else                                _flip[0] = -1;
	if ((kns - _nsLowZ) < _nsSizeZ / 2) _flip[2] = 1;
	else                                _flip[2] = -1;
	_flip[1] = 1;
	return interpolate(i, j, k, _flip);
}

bool NSLBCouplingStencil::applyFrontWall  ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns;
	FLOAT position[3];
	identifyCellAndPosition (ins, jns, kns, position, i, j, k);
	if ((ins - _nsLowX) < _nsSizeX / 2) _flip[0] = 1;
	else                                _flip[0] = -1;
	if ((jns - _nsLowY) < _nsSizeY / 2) _flip[1] = 1;
	else                                _flip[1] = -1;
	_flip[2] = -1;
	return interpolate(i, j, k, _flip);
}

bool NSLBCouplingStencil::applyBackWall   ( LBField & lbField, int i, int j, int k ){
	int ins, jns, kns;
	FLOAT position[3];
	identifyCellAndPosition (ins, jns, kns, position, i, j, k);
	if ((ins - _nsLowX) < _nsSizeX / 2) _flip[0] = 1;
	else                                _flip[0] = -1;
	if ((jns - _nsLowY) < _nsSizeY / 2) _flip[1] = 1;
	else                                _flip[1] = -1;
	_flip[2] = 1;
	return interpolate(i, j, k, _flip);
}
