#ifndef EXAMPLES_HEAT_DRIVERNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_HEAT_DRIVERNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/heat/Driver.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_DriverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_DriverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_DriverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 
namespace heat { 
  
     class DriverNative2NativePlainPort;
} 
}

class examples::heat::DriverNative2NativePlainPort: public examples::heat::Driver{
  private:
    examples::heat::Driver* _destination;
  public:
    DriverNative2NativePlainPort();
    ~DriverNative2NativePlainPort();
    
    void connect(examples::heat::Driver*);
    void go();
};

#endif
