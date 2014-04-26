#include "cca/cfd/UekermannDriverImplementation.h"

#include <sys/time.h>
 cca::cfd::UekermannDriverImplementation* cca::cfd::UekermannDriverImplementation::singleton=NULL;
cca::cfd::UekermannDriverImplementation::UekermannDriverImplementation(){
	singleton=this;
}

cca::cfd::UekermannDriverImplementation::~UekermannDriverImplementation(){

}
extern "C" void main_loop_(bool);
int main(int argc, char *argv[]){
	int provided;
	MPI_Init_thread(&argc,&argv,MPI_THREAD_MULTIPLE ,&provided);
	std::cout<<"main loop"<<std::endl;
	main_loop_(false);
	cca::cfd::UekermannDriverImplementation::singleton->go(argv[1]);
}

void cca::cfd::UekermannDriverImplementation::exchangeBoundaries(){
	double dt=0;
	int fl;

	_ns->syncr(fl);
	_lb->syncr(fl);
	_lb2ns->iterateBoundaryParallel();
	_lb2ns->retrieveTimestep(dt);
	_ns2lb->iterateParallel();
	_ns2lb->retrieveTimestep(dt);

}
void cca::cfd::UekermannDriverImplementation::go(const std::string configFile){
	int fl;
	_ns->setupParallel(configFile);
	_ns->syncr(fl);
	_lb->setupParallel(configFile);
	_lb->syncr(fl);
	for (int bigloop = 0; bigloop < 40; bigloop++){
		std::cout << "Performing cycle " << bigloop << std::endl;
		exchangeBoundaries();
		_ns->solveParallel();
		_lb->solveParallel();
		//		_ns->printNSPressure();
		//		_ns->printNSProfiles();
		_ns->plotParallel();
		_lb->plotParallel();
		//_lb->plot();
		//_ns->plot();
	}
	//_ns->closeNSProfiles();
	//_lb->closeLBProfiles();
	//	 gettimeofday(&t2, NULL);
	//	 elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
	//	    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
	//	 std::cout << elapsedTime << " ms.\n";
}
