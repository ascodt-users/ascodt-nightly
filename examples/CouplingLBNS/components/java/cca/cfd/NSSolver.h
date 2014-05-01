#ifndef CCA_CFD_NSSOLVER_H_
#define CCA_CFD_NSSOLVER_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include <iostream>
#include <string>



namespace cca { 
namespace cfd { 
  
     class NSSolver;
} 
}

class cca::cfd::NSSolver {
  public:
    virtual ~NSSolver(){}
     virtual void syncr(int& value)=0;
     virtual void syncrParallel(int& value)=0;
     virtual void plot()=0;
     virtual void plotParallel()=0;
     virtual void forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn)=0;
     virtual void forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn)=0;
     virtual void iterateInner()=0;
     virtual void iterateInnerParallel()=0;
     virtual void iterateBoundary()=0;
     virtual void iterateBoundaryParallel()=0;
     virtual void closeNSProfiles()=0;
     virtual void closeNSProfilesParallel()=0;
     virtual void printNSProfiles()=0;
     virtual void printNSProfilesParallel()=0;
     virtual void printNSPressure()=0;
     virtual void printNSPressureParallel()=0;
     virtual void setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len)=0;
     virtual void setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len)=0;
     virtual void solveOneTimestepPhaseTwo()=0;
     virtual void solveOneTimestepPhaseTwoParallel()=0;
     virtual void solveOneTimestepPhaseOne()=0;
     virtual void solveOneTimestepPhaseOneParallel()=0;
     virtual void solve()=0;
     virtual void solveParallel()=0;
     virtual void setupCommForLBRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len)=0;
     virtual void setupCommForLBRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len)=0;
     virtual void setup(const std::string inputScenario)=0;
     virtual void setupParallel(const std::string inputScenario)=0;


};

#endif
