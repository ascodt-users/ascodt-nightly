#ifndef CCA_CFD_NS2LBNATIVE2NATIVEPLAINPORT_H_
#define CCA_CFD_NS2LBNATIVE2NATIVEPLAINPORT_H_ 

#include "cca/cfd/NS2LB.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace cca { 
namespace cfd { 
  
     class NS2LBNative2NativePlainPort;
} 
}

class cca::cfd::NS2LBNative2NativePlainPort: public cca::cfd::NS2LB{
  private:
    cca::cfd::NS2LB* _destination;
  public:
    NS2LBNative2NativePlainPort();
    ~NS2LBNative2NativePlainPort();
    
    void connect(cca::cfd::NS2LB*);
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
