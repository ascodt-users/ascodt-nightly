#ifndef CCA_CFD_DRIVERNATIVE2NATIVEPLAINPORT_H_
#define CCA_CFD_DRIVERNATIVE2NATIVEPLAINPORT_H_ 

#include "cca/cfd/Driver.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_DriverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_DriverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_DriverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace cca { 
namespace cfd { 
  
     class DriverNative2NativePlainPort;
} 
}

class cca::cfd::DriverNative2NativePlainPort: public cca::cfd::Driver{
  private:
    cca::cfd::Driver* _destination;
  public:
    DriverNative2NativePlainPort();
    ~DriverNative2NativePlainPort();
    
    void connect(cca::cfd::Driver*);
    void go(const std::string configFile);  
    void goParallel(const std::string configFile);
   
};

#endif
