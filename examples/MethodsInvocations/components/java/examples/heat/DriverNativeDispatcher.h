#ifndef EXAMPLES_HEAT_DRIVERNATIVEDISPATCHER_H_
#define EXAMPLES_HEAT_DRIVERNATIVEDISPATCHER_H_ 

#include "examples/heat/Driver.h"
#include <iostream>
#include <vector>

namespace examples { 
namespace heat { 
  
     class DriverNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_DriverNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_DriverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_DriverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_heat_DriverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::heat::DriverNativeDispatcher: public examples::heat::Driver{
  protected:
    std::vector<examples::heat::Driver*> _destinations;
  public:
    DriverNativeDispatcher();
    virtual ~DriverNativeDispatcher();
    
    void connect(examples::heat::Driver* ref);
    void disconnect(examples::heat::Driver* ref);
    bool isConnected() const;
    void go();
};

#endif
