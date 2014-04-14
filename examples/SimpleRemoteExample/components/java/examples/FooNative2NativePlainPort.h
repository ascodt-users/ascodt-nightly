#ifndef EXAMPLES_FOONATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_FOONATIVE2NATIVEPLAINPORT_H_ 

#include "examples/Foo.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_FooNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_FooNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_FooNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 

     class FooNative2NativePlainPort;
}

class examples::FooNative2NativePlainPort: public examples::Foo{
  private:
    examples::Foo* _destination;
  public:
    FooNative2NativePlainPort();
    ~FooNative2NativePlainPort();
    
    void connect(examples::Foo*);
    void bar(const int a,const int b);  
    void barParallel(const int a,const int b);
   
};

#endif
