#ifndef DE_TUM_FOOBARNATIVE2NATIVEPLAINPORT_H_
#define DE_TUM_FOOBARNATIVE2NATIVEPLAINPORT_H_ 

#include "de/tum/FooBar.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_de_tum_FooBarNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_de_tum_FooBarNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_de_tum_FooBarNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace de { 
namespace tum { 
  
     class FooBarNative2NativePlainPort;
} 
}

class de::tum::FooBarNative2NativePlainPort: public de::tum::FooBar{
  private:
    de::tum::FooBar* _destination;
  public:
    FooBarNative2NativePlainPort();
    ~FooBarNative2NativePlainPort();
    
    void connect(de::tum::FooBar*);
    void foo(const double* data, const int data_len);
    void bar(double* data, const int data_len);
    void reset();
};

#endif
