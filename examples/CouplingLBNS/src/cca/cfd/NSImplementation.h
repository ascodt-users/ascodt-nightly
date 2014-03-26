#ifndef CCA_CFD_NSIMPLEMENTATION_H_
#define CCA_CFD_NSIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include "cca/cfd/NSAbstractImplementation.h"
#include <string>
#include "examples/kernel/Parameters.h"
#include "examples/cfd/ns/coupling/LBNSCouplingIterator.h"
#include "examples/cfd/ns/coupling/NSLBCouplingStencil.h"
#include "examples/cfd/lb/LBField.h"
#include "Iterators.h"
#include <vector>
#include <pthread.h>
#include <fstream>
namespace cca { 
namespace cfd { 
  
     class NSImplementation;
} 
}
class Configuration;
class FlowField;
class Simulation;
class cca::cfd::NSImplementation : public cca::cfd::NSAbstractImplementation{
private:
	pthread_mutex_t _mutex;
	Configuration* _configuration;
	FlowField *_flowField;
	Simulation *_simulation;
	Parameters _parameters;
	LBNSCouplingIterator *_lbnsCouplingIterator;
	NSLBCouplingStencil *_nslbStencil;
	GlobalBoundaryIterator<LBField> *_nslbCouplingIterator;
	std::vector<double> _velocityX;
	std::vector<double> _velocityY;
	std::vector<double> _velocityZ;
	std::vector<double> _jacobian;
	std::vector<double> _pressure;
	double _time;
	LBField* _lbField;
	int _iter;
	std::ofstream _nsprofiles;
	std::ofstream _nspressure;
public:
          NSImplementation();
          ~NSImplementation();
          void setup(const std::string inputScenario);
          void solveOneTimestepPhaseOne();
          void solveOneTimestepPhaseTwo();
          void setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);
          void retrieveTimestep(double& timestep);
          void plot();
          void iterate();
          void iterateBoundary();
          void iterateInner();
          void retrieveVelocitiesSize(int& memory);
          void retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);
          void retrieveJacobianCopy(double* jacobian, const int jacobian_len);
          void retrievePressureCopy(double* pressure, const int pressure_len);
          void printNSPressure();
          void printNSProfiles();
          void closeNSProfiles();
          void solve();
};     


#endif
