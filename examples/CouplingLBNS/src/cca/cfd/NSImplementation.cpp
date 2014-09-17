#include "cca/cfd/NSImplementation.h"
#include <petsc.h>
#include "examples/kernel/Configuration.h"
#include <assert.h>
#include "examples/cfd/ns/Simulation.h"
#include "PetscParallelConfiguration.h"
#include "examples/cfd/ns/coupling/LBNSFGHCorrectionIterator.h"
#include "examples/cfd/ns/coupling/LBNSInitFlagsIterator.h"
#include "examples/cfd/ns/coupling/NSLBCommunicator.h"


#include "utils/Dimensions.hpp"
#include "cplscheme/SharedPointer.hpp"
#include "cplscheme/CouplingData.hpp"
#include <unistd.h>

namespace boost
{

void throw_exception(std::exception const & e){}

}

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
	_nsprofiles.open("nsprofiles.txt");
	_nspressure.open("nspressure.txt");
	_mcFile.open("convergence.txt");
	_comC=0;
	double initialRelaxation =  0.95;
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
void setTimeStep(MaxUStencil &maxUStencil,Parameters &parameters,FlowField &flowField){

	FLOAT localMin, globalMin;

	assertion(flowField.getDim() == 2 || flowField.getDim() == 3);
	FLOAT factor = 1/(parameters.geometry.dx * parameters.geometry.dx) +
			1/(parameters.geometry.dy * parameters.geometry.dy);
	if (flowField.getDim() == 3) {
		factor += 1/(parameters.geometry.dz * parameters.geometry.dz);
		parameters.timestep.dt = parameters.geometry.dz / maxUStencil.getMaxValues()[2];
	} else {
		parameters.timestep.dt = parameters.flow.Re / 2 / factor;
	}

	localMin = std::min(parameters.timestep.dt,
			std::min(std::min(parameters.flow.Re/(2*factor),
					parameters.geometry.dx / maxUStencil.getMaxValues()[0]),
					parameters.geometry.dy / maxUStencil.getMaxValues()[1]));

	// Here, we select the type of operation before compiling. This allows to use the correct
	// data type for MPI. Not a concern for small simulations, but useful if using heterogeneous
	// machines.

	globalMin = MY_FLOAT_MAX;
	MPI_Allreduce(&localMin, &globalMin, 1, MY_MPI_FLOAT, MPI_MIN, PETSC_COMM_WORLD);

	parameters.timestep.dt = globalMin;
	parameters.timestep.dt *= parameters.timestep.tau;
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
extern "C" void main_loop_(bool);
void test(int argc ,char**argv){

	std::cout<<"start solving loop ns"<<std::endl;
	FLOAT time=0;
	Configuration configuration(argv[1]);
	Parameters parameters;
	configuration.loadParameters(parameters);
	PetscParallelConfiguration parallelConfiguration(
			parameters,
			parameters.geometry.sizeX,
			parameters.geometry.sizeY,
			parameters.geometry.sizeZ);


	FlowField flowField(parameters);
	std::cout<<"flow field created"<<std::endl;
	PetscSolver solver (flowField, parameters);
	std::cout<<"petsc solver created"<<std::endl;
	// Get the boundary stencils with the factory
	GlobalBoundaryFactory factory (parameters);
	std::cout<<"factory created"<<std::endl;
	GlobalBoundaryIterator<FlowField> wallVelocityIterator (factory.getGlobalBoundaryVelocityIterator(flowField));
	GlobalBoundaryIterator<FlowField> wallFGHIterator (factory.getGlobalBoundaryFGHIterator(flowField));
	std::cout<<"boundary created"<<std::endl;
	FGHStencil fghStencil(parameters);
	FieldIterator<FlowField> fghIterator(flowField, fghStencil);

	RHSStencil rhsStencil(parameters);
	FieldIterator<FlowField> rhsIterator(flowField, rhsStencil);

	VelocityStencil velocityStencil(parameters);
	FieldIterator<FlowField> velocityIterator(flowField, velocityStencil);

	MaxUStencil maxUStencil(parameters);
	FieldIterator<FlowField> maxUFieldIterator(flowField, maxUStencil);
	GlobalBoundaryIterator<FlowField> maxUBoundaryIterator(flowField, parameters, maxUStencil, 1, 0);
	std::cout<<"petsc parallel"<<std::endl;
	PetscParallelManager parallelManager(flowField, parameters);
	//LBNSFGHCorrectionIterator LBNSFGHCorrectionIterator(parameters, flowField);
	//LBNSInitFlagsIterator initFlagsIterator(parameters, flowField);
	VTKStencil vtkStencil( parameters );
	FieldIterator<FlowField> vtkIterator( flowField, vtkStencil, 1, 0 );

	//initFlagsIterator.iterate();
	std::cout<<"starting time loop"<<std::endl;
	// time loop
	//std::cout << "Performing cycle " << bigloop << std::endl;
	time = 0.0;
	parameters.coupling.set = false;
	while (time < parameters.simulation.finalTime){

		// Get the time step
		std::cout<<" u reset"<<std::endl;
		maxUStencil.reset();    // Not that nice
		std::cout<<" u field"<<std::endl;
		maxUFieldIterator.iterate();
		std::cout<<" u boundary"<<std::endl;
		maxUBoundaryIterator.iterate();
		std::cout<<" time"<<std::endl;
		setTimeStep(maxUStencil, parameters, flowField);
		std::cout<<"fgh"<<std::endl;
		// compute fgh
		fghIterator.iterate();
		std::cout<<"wall fgh"<<std::endl;
		// set global boundary values
		wallFGHIterator.iterate();

		// set velocities from lb in ns
		//lbnsCouplingIterator.iterateBoundary();
		// Set FGH in coupling boundaries
		//LBNSFGHCorrectionIterator.iterate();
		std::cout<<"rhs"<<std::endl;
		// compute the right hand side
		rhsIterator.iterate();
		std::cout<<"solve"<<std::endl;
		// solve for pressure
		solver.solve();
		std::cout<<"comm"<<std::endl;
		parallelManager.communicatePressure();
		std::cout<<"v it"<<std::endl;
		// compute velocity
		velocityIterator.iterate();
		std::cout<<"p com v"<<std::endl;
		parallelManager.communicateVelocity();
		std::cout<<" wall v"<<std::endl;
		// Iterate for velocities on the boundary
		wallVelocityIterator.iterate();
		//lbnsCouplingIterator.iterateBoundary();
		// Transfer velocity from LB to NS
		// lbnsCouplingIterator.iterate();
		std::cout<<"dt++"<<std::endl;
		time += parameters.timestep.dt;
		std::cout<<"time:"<<time<<std::endl;
		// if ( (timeSteps % parameters.stdOut.interval) == 0 && rank == 0) {
		//     std::cout << "Current time: " << time << "\ttimestep: " <<
		//         parameters.timestep.dt << std::endl;
		// }
		// timeSteps++;
		vtkStencil.openFile ( flowField, (float)0 );
		vtkIterator.iterate();
		vtkStencil.write( flowField );
		vtkStencil.closeFile();
	}


}
void testGather(int argc ,char**argv){
	int rank=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int size=0;
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	std::vector<int> data(rank+1);
	std::vector<int> data_size(size);
	std::vector<int> displ;
	if(rank==0){
		data[0]=1;
	}else if(rank==1){
		data[0]=2;
		data[1]=3;
	}else if(rank==2){
		data[0]=4;
		data[1]=5;
		data[2]=6;
	}else if(rank==3){
		data[0]=7;
		data[1]=8;
		data[2]=9;
		data[3]=10;
	}else if(rank==4){
		data[0]=11;
		data[1]=12;
		data[2]=13;
		data[3]=14;
		data[4]=15;
	}else if(rank==5){
		data[0]=16;
		data[1]=17;
		data[2]=18;
		data[3]=19;
		data[4]=20;
		data[5]=21;
	}
	int count=data.size();

	MPI_Gather(&count,1, MPI_INT, &data_size[0], 1, MPI_INT,2, MPI_COMM_WORLD);
	if(rank==2){
		displ.resize(size);

		displ[rank]=0;

		for(int i=0;i<size;i++){
			if(i!=rank){
				displ[i]=count;
				count+=data_size[i];
			}
		}
	}
	data.resize(count);
	if(rank==2)
		MPI_Gatherv(MPI_IN_PLACE,0, MPI_INT,&data[0], &data_size[0],&displ[0], MPI_INT,2, MPI_COMM_WORLD);
	else
		MPI_Gatherv(&data[0],count, MPI_INT,&data[0], &data_size[0],&displ[0], MPI_INT,2, MPI_COMM_WORLD);

	if(rank==2){
		for(int i=0;i<data.size();i++)
			std::cout<<" "<<data[i];
		std::cout<<std::endl;
	}
}

int main(int argc, char *argv[]){
	int provided;
	MPI_Init_thread(&argc,&argv,MPI_THREAD_MULTIPLE ,&provided);
	//testGather(argc,argv);
	//MPI_Finalize();
	PetscInitialize(&argc, &argv, PETSC_NULL, PETSC_NULL);
	//test(argc,argv);
	main_loop_(true);
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
	//_parameters.coupling.set=true;
	_configuration= new Configuration(inputScenario);

	_configuration->loadParameters(_parameters);
	_parameters.coupling.set = true;
	std::cout<<"parame:"<<_parameters.geometry.sizeX<<","<<_parameters.geometry.sizeY<<std::endl;
	PetscParallelConfiguration parallelConfiguration(_parameters,
			_parameters.geometry.sizeX,
			_parameters.geometry.sizeY,
			_parameters.geometry.sizeZ);
	if(_parameters.coupling.set)
		_lbField = new LBField(_parameters,
				_parameters.coupling.sizeNS[0] * _parameters.coupling.ratio-1,
				_parameters.coupling.sizeNS[1] * _parameters.coupling.ratio-1,
				_parameters.coupling.sizeNS[2] * _parameters.coupling.ratio-1);


	_flowField = new FlowField(_parameters);
	//		assert(_flowField);
	_simulation = new Simulation(_parameters,*_flowField);
	LBNSInitFlagsIterator lbnsInitFlagsIterator(_parameters,*_flowField);
	//
	lbnsInitFlagsIterator.iterate();
	if(_parameters.coupling.set)
	{
		_lbnsCouplingIterator = new LBNSCouplingIterator(_parameters,*_flowField);
		//assert(_simulation);
		gatherDomainDescriptions();
		gatherMids();

		if(_parameters.parallel.rank==0&&_lb){
			int regionSize=3*_parameters.parallel.numProcessors[0]*_parameters.parallel.numProcessors[1]*_parameters.parallel.numProcessors[2];
			_lb->setupCommForNSRegionParallel(
					&_startDomain[0],
					regionSize,
					&_endDomain[0],
					regionSize,
					&_mids[0],
					regionSize/3);
			int atr;
			_lb->syncr(atr);
		}
		_nslbStencil = new NSLBCouplingStencil (
				_parameters,
				*_lbField,
				*_flowField);
		_nslbCouplingIterator =  new SmartGlobalBoundaryIterator<LBField> (*_lbField,_parameters, *_nslbStencil);

		for(unsigned int i=0;i<_coms.size();i++)
			_nslbStencil->registerLBRegion(_coms[i]);
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

	std::cout<<"start solving loop ns"<<std::endl;
	FLOAT time=0;
	_parameters.coupling.set=false;
	iqn(_nslbStencil->getCouplingData(),_lbnsCouplingIterator->getCouplingData(),_nslbStencil->getSecondaryCouplingData());

	_nslbStencil->getCouplingData().clear();
	_nslbStencil->getSecondaryCouplingData().clear();

	while (time <=_parameters.simulation.finalTime){
		_simulation->solveTimestepPhaseOne();
		_lbnsCouplingIterator->iterateBoundary();
		_simulation->solveTimestepPhaseTwo();
		_lbnsCouplingIterator->iterateBoundary();
		//time++;
		time += _parameters.timestep.dt;
		//std::cout<<"time:"<<time<<std::endl;

	}
	std::cout<<"clear mapping"<<std::endl;
	_lbnsCouplingIterator->clear();

	std::cout<<"clear mapping end"<<std::endl;
	MPI_Barrier(MPI_COMM_WORLD);
	pthread_mutex_unlock(&_mutex);

}
void cca::cfd::NSImplementation::iterateBoundary(){
	pthread_mutex_lock(&_mutex);
	//_lbnsCouplingIterator->iterateBoundary();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::iterateInner(){
	pthread_mutex_lock(&_mutex);
	//_lbnsCouplingIterator->iterateInner();
	pthread_mutex_unlock(&_mutex);
}
void cca::cfd::NSImplementation::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
	//	pthread_mutex_lock(&_mutex);
	//	_lbnsCouplingIterator->setLBVelocities((double*)velocitiesX,(double*)velocitiesY,(double*)velocitiesZ,
	//			velocitiesX_len,velocitiesY_len,velocitiesZ_len);
	//	pthread_mutex_unlock(&_mutex);
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
void cca::cfd::NSImplementation::iqn(std::vector<double>& nslb,std::vector<double>& lbns,std::vector<double>& secondary){
	if(_iter>=2){
		precice::utils::DynVector dvalues;
		//		double nslb_min=nslb[0];
		//		double nslb_max=nslb[0];
		//		double lbns_min=lbns[0];
		//		double lbns_max=lbns[0];
		//		double secondary_min=secondary[0];
		//		double secondary_max=secondary[0];
		//		int nslb_min_index=0,nslb_max_index=0;
		//		int lbns_min_index=0,lbns_max_index=0;
		//		int secondary_min_index=0,secondary_max_index=0;
		//
		//
		//		for(unsigned int i=0;i<nslb.size();i++){
		//			if(nslb[i]< nslb_min){
		//				nslb_min=nslb[i];
		//				nslb_min_index=i;
		//			}
		//			if(nslb[i]>nslb_max){
		//				nslb_max=nslb[i];
		//				nslb_max_index=i;
		//			}
		//		}
		//		for(unsigned int i=0;i<lbns.size();i++){
		//			if(lbns[i]< lbns_min){
		//				lbns_min=lbns[i];
		//				lbns_min_index=i;
		//			}
		//			if(lbns[i]>lbns_max){
		//				lbns_max=lbns[i];
		//				lbns_max_index=i;
		//			}
		//		}
		//		for(unsigned int i=0;i<secondary.size();i++){
		//			if(secondary[i]< secondary_min){
		//				secondary_min=secondary[i];
		//				secondary_min_index=i;
		//			}
		//			if(secondary[i]>secondary_max){
		//				secondary_max=secondary[i];
		//				secondary_max_index=i;
		//			}
		//		}
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
			std::cout<<"init cpl iqn nsv:"<<nslb.size()<<" lbv:"<<lbns.size()<<" nsp:"<<secondary.size()<<std::endl;
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
		double normDiff = tarch::la::norm2((*_data.at(0)->values) - _data.at(0)->oldValues.column(0));
		double norm = tarch::la::norm2((*_data.at(0)->values));
		_mcFile <<  normDiff << "\t" << norm <<  "\t";
		normDiff = tarch::la::norm2((*_data.at(1)->values) - _data.at(1)->oldValues.column(0));
		norm = tarch::la::norm2((*_data.at(1)->values));
		_mcFile <<  normDiff << "\t" << norm <<  "\t";
		normDiff = tarch::la::norm2((*_data.at(2)->values) - _data.at(2)->oldValues.column(0));
		norm = tarch::la::norm2((*_data.at(2)->values));
		_mcFile <<  normDiff << "\t" << norm <<  "\n";
		_mcFile.flush();
		_pp->performPostProcessing(_data);
		_data.at(0)->oldValues.column(0) = (*_data.at(0)->values);
		_data.at(1)->oldValues.column(0) =(*_data.at(1)->values);
		_data.at(2)->oldValues.column(0) =(*_data.at(2)->values);

		for(unsigned int i=0;i<_data.at(1)->values->size();i++){
			lbns[i]=(*_data.at(1)->values)(i)/scale;

		}
	}

}
void cca::cfd::NSImplementation::iterate(){
	pthread_mutex_lock(&_mutex);

	//	std::cout<<"starting ns stencil iter"<<std::endl;
	//_nslbStencil->computeBoundaryMeanPressure();

	_nslbCouplingIterator->iterate();
	if(_maxSizeCommunicators.size()==0){
		_maxSizeCommunicators.resize(_comC*2);
		_sizeCommunicators.resize(_comC*2);
		_nslbStencil->initGather();
		MPI_Allreduce(&_sizeCommunicators[0],&_maxSizeCommunicators[0],_comC,MPI_2INT,MPI_MAXLOC,MPI_COMM_WORLD);
		std::cout<<"init gather finished"<<std::endl;
		for(int i=0;i<_comC;i++){
			std::cout<<"region i:"<<i<<_maxSizeCommunicators[i*2+1]<<" data:"<<_maxSizeCommunicators[i*2]<<std::endl;
		}
	}

	_nslbStencil->flush();
	MPI_Barrier(MPI_COMM_WORLD);
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

void cca::cfd::NSImplementation::gatherDomainDescriptions(){
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
void cca::cfd::NSImplementation::gatherMids(){
	std::string mid=retrieveSocketAddress();
	_mids.push_back(mid);
	int comm_size=0;
	MPI_Comm_size(MPI_COMM_WORLD,&comm_size);

	if(comm_size>0)
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
				std::cout<<"rank:"<<i<<" mid:"<<std::string(&buff[0])<<std::endl;
				_mids.push_back(std::string(&buff[0]));
			}
		}

}

void cca::cfd::NSImplementation::setupCommForLBRegion(
		const int* startOfRegion,
		const int startOfRegion_len,
		const int* endOfRegion,
		const int endOfRegion_len,
		const std::string* commids,
		const int commids_len){
	pthread_mutex_lock(&_mutex);
	int *start = (int*)startOfRegion;
	int *end = (int*)endOfRegion;
	for(int i=0;i<commids_len;i++){
		//		if(_parameters.parallel.rank==0){
		std::cout<<"lb_start region:"<<i<<","<<commids[i]<<"start_r:["<<startOfRegion[i*3]<<","<<startOfRegion[i*3+1]<<","<<startOfRegion[i*3+2]<<"]"<<std::endl;
		std::cout<<"lb_end region:"<<i<<","<<commids[i]<<"start_r:["<<endOfRegion[i*3]<<","<<endOfRegion[i*3+1]<<","<<endOfRegion[i*3+2]<<"]"<<std::endl;
		std::cout<<"ns_rank:"<<_parameters.parallel.rank<<","<<_lbnsCouplingIterator<<std::endl;
		//		}


		NSLBCommunicator* com=new NSLBCommunicator(
				_parameters,i,(int*)startOfRegion,(int*)endOfRegion,commids[i],
				_maxSizeCommunicators,_sizeCommunicators);
		if(_nslbStencil)
			_nslbStencil->registerLBRegion(com);
		else{
			_coms.push_back(com);
		}
	}
	//MPI_Barrier(MPI_COMM_WORLD);
	_comC=commids_len;
	pthread_mutex_unlock(&_mutex);
}


void cca::cfd::NSImplementation::forwardVelocities(
		const int * keys,
		const int keys_len,
		const int * offsets,
		const int offsets_len,
		const int * flips,
		const int flips_len,
		const double* values,
		const int values_len,
		int& ackn){
	pthread_mutex_lock(&_mutex);

	for (int i=0;i<keys_len;i++){
		_lbnsCouplingIterator->setVelocity(
				keys[i],
				offsets[3*i],
				offsets[3*i+1],
				offsets[3*i+2],
				flips[3*i],
				flips[3*i+1],
				flips[3*i+2],
				values[i]);

	}
	pthread_mutex_unlock(&_mutex);
}

