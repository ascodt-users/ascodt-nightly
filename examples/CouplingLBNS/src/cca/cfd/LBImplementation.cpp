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
#include "examples/cfd/lb/coupling/LBNSCommunicator.h"
#include "PetscParallelConfiguration.h"
#include <unistd.h>
#include <sstream>
#include <iostream>
#include "tinyxml2.h"

#include "utils/Dimensions.hpp"
#include "cplscheme/SharedPointer.hpp"
#include "cplscheme/CouplingData.hpp"
#include "SimpleTimer.h"
#include <math.h>
namespace boost
{

void throw_exception(std::exception const & e){}

}

cca::cfd::LBImplementation::LBImplementation():

												_configuration(NULL),
												_lbField(NULL),
												_streamAndCollideStencil(NULL),
												_streamAndCollideIterator(NULL),
												_streamStencil(NULL),
												_streamIterator(NULL),
												_collideStencil(NULL),
												_collideIterator(NULL),
												_bounceBackStencil(NULL),
												_bounceBackIterator(NULL),
												_lbnsCouplingIterator(NULL),
												_nslbCouplingStencil(NULL),
												_nslbCouplingIterator(NULL),
												_parallelManager(NULL),
												_movingWallStencil(NULL),
												_movingWallIterator(NULL),
												_parabolicStencil(NULL),
												_parabolicIterator(NULL)
{
	pthread_mutex_init(&_mutex, NULL);
	_iter=0;
	_lbprofiles.open("/work_fast/atanasoa/Programme/eclipse/lbprofiles.txt");
	_lbdensityalong.open("/work_fast/atanasoa/Programme/eclipse/lbdensityalong.txt");
	_lbdensitycenter.open("/work_fast/atanasoa/Programme/eclipse/lbdensitycenter.txt");
	_lbvelocitycenter.open("/work_fast/atanasoa/Programme/eclipse/lbvelocitycenter.txt");
	_setupFinished=false;
	_iterC=0;
	_comC=0;
	double initialRelaxation = 0.95;
	int    maxIterationsUsed = 1000;
	int    timestepsReused = 6;
	double singularityLimit = 1e-10;
	std::vector<int> dataIDs;
	dataIDs.push_back(0);
	dataIDs.push_back(1);
	std::map<int, double> scalings;
	scalings.insert(std::make_pair(0,508.154));
	scalings.insert(std::make_pair(1,86.2834));
	_pp = new precice::cplscheme::impl::IQNILSPostProcessing(initialRelaxation,
			maxIterationsUsed,timestepsReused, singularityLimit, dataIDs, scalings);
}


cca::cfd::LBImplementation::~LBImplementation(){
	if(_configuration){
		delete _configuration;
	}
	if(_lbField){
		delete _lbField;
	}
	if(_streamAndCollideStencil){
		delete _streamAndCollideStencil;
	}
	if(_streamAndCollideIterator){
		delete _streamAndCollideIterator;
	}

	if(_streamStencil){
		delete _streamStencil;
	}
	if(_streamIterator){
		delete _streamIterator;
	}

	if(_collideStencil){
		delete _collideStencil;
	}
	if(_collideIterator){
		delete _collideIterator;
	}

	if(	_bounceBackStencil){
		delete 	_bounceBackStencil;
	}
	if(	_bounceBackIterator){
		delete 	_bounceBackIterator;
	}
	if(_lbnsCouplingIterator){
		delete _lbnsCouplingIterator;
	}
	if(_nslbCouplingStencil){
		delete _nslbCouplingStencil;
	}
	if(_nslbCouplingIterator){
		delete _nslbCouplingIterator;
	}
	if(_parallelManager){
		delete _parallelManager;
	}
	if(_movingWallStencil){
		delete _movingWallStencil;
	}
	if(_movingWallIterator){
		delete _movingWallIterator;
	}
	if(_parabolicStencil){
		delete _parabolicStencil;
	}
	if(_parabolicIterator){
		delete _parabolicIterator;
	}

}


void testParallelLBM(std::string conf){
	cca::cfd::LBImplementation lbm;
	lbm.setup(conf);
	lbm.solve();
	lbm.plot();
}

extern "C" void main_loop_(bool);
int main(int argc, char *argv[]){
	int provided;
	MPI_Init_thread(&argc,&argv,MPI_THREAD_MULTIPLE ,&provided);
	PetscInitialize(&argc, &argv, PETSC_NULL, PETSC_NULL);

	//testParallelLBM(std::string(argv[1]));

	main_loop_(true);
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
void cca::cfd::LBImplementation::iqn(std::vector<double>& nslb,std::vector<double>& lbns,std::vector<double>& secondary){
	if(_iter>=2){
		precice::utils::DynVector dvalues;
		//		double nslb_min=nslb[0];
		//				double nslb_max=nslb[0];
		//				double lbns_min=lbns[0];
		//				double lbns_max=lbns[0];
		//				double secondary_min=secondary[0];
		//				double secondary_max=secondary[0];
		//		int nslb_min_index=0,nslb_max_index=0;
		//				int lbns_min_index=0,lbns_max_index=0;
		//				int secondary_min_index=0,secondary_max_index=0;
		//
		//
		//				for(unsigned int i=0;i<nslb.size();i++){
		//					if(nslb[i]< nslb_min){
		//						nslb_min=nslb[i];
		//						nslb_min_index=i;
		//					}
		//					if(nslb[i]>nslb_max){
		//						nslb_max=nslb[i];
		//						nslb_max_index=i;
		//					}
		//				}
		//				for(unsigned int i=0;i<lbns.size();i++){
		//					if(lbns[i]< lbns_min){
		//						lbns_min=lbns[i];
		//						lbns_min_index=i;
		//					}
		//					if(lbns[i]>lbns_max){
		//						lbns_max=lbns[i];
		//						lbns_max_index=i;
		//					}
		//				}
		//				for(unsigned int i=0;i<secondary.size();i++){
		//					if(secondary[i]< secondary_min){
		//						secondary_min=secondary[i];
		//						secondary_min_index=i;
		//					}
		//					if(secondary[i]>secondary_max){
		//						secondary_max=secondary[i];
		//						secondary_max_index=i;
		//					}
		//				}
		double dx= (double)_parameters.coupling.refLength/(double) _parameters.coupling.ratio;
		double dt= (double)_parameters.lb.viscosity * (double)_parameters.flow.Re * dx * dx;
		double scale= dx / dt;
		for(unsigned int i=0;i<nslb.size();i++)
			dvalues.append(nslb[i]);
		precice::utils::DynVector fvalues;

		for(unsigned int i=0;i<lbns.size();i++){
			fvalues.append(lbns[i]*scale);
		}
		precice::utils::DynVector sValues;
		for(unsigned int i=0;i<secondary.size();i++){
			sValues.append(secondary[i]);
		}
		if(_iter==2){
			std::cout<<"init cpl iqn"<<std::endl;
			precice::cplscheme::PtrCouplingData dpcd(new precice::cplscheme::CouplingData(&dvalues,false));
			precice::cplscheme::PtrCouplingData fpcd(new precice::cplscheme::CouplingData(&fvalues,false));
			precice::cplscheme::PtrCouplingData spcd(new precice::cplscheme::CouplingData(&sValues,false));
			dpcd->oldValues.append(precice::cplscheme::CouplingData::DataMatrix(
					dvalues.size(), 1, 0.0));
			fpcd->oldValues.append(precice::cplscheme::CouplingData::DataMatrix(
					fvalues.size(), 1, 0.0));
			spcd->oldValues.append(precice::cplscheme::CouplingData::DataMatrix(
					sValues.size(), 1, 0.0));
			_data.insert(std::pair<int, precice::cplscheme::PtrCouplingData>(0,dpcd));
			_data.insert(std::pair<int, precice::cplscheme::PtrCouplingData>(1,fpcd));

			_data.insert(std::pair<int, precice::cplscheme::PtrCouplingData>(2,spcd));
			_pp->initialize(_data);
		}else{
			std::cout<<"setting data in iqn"<<std::endl;
			_data.at(0)->values = &dvalues;
			_data.at(1)->values = &fvalues;
			_data.at(2)->values = &sValues;




			std::cout<<"start pp"<<std::endl;
		}
		_pp->performPostProcessing(_data);
		_data.at(0)->oldValues.column(0) = (*_data.at(0)->values);
		_data.at(1)->oldValues.column(0) =(*_data.at(1)->values);
		_data.at(2)->oldValues.column(0) =(*_data.at(2)->values);
		for(unsigned int i=0;i<_data.at(0)->values->size();i++)
			nslb[i]=(*_data.at(0)->values)(i);
		for(unsigned int i=0;i<_data.at(2)->values->size();i++)
			secondary[i]=(*_data.at(2)->values)(i);
		//		for(unsigned int i=0;i<_data.at(2)->values->size();i++)
		//					secondary[i]=(*_data.at(2)->values)(i);
	}
}
void cca::cfd::LBImplementation::printLBDensity(){

}

void cca::cfd::LBImplementation::printLBProfiles(){
	pthread_mutex_lock(&_mutex);
	FLOAT density;
	FLOAT velocity[3];
	for (int i = 0; i < _lbField->getCellsY(); i++ ){
		_lbField->getPressureAndVelocity(density, velocity, 35,
				i, 20);
		_lbprofiles << velocity[0]// * _nslbCouplingStencil->getDx() / _nslbCouplingStencil->getDt() <<
		                        <<"\t";
	}
	_lbprofiles << std::endl;
	//
	//	// Print pressure along the flow
	//	for (int i = 0; i < _lbField->getCellsX(); i++){
	//		_lbdensityalong << _lbField->getDensity(_lbField->getFOut(), i, _lbField->getCellsY()/2,
	//				_lbField->getCellsZ() / 2) << "\t";
	//	}
	//	_lbField->getPressureAndVelocity(density, velocity, _lbField->getCellsZ()/2, _lbField->getCellsZ()/2, _lbField->getCellsZ()/2);
	//	_lbdensityalong << std::endl;
	//	_lbdensitycenter << density << std::endl;
	//	_lbvelocitycenter << velocity[0] << std::endl;
	pthread_mutex_unlock(&_mutex);

}
void cca::cfd::LBImplementation::setup(const std::string inputScenario){
	pthread_mutex_lock(&_mutex);
	_configuration= new Configuration(inputScenario);
	_configuration->loadParameters(_parameters,MPI_COMM_WORLD,"parallel-lb");

	PetscParallelConfiguration parallelConfiguration(
			_parameters,
			(_parameters.coupling.set)?_parameters.coupling.sizeNS[0] * _parameters.coupling.ratio-1:
					_parameters.geometry.sizeX,
					(_parameters.coupling.set)?_parameters.coupling.sizeNS[1] * _parameters.coupling.ratio-1:
							_parameters.geometry.sizeY,
							(_parameters.coupling.set)?_parameters.coupling.sizeNS[2] * _parameters.coupling.ratio-1:
									_parameters.geometry.sizeZ
	);
	int rank=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	std::cout<<"creating lb field on rank:"<<rank<<std::endl;
	_lbField=new LBField(
			_parameters,
			_parameters.parallel.localSize[0],
			_parameters.parallel.localSize[1],
			_parameters.parallel.localSize[2]);
	readGeometry("/home/atanasoa/Desktop/spheres.xml");
	_lbField->allocate();
	_streamAndCollideStencil = new LBStreamAndCollideStencil(_parameters);
	_streamAndCollideIterator = new  FieldIterator<LBField>(*_lbField, *_streamAndCollideStencil);
	_streamStencil = new LBStreamStencil(_parameters);
	_streamIterator = new  SOAFieldIterator<LBField>(*_lbField, *_streamStencil);
	_collideStencil = new LBCollideStencil(_parameters);
	_collideIterator = new  FieldIterator<LBField>(*_lbField, *_collideStencil);



	_bounceBackStencil = new LBBounceBackStencil(_parameters);
	_bounceBackIterator = new FieldIterator<LBField> (*_lbField, *_bounceBackStencil);
	_movingWallStencil = new LBMovingWallStencil(_parameters);
	_movingWallIterator = new GlobalBoundaryIterator<LBField>(*_lbField,_parameters,*_movingWallStencil, 1, -1);
	_parabolicStencil = new LBParabolicStencil(_parameters,0,-0.000005);
	_parabolicIterator = new GlobalBoundaryIterator<LBField>(*_lbField,_parameters,*_parabolicStencil, 1, -1);
	std::cout<<"setup with coupling:"<<_parameters.coupling.set<<std::endl;
	if(_parameters.coupling.set){
		_lbnsCouplingIterator = new LBNSCouplingIterator (_parameters,*_lbField);
		for(unsigned int i=0;i<_coms.size();i++)
			_lbnsCouplingIterator->registerNSRegion(_coms[i]);
		gatherDomainDescriptions();
		gatherMids();
		if(_parameters.parallel.rank==0&&_ns){
			std::cout<<"setting lb region"<<std::endl;
			int regionSize=3*_parameters.parallel.numProcessors[0]*_parameters.parallel.numProcessors[1]*_parameters.parallel.numProcessors[2];
			_ns->setupCommForLBRegionParallel(
					&_startDomain[0],
					regionSize,
					&_endDomain[0],
					regionSize,
					&_mids[0],
					regionSize/3);
			int atr;
			_ns->syncr(atr);
		}
		_nslbCouplingStencil = new NSLBCouplingStencil (
				_parameters,
				*_lbField);
		_nslbCouplingIterator = new GlobalBoundaryIterator<LBField>(*_lbField, _parameters,*_nslbCouplingStencil);
	}
	_parallelManager = new LBParallelManager(*_lbField,_parameters);
	//_parameters.coupling.set = false;
	pthread_mutex_unlock(&_mutex);
}

void cca::cfd::LBImplementation::readGeometry(std::string file){

	//	tinyxml2::XMLElement *node;
	//	tinyxml2::XMLElement *subNode;

	//if(_parameters.parallel.rank==0){
	tinyxml2::XMLDocument confFile;
	confFile.LoadFile(file.c_str());
	std::cout<<"reading geomtry file"<<std::endl;
	tinyxml2::XMLElement* root = confFile.FirstChildElement("spheres");

	for(tinyxml2::XMLElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{

		//std::cout<<"sphere pos:"<<<<std::endl;
		std::istringstream iss(e->Attribute("center"));
		std::string token;
		std::vector<double> pos;
		double radius;
		while(std::getline(iss, token, ';')) {
			pos.push_back(atof(token.c_str()));
		}
		e->QueryDoubleAttribute("radius",&radius);


		_lbField->registerSphere(pos[0],pos[1],pos[2],radius);

		//std::string wmName = e->Attribute("name");

	}
	//}
}
void cca::cfd::LBImplementation::solve(){
	pthread_mutex_lock(&_mutex);

	SimpleTimer timer;

	// parabolicIterator.iterate();

	timer.start();
	int cellZ=
			(_parameters.coupling.set)?
					_parameters.coupling.sizeNS[2] * _parameters.coupling.ratio + 1:
					_parameters.geometry.sizeZ+2;
	const int lbIterations = 10000* (cellZ-1) * (cellZ-1) / (40*40);

	if(_parameters.coupling.set){
		iqn(_nslbCouplingStencil->getCouplingData(),_lbnsCouplingIterator->getCouplingData(),_nslbCouplingStencil->getSecondaryCouplingData());
		_lbnsCouplingIterator->getCouplingData().clear();
		_nslbCouplingIterator->iterate();
	}
	for (int i = 0; i < lbIterations; i++){

		_parallelManager->communicatePdfs();
		_lbField->swap();
		_streamAndCollideIterator->iterate();
		//_streamIterator->iterate();
		//_collideIterator->iterate();

		//_movingWallIterator->iterate();
		//_parabolicIterator->iterate();

		_bounceBackIterator->iterate();
		//		if(i%500==0){
		//			printLBProfiles();
		//			plot();
		//		}
		//std::cout<<"iter:"<<i<<" from:"<<lbIterations<<std::endl;
	}
	//printLBProfiles();
	if(_parameters.coupling.set){
		_nslbCouplingStencil->clear();
	}
	const FLOAT duration = timer.getTimeAndContinue();
	std::cout << "Performance: " << (_lbField->getNx() * _lbField->getNy() * _lbField->getNz()) * lbIterations /
			(duration * 1e6) <<  " MLUPS" << std::endl;
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
	//_nslbCouplingStencil->setVelocities((double*)velocitiesX,(double*)velocitiesY,(double*)velocitiesZ,velocitiesX_len);
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::setPressure(const double* pressure, const int pressure_len){
	pthread_mutex_lock(&_mutex);
	//	_nslbCouplingStencil->setPressure((double*)pressure,pressure_len);
	//	_nslbCouplingStencil->reset();
	//	_nslbCouplingIterator->iterate();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::LBImplementation::setGradients(const double* gradients, const int gradients_len){
	pthread_mutex_lock(&_mutex);
	//_nslbCouplingStencil->setJacobian(gradients,gradients_len);
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
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	std::cout<<"lb rank:"<<rank<<"starting boundary iter"<<std::endl;
	_lbnsCouplingIterator->iterateBoundary();
	if(_maxSizeCommunicators.size()==0){
		_maxSizeCommunicators.resize(_comC*2);
		_sizeCommunicators.resize(_comC*2);
		_lbnsCouplingIterator->initGather();
		MPI_Allreduce(&_sizeCommunicators[0],&_maxSizeCommunicators[0],_comC,MPI_2INT,MPI_MAXLOC,MPI_COMM_WORLD);
		std::cout<<"init gather finished"<<std::endl;
		for(int i=0;i<_comC;i++){
			std::cout<<"region i:"<<i<<_maxSizeCommunicators[i*2+1]<<" data:"<<_maxSizeCommunicators[i*2]<<std::endl;
		}
	}
	_lbnsCouplingIterator->flush();
	MPI_Barrier(MPI_COMM_WORLD);
	std::cout<<"rank:"<<rank<<"finished boundary iter"<<std::endl;
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


void cca::cfd::LBImplementation::gatherDomainDescriptions(){
	std::vector<int> startBuffer;
	std::vector<int> endBuffer;
	startBuffer.resize(3);
	endBuffer.resize(3);
	if(_parameters.parallel.rank==0){
		_startDomain.resize(3*_parameters.parallel.numProcessors[0]*_parameters.parallel.numProcessors[1]*_parameters.parallel.numProcessors[2]);
		_endDomain.resize(3*_parameters.parallel.numProcessors[0]*_parameters.parallel.numProcessors[1]*_parameters.parallel.numProcessors[2]);
	}
	startBuffer[0]=_parameters.parallel.firstCorner[0];

	startBuffer[1]=_parameters.parallel.firstCorner[1];

	startBuffer[2]=_parameters.parallel.firstCorner[2];

	endBuffer[0]=_parameters.parallel.firstCorner[0]+_parameters.parallel.localSize[0]+1;

	endBuffer[1]=_parameters.parallel.firstCorner[1]+_parameters.parallel.localSize[1]+1;

	endBuffer[2]=_parameters.parallel.firstCorner[2]+_parameters.parallel.localSize[2]+1;
	MPI_Gather(&startBuffer[0],3,MPI_INT,&_startDomain[0],3,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Gather(&endBuffer[0],3,MPI_INT,&_endDomain[0],3,MPI_INT,0,MPI_COMM_WORLD);

}
extern std::string retrieveSocketAddress();
void cca::cfd::LBImplementation::gatherMids(){
	std::string mid=retrieveSocketAddress();
	_mids.push_back(mid);
	if(_parameters.parallel.rank!=0){

		std::vector<char> bytes(mid.begin(), mid.end());
		bytes.push_back('\0');
		int num_of_bytes=(int)bytes.size();
		assert(num_of_bytes>0);
		MPI_Send(&num_of_bytes,1,MPI_INT,0,1000,MPI_COMM_WORLD);
		MPI_Send(&bytes[0],num_of_bytes,MPI_BYTE,0,1000,MPI_COMM_WORLD);
	}else{
		int pieces=
				_parameters.parallel.numProcessors[0]*
				_parameters.parallel.numProcessors[1]*
				_parameters.parallel.numProcessors[2];
		for(int i=1;i<pieces;i++)
		{
			int number_of_bytes=0;
			MPI_Status status;
			MPI_Recv (&number_of_bytes,1, MPI_INT,i, 1000, MPI_COMM_WORLD,&status);
			assert(number_of_bytes>0);
			std::vector<char> buff(number_of_bytes);
			MPI_Recv (&buff[0],number_of_bytes,MPI_BYTE,i,1000,MPI_COMM_WORLD,&status);
			std::cout<<"lb rank:"<<i<<" mid:"<<std::string(&buff[0])<<std::endl;
			_mids.push_back(std::string(&buff[0]));
		}
	}

}

void cca::cfd::LBImplementation::setupCommForNSRegion(
		const int* startOfRegion,
		const int startOfRegion_len,
		const int* endOfRegion,
		const int endOfRegion_len,
		const std::string* commids,
		const int commids_len){
	pthread_mutex_lock(&_mutex);
	_comC=commids_len;
	int *start = (int*)startOfRegion;
	int *end = (int*)endOfRegion;
	for(int i=0;i<commids_len;i++){
		//		if(_parameters.parallel.rank==0){
		std::cout<<"ns_start region:"<<i<<","<<commids[i]<<"start_r:["<<startOfRegion[i*3]<<","<<startOfRegion[i*3+1]<<","<<startOfRegion[i*3+2]<<"]"<<std::endl;
		std::cout<<"ns_end region:"<<i<<","<<commids[i]<<"start_r:["<<endOfRegion[i*3]<<","<<endOfRegion[i*3+1]<<","<<endOfRegion[i*3+2]<<"]"<<std::endl;
		std::cout<<"lb_rank:"<<_parameters.parallel.rank<<","<<_lbnsCouplingIterator<<std::endl;
		//		}
		//if(_lbnsCouplingIterator!=NULL)
		//_lbnsCouplingIterator->registerNSRegion(i,(int*)startOfRegion,(int*)endOfRegion,commids[i]);
		int a[3];
		LBNSCommunicator* com=new LBNSCommunicator(
				_parameters,
				i,
				(int*)startOfRegion,
				(int*)endOfRegion,
				commids[i],
				_maxSizeCommunicators,
				_sizeCommunicators);
		if(_lbnsCouplingIterator!=NULL)
			_lbnsCouplingIterator->registerNSRegion(com);
		else
			_coms.push_back(com);
	}
	_setupFinished=true;
	//MPI_Barrier(MPI_COMM_WORLD);
	pthread_mutex_unlock(&_mutex);
}

void cca::cfd::LBImplementation::forwardVelocities(
		const int * keys,
		const int keys_len,
		const int * offsets,
		const int offsets_len,
		const int * flips,
		const int flips_len,
		const double* values,
		const int values_len,
		int& ack){
	pthread_mutex_lock(&_mutex);
	for (int i=0;i<keys_len;i++){
		_nslbCouplingStencil->setVelocityComponent(
				keys[i],
				offsets[3*i],
				offsets[3*i+1],
				offsets[3*i+2],
				flips[3*i],
				flips[3*i+1],
				flips[3*i+2],
				values[i]);

	}
	ack=1;
	//std::cout<<"receiving velocities on lb"<<std::endl;
	pthread_mutex_unlock(&_mutex);
}

void cca::cfd::LBImplementation::forwardPressure(
		const int * keys,
		const int keys_len,
		const int * offsets,
		const int offsets_len,
		const int * flips,
		const int flips_len,
		const double* values,
		const int values_len,
		int& ack){
	pthread_mutex_lock(&_mutex);
	//	std::cout<<"start iter:"<<_iterC++<<std::endl;
	//	std::cout<<"receiving pressure on rank:"
	//			<<_parameters.parallel.rank<<" size:"<<values_len<<std::endl;
	for (unsigned int i = 0 ; i < values_len;i++)
		_nslbCouplingStencil->setPressure(
				keys[i],
				offsets[3*i],
				offsets[3*i+1],
				offsets[3*i+2],
				flips[3*i],
				flips[3*i+1],
				flips[3*i+2],
				values[i]);
	ack=1;
	pthread_mutex_unlock(&_mutex);
}
