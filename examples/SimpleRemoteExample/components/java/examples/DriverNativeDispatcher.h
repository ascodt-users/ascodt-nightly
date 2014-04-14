#ifndef EXAMPLES_DRIVERNATIVEDISPATCHER_H_
#define EXAMPLES_DRIVERNATIVEDISPATCHER_H_ 

#include "examples/Driver.h"
#include <iostream>
#include <vector>

namespace examples { 

     class DriverNativeDispatcher;
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_DriverNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_DriverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_DriverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_DriverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::DriverNativeDispatcher: public examples::Driver{
  protected:
    std::vector<examples::Driver*> _destinations;
  public:
    DriverNativeDispatcher();
    virtual ~DriverNativeDispatcher();
    
    void connect(examples::Driver* ref);
    void disconnect(examples::Driver* ref);
    bool isConnected() const;
    void go();  
    void goParallel();
   
};

#endif
