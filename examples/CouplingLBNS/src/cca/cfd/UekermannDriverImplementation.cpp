#include "cca/cfd/UekermannDriverImplementation.h"
#include <sys/time.h>
cca::cfd::UekermannDriverImplementation::UekermannDriverImplementation(){

}

cca::cfd::UekermannDriverImplementation::~UekermannDriverImplementation(){

}
extern "C" void main_loop_();
int main(){
     main_loop_();
}

void cca::cfd::UekermannDriverImplementation::exchangeBoundaries(){
	int velocitiesLB_X=0;
	int velocitiesLB_Y=0;
	int velocitiesLB_Z=0;
	int velocitiesNS=0;
	_lb2ns->iterateBoundary();
	_lb2ns->retrieveVelocitiesSize(velocitiesLB_X,velocitiesLB_Y,velocitiesLB_Z);
	_lbVelocityX.resize(velocitiesLB_X);
	_lbVelocityY.resize(velocitiesLB_Y);
	_lbVelocityZ.resize(velocitiesLB_Z);
	_lb2ns->retrieveVelocitiesCopy(
			&_lbVelocityX[0],
			velocitiesLB_X,
			&_lbVelocityY[0],
			velocitiesLB_Y,
			&_lbVelocityZ[0],
			velocitiesLB_Z);
	_ns->setVelocities(
			&_lbVelocityX[0],
			velocitiesLB_X,
			&_lbVelocityY[0],
			velocitiesLB_Y,
			&_lbVelocityZ[0],
			velocitiesLB_Z);

	_ns2lb->iterate();
	_ns2lb->retrieveVelocitiesSize(velocitiesNS);
	_nsVelocityX.resize(velocitiesNS);
	_nsVelocityY.resize(velocitiesNS);
	_nsVelocityZ.resize(velocitiesNS);
	_nsJacobian.resize(velocitiesNS*9);
	_nsPressure.resize(velocitiesNS);
	_ns2lb->retrieveVelocitiesCopy(
			&_nsVelocityX[0],
			velocitiesNS,
			&_nsVelocityY[0],
			velocitiesNS,
			&_nsVelocityZ[0],
			velocitiesNS);
	_ns2lb->retrieveJacobianCopy(&_nsJacobian[0],velocitiesNS*9);
	_ns2lb->retrievePressureCopy(&_nsPressure[0],velocitiesNS);

	_lb->setVelocities(&_nsVelocityX[0],velocitiesNS,&_nsVelocityY[0],velocitiesNS,&_nsVelocityZ[0],velocitiesNS);
	_lb->setGradients(&_nsJacobian[0],velocitiesNS*9);
	_lb->setPressure(&_nsPressure[0],velocitiesNS);
}
void cca::cfd::UekermannDriverImplementation::go(const std::string configFile){
	_ns->setup(configFile);
	_lb->setup(configFile);
	 timeval t1, t2;
	    double elapsedTime;
	 gettimeofday(&t1, NULL);
	for (int bigloop = 0; bigloop < 40; bigloop++){
		std::cout << "Performing cycle " << bigloop << std::endl;
		exchangeBoundaries();
		_ns->solve();
		_lb->solve();
		_ns->printNSPressure();
		_ns->printNSProfiles();
		//_lb->plot();
		//_ns->plot();
	}
	_ns->closeNSProfiles();
	_lb->closeLBProfiles();
	 gettimeofday(&t2, NULL);
	 elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
	 std::cout << elapsedTime << " ms.\n";
}
