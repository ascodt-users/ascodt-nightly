#ifndef CCA_CFD_LBSOLVERNATIVEDISPATCHER_H_
#define CCA_CFD_LBSOLVERNATIVEDISPATCHER_H_ 

#include "cca/cfd/LBSolver.h"
#include <iostream>
#include <vector>

namespace cca { 
namespace cfd { 
  
     class LBSolverNativeDispatcher;
} 
}

#ifdef JAVA
#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

#endif

class cca::cfd::LBSolverNativeDispatcher: public cca::cfd::LBSolver{
  protected:
    std::vector<cca::cfd::LBSolver*> _destinations;
  public:
    LBSolverNativeDispatcher();
    virtual ~LBSolverNativeDispatcher();
    
    void connect(cca::cfd::LBSolver* ref);
    void disconnect(cca::cfd::LBSolver* ref);
    bool isConnected() const;
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
