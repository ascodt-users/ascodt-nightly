#ifndef EXAMPLES_DRIVERNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_DRIVERNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/Driver.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_DriverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_DriverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_DriverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 

     class DriverNative2NativePlainPort;
}

class examples::DriverNative2NativePlainPort: public examples::Driver{
  private:
    examples::Driver* _destination;
  public:
    DriverNative2NativePlainPort();
    ~DriverNative2NativePlainPort();
    
    void connect(examples::Driver*);
    void go();  
    void goParallel();
   
};

#endif
