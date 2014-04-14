#ifndef CCA_CFD_LBIMPLEMENTATION_H_
#define CCA_CFD_LBIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include "cca/cfd/LBAbstractImplementation.h"
#include <string>
#include "examples/kernel/Parameters.h"
#include "examples/cfd/lb/LBField.h"
#include "examples/cfd/lb//stencils/LBStreamAndCollideStencil.h"
#include "examples/cfd/lb/stencils/LBBounceBackStencil.h"
#include "examples/cfd/lb/stencils/LBVTKStencil.h"
#include "examples/cfd/lb/stencils/LBMovingWallStencil.h"
#include "examples/cfd/lb/coupling/LBNSCouplingIterator.h"
#include "examples/cfd/lb/coupling/NSLBCouplingStencil.h"
#include "examples/cfd/lb/parallelManagers/LBParallelManager.h"
#include "Iterators.h"
#include <pthread.h>
#include <fstream>
namespace cca { 
namespace cfd { 

class LBImplementation;
} 
}
class Configuration;
class LBNSCommunicator;
class cca::cfd::LBImplementation : public cca::cfd::LBAbstractImplementation{
private:
	pthread_mutex_t _mutex;
	Configuration* _configuration;
	Parameters _parameters;
	LBField* _lbField;
	LBStreamAndCollideStencil* _streamAndCollideStencil;
	FieldIterator<LBField>* _streamAndCollideIterator;
	LBBounceBackStencil* _bounceBackStencil;
	FieldIterator<LBField>* _bounceBackIterator;
	LBNSCouplingIterator* _lbnsCouplingIterator;
	NSLBCouplingStencil *_nslbCouplingStencil;
	GlobalBoundaryIterator<LBField> *_nslbCouplingIterator;
	LBParallelManager* _parallelManager;
	LBMovingWallStencil *_movingWallStencil;
	GlobalBoundaryIterator<LBField>* _movingWallIterator;
	std::ofstream _lbprofiles;
	std::ofstream _lbvelocitycenter;
	std::ofstream _lbdensityalong;
	std::ofstream _lbdensitycenter;
	int _iter;
	bool _setupFinished;
	std::vector<int> _startDomain;
	std::vector<int> _endDomain;
	std::vector<std::string> _mids;
	int _iterC;
	std::vector<LBNSCommunicator*> _coms;
	void gatherDomainDescriptions();
	void gatherMids();
public:
	LBImplementation();
	~LBImplementation();
	void setup(const std::string inputScenario);
	void solve();
	void solveOneTimestep();
	void setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);
	void setPressure(const double* pressure, const int pressure_len);
	void setGradients(const double* gradients, const int gradients_len);
	void plot();
	void iterateBoundary();
	void iterateInner();
	void retrieveVelocitiesSize(int& memoryX,int& memoryY,int& memoryZ);
	void retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);
	void closeLBProfiles();
	void printLBDensity();
	void printLBProfiles();
	void setupCommForNSRegion(
			const int* startOfRegion,
			const int startOfRegion_len,
			const int* endOfRegion,
			const int endOfRegion_len,
			const std::string* commids,
			const int commids_len);
	void forwardVelocities(
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
			int& ack);
	void forwardPressure(
			const int * keys,
			const int keys_len,
			const int * offsets,
			const int offsets_len,
			const int * flips,
			const int flips_len,
			const double* values,
			const int values_len,
			int& ack);
	void retrieveTimestep(double& timestep){

	}
	void syncr(int& atr){

		}

};     


#endif