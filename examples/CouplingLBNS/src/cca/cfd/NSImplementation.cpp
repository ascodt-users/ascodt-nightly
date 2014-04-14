#include "cca/cfd/NSImplementation.h"
#include <petsc.h>
#include "examples/kernel/Configuration.h"
#include <assert.h>
#include "examples/cfd/ns/Simulation.h"
#include "PetscParallelConfiguration.h"
#include "examples/cfd/ns/coupling/LBNSFGHCorrectionIterator.h"
#include "examples/cfd/ns/coupling/LBNSInitFlagsIterator.h"
#include "examples/cfd/ns/coupling/NSLBCommunicator.h"
#include <unistd.h>
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
extern "C" void main_loop_();
void test(int argc ,char**argv){

	std::cout<<"start solving loop ns"<<std::endl;
	FLOAT time=0;
	//_parameters.coupling.set = false;
	Configuration configuration(argv[1]);
	Parameters parameters;
	configuration.loadParameters(parameters);
	PetscParallelConfiguration parallelConfiguration(parameters);


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
	LBNSFGHCorrectionIterator LBNSFGHCorrectionIterator(parameters, flowField);
	LBNSInitFlagsIterator initFlagsIterator(parameters, flowField);
	 VTKStencil vtkStencil( parameters );
	    FieldIterator<FlowField> vtkIterator( flowField, vtkStencil, 1, 0 );

	initFlagsIterator.iterate();
	std::cout<<"starting time loop"<<std::endl;
	// time loop
	//std::cout << "Performing cycle " << bigloop << std::endl;
	time = 0.0;
	parameters.coupling.set = false;
	while (time < parameters.simulation.finalTime){

		// Get the time step
		maxUStencil.reset();    // Not that nice
		maxUFieldIterator.iterate();
		maxUBoundaryIterator.iterate();
		setTimeStep(maxUStencil, parameters, flowField);

		// compute fgh
		fghIterator.iterate();

		// set global boundary values
		wallFGHIterator.iterate();

		// set velocities from lb in ns
		//lbnsCouplingIterator.iterateBoundary();
		// Set FGH in coupling boundaries
		LBNSFGHCorrectionIterator.iterate();

		// compute the right hand side
		rhsIterator.iterate();

		// solve for pressure
		solver.solve();

		parallelManager.communicatePressure();

		// compute velocity
		velocityIterator.iterate();

		parallelManager.communicateVelocity();

		// Iterate for velocities on the boundary
		wallVelocityIterator.iterate();
		//lbnsCouplingIterator.iterateBoundary();
		// Transfer velocity from LB to NS
		// lbnsCouplingIterator.iterate();

		time += parameters.timestep.dt;
		std::cout<<"time:"<<time<<std::endl;
		// if ( (timeSteps % parameters.stdOut.interval) == 0 && rank == 0) {
		//     std::cout << "Current time: " << time << "\ttimestep: " <<
		//         parameters.timestep.dt << std::endl;
		// }
		// timeSteps++;
	}
	vtkStencil.openFile ( flowField, (float)0 );
	vtkIterator.iterate();
	vtkStencil.write( flowField );
	vtkStencil.closeFile();

}
int main(int argc, char *argv[]){
	int provided;
	MPI_Init_thread(&argc,&argv,MPI_THREAD_MULTIPLE ,&provided);

	PetscInitialize(&argc, &argv, PETSC_NULL, PETSC_NULL);
	//test(argc,argv);
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
	//_parameters.coupling.set=true;
	_configuration= new Configuration(inputScenario.c_str());

	_configuration->loadParameters(_parameters);
	_parameters.coupling.set=false;
	PetscParallelConfiguration parallelConfiguration(_parameters);
	_parameters.coupling.set=true;
	//
	_flowField = new FlowField(_parameters);
	//		assert(_flowField);
	_simulation = new Simulation(_parameters,*_flowField);
	LBNSInitFlagsIterator lbnsInitFlagsIterator(_parameters,*_flowField);

	lbnsInitFlagsIterator.iterate();

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

			_lbField = new LBField(_parameters);
			_nslbStencil = new NSLBCouplingStencil (
					_parameters,
					*_lbField,
					*_flowField);
			_nslbCouplingIterator =  new GlobalBoundaryIterator<LBField> (*_lbField,_parameters, *_nslbStencil);
			for(unsigned int i=0;i<_coms.size();i++)
				_nslbStencil->registerLBRegion(_coms[i]);



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
	while (time <=_parameters.simulation.finalTime){
		_simulation->solveTimestepPhaseOne();
		_lbnsCouplingIterator->iterateBoundary();
		_simulation->solveTimestepPhaseTwo();
		_lbnsCouplingIterator->iterateBoundary();
		time += _parameters.timestep.dt;
		std::cout<<"time:"<<time<<std::endl;

	}
	_lbnsCouplingIterator->clear();
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
void cca::cfd::NSImplementation::iterate(){
	pthread_mutex_lock(&_mutex);
	std::cout<<"starting ns stencil iter"<<std::endl;
	_parameters.coupling.set=true;
		_nslbStencil->computeBoundaryMeanPressure();

		_nslbCouplingIterator->iterate();
		_nslbStencil->flush();
	_parameters.coupling.set=false;
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


		NSLBCommunicator* com=new NSLBCommunicator(_parameters,i,(int*)startOfRegion,(int*)endOfRegion,commids[i]);
		if(_nslbStencil)
			_nslbStencil->registerLBRegion(com);
		else{
			_coms.push_back(com);
		}
	}
	//MPI_Barrier(MPI_COMM_WORLD);
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
		const int* componentSize,
		const int componentSize_len,
		int& ackn){
	pthread_mutex_lock(&_mutex);
	int offset=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<componentSize[i];j++){
			_lbnsCouplingIterator->setVelocity(
					keys[offset+j],
					offsets[3*(offset+j)],
					offsets[3*(offset+j)+1],
					offsets[3*(offset+j)+2],
					flips[3*(offset+j)],
					flips[3*(offset+j)+1],
					flips[3*(offset+j)+2],
					i,
					values[offset+j]);


		}
		offset+=componentSize[i];
	}
	pthread_mutex_unlock(&_mutex);
}

