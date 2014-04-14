#ifndef CCA_CFD_LBSOLVER2NATIVE2JAVAPLAINPORT_H_
#define CCA_CFD_LBSOLVER2NATIVE2JAVAPLAINPORT_H_ 

#include "cca/cfd/LBSolver.h"
#include <jni.h> 
#include <iostream>
//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);

#ifdef __cplusplus
  }
#endif




namespace cca { 
namespace cfd { 
  
     class LBSolverNative2JavaPlainPort;
} 
}

class cca::cfd::LBSolverNative2JavaPlainPort: public cca::cfd::LBSolver{
  private:
    JavaVM* _jvm;
    jobject _obj;
  public:
    LBSolverNative2JavaPlainPort(JavaVM* jvm,jobject obj);
    ~LBSolverNative2JavaPlainPort();
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
    void forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn);
	void forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn);
    void forwardPressure(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);
	void forwardPressureParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);
    void syncr(int& value);
	void syncrParallel(int& value);
    void plot();
	void plotParallel();
};
#endif