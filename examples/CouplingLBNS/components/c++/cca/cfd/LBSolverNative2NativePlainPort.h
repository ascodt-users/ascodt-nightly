#ifndef CCA_CFD_LBSOLVERNATIVE2NATIVEPLAINPORT_H_
#define CCA_CFD_LBSOLVERNATIVE2NATIVEPLAINPORT_H_ 

#include "cca/cfd/LBSolver.h"
#include <iostream>

#ifdef JAVA
#include <jni.h> 
#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif
#endif

namespace cca { 
namespace cfd { 
  
     class LBSolverNative2NativePlainPort;
} 
}

class cca::cfd::LBSolverNative2NativePlainPort: public cca::cfd::LBSolver{
  private:
    cca::cfd::LBSolver* _destination;
  public:
    LBSolverNative2NativePlainPort();
    ~LBSolverNative2NativePlainPort();
    
    void connect(cca::cfd::LBSolver*);
    void setup(const std::string inputScenario);  
    void setupParallel(const std::string inputScenario);
   
    void setupCommForNSRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len);  
    void setupCommForNSRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len);
   
    void solve();  
    void solveParallel();
   
    void solveOneTimestep();  
    void solveOneTimestepParallel();
   
    void setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);  
    void setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);
   
    void setPressure(const double* pressure, const int pressure_len);  
    void setPressureParallel(const double* pressure, const int pressure_len);
   
    void setGradients(const double* gradients, const int gradients_len);  
    void setGradientsParallel(const double* gradients, const int gradients_len);
   
    void closeLBProfiles();  
    void closeLBProfilesParallel();
   
    void printLBDensity();  
    void printLBDensityParallel();
   
    void printLBProfiles();  
    void printLBProfilesParallel();
   
    void forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);  
    void forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);
   
    void forwardPressure(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);  
    void forwardPressureParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);
   
    void syncr(int& value);  
    void syncrParallel(int& value);
   
    void plot();  
    void plotParallel();
   
};

#endif
