#ifndef CCA_CFD_NSSOLVERNATIVEDISPATCHER_H_
#define CCA_CFD_NSSOLVERNATIVEDISPATCHER_H_ 

#include "cca/cfd/NSSolver.h"
#include <iostream>
#include <vector>

namespace cca { 
namespace cfd { 
  
     class NSSolverNativeDispatcher;
} 
}

#ifdef JAVA
#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

#endif

class cca::cfd::NSSolverNativeDispatcher: public cca::cfd::NSSolver{
  protected:
    std::vector<cca::cfd::NSSolver*> _destinations;
  public:
    NSSolverNativeDispatcher();
    virtual ~NSSolverNativeDispatcher();
    
    void connect(cca::cfd::NSSolver* ref);
    void disconnect(cca::cfd::NSSolver* ref);
    bool isConnected() const;
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
   
    void forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);  
    void forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);
   
    void plot();  
    void plotParallel();
   
    void syncr(int& value);  
    void syncrParallel(int& value);
   
};

#endif
