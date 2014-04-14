#include "cca/cfd/CouplingDriverImplementation.h"
#include <petsc.h>
#include "examples/cfd/lb/LBField.h"
const FLOAT oneThird = 1.0 / 3.0;
/** A simple rounding function.
 * @param Floating point input number
 * @return Integer closest to the value of the input
 */
int myRound (FLOAT n){
	return (int)floor(n + 0.5);
}
cca::cfd::CouplingDriverImplementation::CouplingDriverImplementation():
						_configuration(NULL){

}

cca::cfd::CouplingDriverImplementation::~CouplingDriverImplementation(){
	if(_configuration){
		delete _configuration;
	}
}

double cca::cfd::CouplingDriverImplementation::computePhysicalLBTimeStep(){

	return _parameters.flow.Re * oneThird * (_parameters.lb.tau - 0.5) *
			_parameters.geometry.dx * _parameters.geometry.dx / (_parameters.coupling.ratio * _parameters.coupling.ratio);
}


extern "C" void main_loop_();
int main(int argc, char *argv[]){
	PetscInitialize(&argc, &argv, PETSC_NULL, PETSC_NULL);
	main_loop_();
	PetscFinalize();
}

void cca::cfd::CouplingDriverImplementation::go(const std::string configFile){
	Configuration configuration (configFile.c_str());
	configuration.loadParameters(_parameters, MPI_COMM_WORLD);
	const FLOAT LBTimeStep = computePhysicalLBTimeStep();
	// This is the value that we expect the timestep to have
	const FLOAT NSTimeStep = 0.5 * _parameters.timestep.tau * _parameters.flow.Re /
			(3 / (_parameters.geometry.dx * _parameters.geometry.dx));

	const FLOAT timeRatio = myRound(NSTimeStep / LBTimeStep);

	const FLOAT rTimeRatio = LBTimeStep / NSTimeStep;

	std::vector<double>  lbVelocityX;
	std::vector<double>  lbVelocityY;
	std::vector<double>  lbVelocityZ;
	std::vector<double>  nsVelocityX;
	std::vector<double>  nsVelocityY;
	std::vector<double>  nsVelocityZ;
	std::vector<double>  nsPressure;
	std::vector<double>  nsJacobian;
	//_ns->setup(configFile);
	_lb->setupParallel(configFile);
	_ns->setupParallel(configFile);


//	_lb->solveParallel();
//	_lb->plotParallel();
	double timeSteps=1000;
	//LBField lbField(_parameters);
	double time = 0.0;
	double dt=0.0;
	int velocitiesLB_X=0;
	int velocitiesLB_Y=0;
	int velocitiesLB_Z=0;
	int velocitiesNS=0;
	for (int bigloop = 0; bigloop < 20; bigloop++){
		std::cout << "Performing cycle " << bigloop << std::endl;

		_lb2ns->iterateBoundaryParallel();

		_lb2ns->retrieveTimestep(dt);
		_ns->solveParallel();
		_ns2lb->iterateParallel();
		_ns2lb->retrieveTimestep(dt);

		_lb->solveParallel();
		//_lb->plotParallel();
		/*_lb2ns->iterateInner();
				_lb2ns->retrieveVelocitiesSize(velocitiesLB_X,velocitiesLB_Y,velocitiesLB_Z);
				lbVelocityX.resize(velocitiesLB_X);
				lbVelocityY.resize(velocitiesLB_Y);
				lbVelocityZ.resize(velocitiesLB_Z);
				_lb2ns->retrieveVelocitiesCopy(
									&lbVelocityX[0],
									velocitiesLB_X,
									&lbVelocityY[0],
									velocitiesLB_Y,
									&lbVelocityZ[0],
									velocitiesLB_Z);
				_ns->setVelocities(
								&lbVelocityX[0],
								velocitiesLB_X,
								&lbVelocityY[0],
								velocitiesLB_Y,
								&lbVelocityZ[0],
								velocitiesLB_Z);
				_ns->iterateInner();
		_ns->printNSPressure();

		_ns2lb->iterate();
		_ns2lb->retrieveVelocitiesSize(velocitiesNS);
		nsVelocityX.resize(velocitiesNS);
		nsVelocityY.resize(velocitiesNS);
		nsVelocityZ.resize(velocitiesNS);
		nsJacobian.resize(velocitiesNS*9);
		nsPressure.resize(velocitiesNS);
		_ns2lb->retrieveVelocitiesCopy(
				&nsVelocityX[0],
				velocitiesNS,
				&nsVelocityY[0],
				velocitiesNS,
				&nsVelocityZ[0],
				velocitiesNS);
		_ns2lb->retrieveJacobianCopy(&nsJacobian[0],velocitiesNS*9);
		_ns2lb->retrievePressureCopy(&nsPressure[0],velocitiesNS);

		_lb->setVelocities(&nsVelocityX[0],velocitiesNS,&nsVelocityY[0],velocitiesNS,&nsVelocityZ[0],velocitiesNS);
		_lb->setGradients(&nsJacobian[0],velocitiesNS*9);
		_lb->setPressure(&nsPressure[0],velocitiesNS);

		const int lbIterations = 10000;
		// The original experiments had a field of size 40
		for (int i = 0; i < lbIterations * (lbField.getCellsZ()-1) * (lbField.getCellsZ()-1) / (40*40); i++){
			_lb->solveOneTimestep();
		}
	    */
		//_lb->printLBProfiles();
		//_ns->printNSProfiles();
		//_lb->plot();
		_lb->plotParallel();
		_ns->plotParallel();
	}
	//_ns->closeNSProfiles();
	//_lb->closeLBProfiles();

}
