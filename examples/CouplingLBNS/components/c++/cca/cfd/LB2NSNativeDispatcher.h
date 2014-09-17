#ifndef CCA_CFD_LB2NSNATIVEDISPATCHER_H_
#define CCA_CFD_LB2NSNATIVEDISPATCHER_H_ 

#include "cca/cfd/LB2NS.h"
#include <iostream>
#include <vector>

namespace cca { 
namespace cfd { 
  
     class LB2NSNativeDispatcher;
} 
}

#ifdef JAVA
#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

#endif

class cca::cfd::LB2NSNativeDispatcher: public cca::cfd::LB2NS{
  protected:
    std::vector<cca::cfd::LB2NS*> _destinations;
  public:
    LB2NSNativeDispatcher();
    virtual ~LB2NSNativeDispatcher();
    
    void connect(cca::cfd::LB2NS* ref);
    void disconnect(cca::cfd::LB2NS* ref);
    bool isConnected() const;
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
