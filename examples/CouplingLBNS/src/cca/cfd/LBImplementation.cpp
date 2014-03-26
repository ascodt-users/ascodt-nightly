#include "cca/cfd/LBImplementation.h"
#include <petsc.h>
#include "examples/kernel/Configuration.h"
#include <assert.h>
#include "examples/cfd/lb/LBField.h"
#include "Iterators.h"
#include "examples/cfd/lb/stencils/LBStreamAndCollideStencil.h"

#include "examples/cfd/lb/stencils/LBCollideStencil.h"
#include "examples/cfd/lb/stencils/LBStreamStencil.h"

#include "examples/cfd/lb/stencils/LBMovingWallStencil.h"
#include "examples/cfd/lb/stencils/LBParabolicStencil.h"
#include "examples/cfd/lb/stencils/LBRotatedParabolicStencil.h"
#include "examples/cfd/lb/stencils/LBVTKStencil.h"

#include "PetscParallelConfiguration.h"
cca::cfd::LBImplementation::LBImplementation():

_configuration(NULL),
_lbField(NULL),
_streamAndCollideStencil(NULL),
_streamAndCollideIterator(NULL),
_bounceBackStencil(NULL),
_bounceBackIterator(NULL),
_lbnsCouplingIterator(NULL),
_nslbCouplingStencil(NULL),
_nslbCouplingIterator(NULL),
_parallelManager(NULL),
_movingWallStencil(NULL),
_movingWallIterator(NULL)
{
	pthread_mutex_init(&_mutex, NULL);
	_iter=0;
	_lbprofiles.open("/work_fast/atanasoa/Programme/eclipse/lbprofiles.txt");
	_lbdensityalong.open("/work_fast/atanasoa/Programme/eclipse/lbdensityalong.txt");
	_lbdensitycenter.open("/work_fast/atanasoa/Programme/eclipse/lbdensitycenter.txt");
	_lbvelocitycenter.open("/work_fast/atanasoa/Programme/eclipse/lbvelocitycenter.txt");
}


cca::cfd::LBImplementation::~LBImplementation(){
//	if(_configuration){
//		delete _configuration;
//	}
//	if(_lbField){
//		delete _lbField;
//	}
//	if(_streamAndCollideStencil){
//		delete _streamAndCollideStencil;
//	}
//	if(_streamAndCollideIterator){
//		delete _streamAndCollideIterator;
//	}
//	if(	_bounceBackStencil){
//		delete 	_bounceBackStencil;
//	}
//	if(	_bounceBackIterator){
//		delete 	_bounceBackIterator;
//	}
//	if(_lbnsCouplingIterator){
//		delete _lbnsCouplingIterator;
//	}
//	if(_nslbCouplingStencil){
//		delete _nslbCouplingStencil;
//	}
//	if(_nslbCouplingIterator){
//		delete _nslbCouplingIterator;
//	}
//	if(_parallelManager){
//		delete _parallelManager;
//	}
//	if(_movingWallStencil){
//		delete _movingWallStencil;
//	}
//	if(_movingWallIterator){
//		delete _movingWallIterator;
//	}

}


void testParallelLBM(std::string conf){
	cca::cfd::LBImplementation lbm;
	lbm.setup(conf);
	lbm.solve();
	lbm.plot();
}

extern "C" void main_loop_();
int main(int argc, char *argv[]){
	PetscInitialize(&argc, &argv, PETSC_NULL, PETSC_NULL);
	testParallelLBM(std::string(
			"/work_fast/atanasoa/Programme/workspace_new/LB_NS_EOF/trunk/src/configurationFiles/cavity_lb.xml"));

	PetscFinalize();
}

void cca::cfd::LBImplementation::closeLBProfiles(){
	pthread_mutex_lock(&_mutex);
	_lbprofiles.close();
	_lbvelocitycenter.close();
	_lbdensityalong.close();
	_lbdensitycenter.close();
	pthread_mutex_unlock(&_mutex);

}

void cca::cfd::LBImplementation::printLBDensity(){

}

void cca::cfd::LBImplementation::printLBProfiles(){
	pthread_mutex_lock(&_mutex);
	FLOAT density;
	FLOAT velocity[3];
	for (int i = 0; i < _lbField->getCellsY(); i++ ){
		_lbField->getPressureAndVelocity(density, velocity, _lbField->getCellsX()/2,
				i, _lbField->getCellsZ()/2);
		_lbprofiles << velocity[0] * _nslbCouplingStencil->getDx() / _nslbCouplingStencil->getDt() <<
				"\t";
	}
	_lbprofiles << std::endl;

	// Print pressure along the flow
	for (int i = 0; i < _lbField->getCellsX(); i++){
		_lbdensityalong << _lbField->getDensity(_lbField->getFOut(), i, _lbField->getCellsY()/2,
				_lbField->getCellsZ() / 2) << "\t";
	}
	_lbField->getPressureAndVelocity(density, velocity, _lbField->getCellsZ()/2, _lbField->getCellsZ()/2, _lbField->getCellsZ()/2);
	_lbdensityalong << std::endl;
	_lbdensitycenter << density << std::endl;
	_lbvelocitycenter << velocity[0] << std::endl;
	pthread_mutex_unlock(&_mutex);

}
void cca::cfd::LBImplementation::setup(const std::string inputScenario){
	pthread_mutex_lock(&_mutex);
	_configuration= new Configuration(inputScenario);
	_configuration->loadParameters(_parameters, MPI_COMM_WORLD);
	PetscParallelConfiguration parallelConfiguration(_parameters);
	std::cout<<"creating lb field"<<std::endl;
	_lbField=new LBField(_parameters);

	_lbField->allocate();
	_streamAndCollideStencil = new LBStreamAndCollideStencil(_parameters);
	_streamAndCollideIterator = new  FieldIterator<LBField>(*_lbField, *_streamAndCollideStencil);
	_bounceBackStencil = new LBBounceBackStencil(_parameters);
	_bounceBackIterator = new FieldIterator<LBField> (*_lbField, *_bounceBackStencil);
	_movingWallStencil = new LBMovingWallStencil(_parameters);
	_movingWallIterator = new GlobalBoundaryIterator<LBField>(*_lbField,_parameters,*_movingWallStencil, 1, -1);

//	_lbnsCouplingIterator = new LBNSCouplingIterator (_parameters,*_lbField);
//	_nslbCouplingStencil = new NSLBCouplingStencil (
//			_parameters,
//			*_lbField);
//	_nslbCouplingIterator = new GlobalBoundaryIterator<LBField>(*_lbField, _parameters,*_nslbCouplingStencil);
	_parallelManager = new LBParallelManager(*_lbField,_parameters);
	_parameters.coupling.set = false;
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::solve(){
	pthread_mutex_lock(&_mutex);

	const int lbIterations = 1000;
	// The original experiments had a field of size 40
	//s* (_lbField->getCellsZ()-1) * (_lbField->getCellsZ()-1) / (40*40)

	for (int i = 0; i < lbIterations; i++){
		_parallelManager->communicatePdfs();
		_lbField->swap();
		_streamAndCollideIterator->iterate();
		//_bounceBackIterator->iterate();
		_movingWallIterator->iterate();
	}
	pthread_mutex_unlock(&_mutex);

}

void cca::cfd::LBImplementation::solveOneTimestep(){
	pthread_mutex_lock(&_mutex);
	_lbField->swap();
	_streamAndCollideIterator->iterate();
	_bounceBackIterator->iterate();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
	pthread_mutex_lock(&_mutex);
	_nslbCouplingStencil->setVelocities((double*)velocitiesX,(double*)velocitiesY,(double*)velocitiesZ,velocitiesX_len);
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::setPressure(const double* pressure, const int pressure_len){
	pthread_mutex_lock(&_mutex);
	_nslbCouplingStencil->setPressure((double*)pressure,pressure_len);
	_nslbCouplingStencil->reset();
	_nslbCouplingIterator->iterate();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::setGradients(const double* gradients, const int gradients_len){
	pthread_mutex_lock(&_mutex);
	_nslbCouplingStencil->setJacobian(gradients,gradients_len);
	pthread_mutex_unlock(&_mutex);
}

void cca::cfd::LBImplementation::plot(){
	pthread_mutex_lock(&_mutex);
	LBVTKStencil lbvtkStencil (_parameters);
	lbvtkStencil.setPrefix("lbresults");

	FieldIterator<LBField> lbvtkIterator(*_lbField, lbvtkStencil);
	lbvtkStencil.openFile ( *_lbField,_iter++);
	lbvtkIterator.iterate();
	lbvtkStencil.write( *_lbField );
	lbvtkStencil.closeFile();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::iterateBoundary(){
	pthread_mutex_lock(&_mutex);
	_lbnsCouplingIterator->iterateBoundary();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::iterateInner(){
	pthread_mutex_lock(&_mutex);
	_lbnsCouplingIterator->iterateInner();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::retrieveVelocitiesSize(int& memoryX,int& memoryY,int& memoryZ){
	pthread_mutex_lock(&_mutex);
	memoryX= _lbnsCouplingIterator->getVelocitySizeX();
	memoryY= _lbnsCouplingIterator->getVelocitySizeY();
	memoryZ= _lbnsCouplingIterator->getVelocitySizeZ();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
	pthread_mutex_lock(&_mutex);
	for(int i=0;i<velocityX_len;i++){
		velocityX[i]= _lbnsCouplingIterator->getVelocityX()[i];

	}
	for(int i=0;i<velocityY_len;i++){
		velocityY[i]= _lbnsCouplingIterator->getVelocityY()[i];

	}
	for(int i=0;i<velocityZ_len;i++){
		velocityZ[i]= _lbnsCouplingIterator->getVelocityZ()[i];

	}
	pthread_mutex_unlock(&_mutex);
}
