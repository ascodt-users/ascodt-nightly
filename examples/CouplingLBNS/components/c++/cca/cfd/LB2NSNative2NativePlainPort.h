#ifndef CCA_CFD_LB2NSNATIVE2NATIVEPLAINPORT_H_
#define CCA_CFD_LB2NSNATIVE2NATIVEPLAINPORT_H_ 

#include "cca/cfd/LB2NS.h"
#include <iostream>

#ifdef JAVA
#include <jni.h> 
#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif
#endif

namespace cca { 
namespace cfd { 
  
     class LB2NSNative2NativePlainPort;
} 
}

class cca::cfd::LB2NSNative2NativePlainPort: public cca::cfd::LB2NS{
  private:
    cca::cfd::LB2NS* _destination;
  public:
    LB2NSNative2NativePlainPort();
    ~LB2NSNative2NativePlainPort();
    
    void connect(cca::cfd::LB2NS*);
    void iterateBoundary();  
    void iterateBoundaryParallel();
   
    void iterateInner();  
    void iterateInnerParallel();
   
    void retrieveTimestep(double& dt);  
    void retrieveTimestepParallel(double& dt);
   
    void retrieveVelocitiesSize(int& memoryX,int& memoryY,int& memoryZ);  
    void retrieveVelocitiesSizeParallel(int& memoryX,int& memoryY,int& memoryZ);
   
    void retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);  
    void retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);
   
};

#endif
