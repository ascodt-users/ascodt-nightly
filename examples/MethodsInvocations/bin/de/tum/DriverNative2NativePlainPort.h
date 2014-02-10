#ifndef DE_TUM_DRIVERNATIVE2NATIVEPLAINPORT_H_
#define DE_TUM_DRIVERNATIVE2NATIVEPLAINPORT_H_ 

#include "de/tum/Driver.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_DriverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_DriverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_DriverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace de { 
namespace tum { 
  
     class DriverNative2NativePlainPort;
} 
}

class de::tum::DriverNative2NativePlainPort: public de::tum::Driver{
  private:
    de::tum::Driver* _destination;
  public:
    DriverNative2NativePlainPort();
    ~DriverNative2NativePlainPort();
    
    void connect(de::tum::Driver*);
    void go();
};

#endif
