#ifndef CCA_CFD_NSSOLVERNATIVE2NATIVEPLAINPORT_H_
#define CCA_CFD_NSSOLVERNATIVE2NATIVEPLAINPORT_H_ 

#include "cca/cfd/NSSolver.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace cca { 
namespace cfd { 
  
     class NSSolverNative2NativePlainPort;
} 
}

class cca::cfd::NSSolverNative2NativePlainPort: public cca::cfd::NSSolver{
  private:
    cca::cfd::NSSolver* _destination;
  public:
    NSSolverNative2NativePlainPort();
    ~NSSolverNative2NativePlainPort();
    
    void connect(cca::cfd::NSSolver*);
    void setup(const std::string inputScenario);  
    void setupParallel(const std::string inputScenario);
   
    void setupCommForLBRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len);  
    void setupCommForLBRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len);
   
    void solve();  
    void solveParallel();
   
    void solveOneTimestepPhaseOne();  
    void solveOneTimestepPhaseOneParallel();
   
    void solveOneTimestepPhaseTwo();  
    void solveOneTimestepPhaseTwoParallel();
   
    void setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);  
    void setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);
   
    void printNSPressure();  
    void printNSPressureParallel();
   
    void printNSProfiles();  
    void printNSProfilesParallel();
   
    void closeNSProfiles();  
    void closeNSProfilesParallel();
   
    void iterateBoundary();  
    void iterateBoundaryParallel();
   
    void iterateInner();  
    void iterateInnerParallel();
   
    void forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn);  
    void forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn);
   
    void plot();  
    void plotParallel();
   
    void syncr(int& value);  
    void syncrParallel(int& value);
   
};

#endif
