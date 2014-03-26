#include "cca/cfd/NSImplementation.h"
#include <petsc.h>
#include "examples/kernel/Configuration.h"
#include <assert.h>
#include "examples/cfd/ns/Simulation.h"
#include "PetscParallelConfiguration.h"
#include "examples/cfd/ns/coupling/LBNSFGHCorrectionIterator.h"
#include "examples/cfd/ns/coupling/LBNSInitFlagsIterator.h"
cca::cfd::NSImplementation::NSImplementation(){
	pthread_mutex_init(&_mutex, NULL);
	_configuration = NULL;
	_simulation = NULL;
	_flowField = NULL;
	_time=0.0;
	_lbnsCouplingIterator=NULL;
	_nslbStencil=NULL;
	_nslbCouplingIterator=NULL;
	_lbField=NULL;
	_iter=0;
	_nsprofiles.open("/work_fast/atanasoa/Programme/eclipse/nsprofiles.txt");
	_nspressure.open("/work_fast/atanasoa/Programme/eclipse/nspressure.txt");
}

cca::cfd::NSImplementation::~NSImplementation(){
	if(_configuration){
		delete _configuration;
	}
	if(_simulation){
		delete _simulation;
	}
	if(_flowField){
		delete _flowField;
	}
	if(_lbnsCouplingIterator){
		delete _lbnsCouplingIterator;
	}
	if(_nslbStencil){
		delete _nslbStencil;
	}
	if(_nslbCouplingIterator){
		delete _nslbCouplingIterator;
	}
	if(_lbField){
		delete _lbField;
	}

}
extern "C" void main_loop_();
int main(int argc, char *argv[]){
	PetscInitialize(&argc, &argv, PETSC_NULL, PETSC_NULL);
	main_loop_();
	PetscFinalize();
}
void cca::cfd::NSImplementation::printNSPressure(){
	pthread_mutex_lock(&_mutex);
	FLOAT pressureSum;
	const int halfSize = _flowField->getCellsY() / 2;
	for (int i = 2; i < _flowField->getCellsX(); i++){
		pressureSum = _flowField->getPressure().getScalar(i, 1 + halfSize, 1 + halfSize);
		pressureSum += _flowField->getPressure().getScalar(i, 1 + halfSize, 2 + halfSize);
		pressureSum += _flowField->getPressure().getScalar(i, 2 + halfSize, 1 + halfSize);
		pressureSum += _flowField->getPressure().getScalar(i, 2 + halfSize, 2 + halfSize);
		pressureSum /= 4.0;
		_nspressure << pressureSum << "\t";
	}
	_nspressure << std::endl;

	pthread_mutex_unlock(&_mutex);
}

void cca::cfd::NSImplementation::printNSProfiles(){
	pthread_mutex_lock(&_mutex);
	for (int i = 2; i < _flowField->getCellsY() - 1; i++ ){
		_nsprofiles << (_flowField->getVelocity().getVector((_flowField->getCellsX()-3)/2 + 1, i,
				(_flowField->getCellsZ()/2-1))[0] +
				_flowField->getVelocity().getVector((_flowField->getCellsX()-3)/2 + 1, i,
						(_flowField->getCellsZ()/2))[0]) / 2 << "\t";
	}
	_nsprofiles << std::endl;
	pthread_mutex_unlock(&_mutex);
}

void cca::cfd::NSImplementation::closeNSProfiles(){
	pthread_mutex_lock(&_mutex);
	_nsprofiles.close();
	_nspressure.close();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::setup(const std::string inputScenario){
	pthread_mutex_lock(&_mutex);
	std::cout<<"ns setup:"<<inputScenario<<std::endl;
	_configuration= new Configuration(inputScenario);
	_configuration->loadParameters(_parameters);
	std::cout<<"ns setup loaded parameters"<<std::endl;
	PetscParallelConfiguration parallelConfiguration(_parameters);
	if (_parameters.simulation.type=="turbulence"){
		std::cout << "Start turbulence simulation in " << _parameters.geometry.dim << "D" << std::endl;
		//_flowField = new TurbulentFlowField(_parameters);
		assert(_flowField);
		//_simulation = new TurbulentSimulation(_parameters,*turbulentFlowField);
		assert(_simulation);
	} else if (_parameters.simulation.type=="dns"){
		std::cout << "Start DNS simulation in " << _parameters.geometry.dim << "D" << std::endl;
		_flowField = new FlowField(_parameters);
		assert(_flowField);
		_simulation = new Simulation(_parameters,*_flowField);
		_lbnsCouplingIterator = new LBNSCouplingIterator(_parameters,*_flowField);
		LBNSInitFlagsIterator lbnsInitFlagsIterator(_parameters,*_flowField);
		assert(_simulation);
		_lbField=new LBField(_parameters);
		_nslbStencil = new NSLBCouplingStencil (
				_parameters,
				*_lbField,
				*_flowField,
				_velocityX,
				_velocityY,
				_velocityZ,
				_jacobian,
				_pressure);
		_nslbCouplingIterator =  new GlobalBoundaryIterator<LBField> (*_lbField,_parameters, *_nslbStencil);
		_parameters.coupling.set = true;
		lbnsInitFlagsIterator.iterate();
	} else {
		handleError(1, "Unknown simulation type! Currently supported: dns, turbulence");
	}
	std::cout<<"ns setup finished"<<std::endl;
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::solveOneTimestepPhaseOne(){
	pthread_mutex_lock(&_mutex);

	_simulation->solveTimestepPhaseOne();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::solveOneTimestepPhaseTwo(){
	pthread_mutex_lock(&_mutex);

	_simulation->solveTimestepPhaseTwo();
	pthread_mutex_unlock(&_mutex);
}

void cca::cfd::NSImplementation::solve(){
	pthread_mutex_lock(&_mutex);
	double time=0.0;
	while (time < _parameters.simulation.finalTime){
		_simulation->solveTimestepPhaseOne();
		_lbnsCouplingIterator->iterateBoundary();
		_simulation->solveTimestepPhaseTwo();
		time += _parameters.timestep.dt;
	}

	pthread_mutex_unlock(&_mutex);

}
void cca::cfd::NSImplementation::iterateBoundary(){
	pthread_mutex_lock(&_mutex);
	_lbnsCouplingIterator->iterateBoundary();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::iterateInner(){
	pthread_mutex_lock(&_mutex);
	_lbnsCouplingIterator->iterateInner();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
	pthread_mutex_lock(&_mutex);
	_lbnsCouplingIterator->setLBVelocities((double*)velocitiesX,(double*)velocitiesY,(double*)velocitiesZ,
			velocitiesX_len,velocitiesY_len,velocitiesZ_len);
	pthread_mutex_unlock(&_mutex);
}



void cca::cfd::NSImplementation::retrieveTimestep(double& timestep){
	pthread_mutex_lock(&_mutex);
	timestep=_parameters.timestep.dt;
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::plot(){
	pthread_mutex_lock(&_mutex);
	_simulation->plotVTK(_iter++);
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::iterate(){
	pthread_mutex_lock(&_mutex);
	_velocityX.clear();
	_velocityY.clear();
	_velocityZ.clear();
	_jacobian.clear();
	_pressure.clear();
	_nslbStencil->computeBoundaryMeanPressure();
	_nslbCouplingIterator->iterate();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::retrieveVelocitiesSize(int& memory){
	pthread_mutex_lock(&_mutex);
	memory= _velocityX.size();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
	pthread_mutex_lock(&_mutex);
	for(int i=0;i<velocityX_len;i++){
		velocityX[i]= _velocityX[i];
		velocityY[i]= _velocityY[i];
		velocityZ[i]= _velocityZ[i];
	}
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::retrieveJacobianCopy(double* jacobian, const int jacobian_len){
	pthread_mutex_lock(&_mutex);
	for(int i=0;i<jacobian_len;i++){
		jacobian[i]= _jacobian[i];
	}
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::retrievePressureCopy(double* pressure, const int pressure_len){
	pthread_mutex_lock(&_mutex);
	for(int i=0;i<pressure_len;i++){
		pressure[i]= _pressure[i];
	}
	pthread_mutex_unlock(&_mutex);
}
