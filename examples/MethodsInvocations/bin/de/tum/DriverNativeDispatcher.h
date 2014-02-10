#ifndef DE_TUM_DRIVERNATIVEDISPATCHER_H_
#define DE_TUM_DRIVERNATIVEDISPATCHER_H_ 

#include "de/tum/Driver.h"
#include <iostream>
#include <vector>

namespace de { 
namespace tum { 
  
     class DriverNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_DriverNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_DriverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_DriverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_de_tum_DriverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class de::tum::DriverNativeDispatcher: public de::tum::Driver{
  protected:
    std::vector<de::tum::Driver*> _destinations;
  public:
    DriverNativeDispatcher();
    virtual ~DriverNativeDispatcher();
    
    void connect(de::tum::Driver* ref);
    void disconnect(de::tum::Driver* ref);
    bool isConnected() const;
    void go();
};

#endif
