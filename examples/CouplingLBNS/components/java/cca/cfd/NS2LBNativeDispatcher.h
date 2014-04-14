#ifndef CCA_CFD_NS2LBNATIVEDISPATCHER_H_
#define CCA_CFD_NS2LBNATIVEDISPATCHER_H_ 

#include "cca/cfd/NS2LB.h"
#include <iostream>
#include <vector>

namespace cca { 
namespace cfd { 
  
     class NS2LBNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class cca::cfd::NS2LBNativeDispatcher: public cca::cfd::NS2LB{
  protected:
    std::vector<cca::cfd::NS2LB*> _destinations;
  public:
    NS2LBNativeDispatcher();
    virtual ~NS2LBNativeDispatcher();
    
    void connect(cca::cfd::NS2LB* ref);
    void disconnect(cca::cfd::NS2LB* ref);
    bool isConnected() const;
    void iterate();
	void iterateParallel();
    void retrieveTimestep(double& timestep);
	void retrieveTimestepParallel(double& timestep);
    void retrieveVelocitiesSize(int& memory);
	void retrieveVelocitiesSizeParallel(int& memory);
    void retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);
	void retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);
    void retrieveJacobianCopy(double* jacobian, const int jacobian_len);
	void retrieveJacobianCopyParallel(double* jacobian, const int jacobian_len);
    void retrievePressureCopy(double* pressure, const int pressure_len);
	void retrievePressureCopyParallel(double* pressure, const int pressure_len);
};

#endif
