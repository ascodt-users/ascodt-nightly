#ifndef DE_TUM_FOOBARNATIVEDISPATCHER_H_
#define DE_TUM_FOOBARNATIVEDISPATCHER_H_ 

#include "de/tum/FooBar.h"
#include <iostream>
#include <vector>

namespace de { 
namespace tum { 
  
     class FooBarNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_FooBarNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_FooBarNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_FooBarNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_de_tum_FooBarNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class de::tum::FooBarNativeDispatcher: public de::tum::FooBar{
  protected:
    std::vector<de::tum::FooBar*> _destinations;
  public:
    FooBarNativeDispatcher();
    virtual ~FooBarNativeDispatcher();
    
    void connect(de::tum::FooBar* ref);
    void disconnect(de::tum::FooBar* ref);
    bool isConnected() const;
    void foo(const double* data, const int data_len);
    void bar(double* data, const int data_len);
    void reset();
};

#endif
