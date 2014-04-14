#ifndef EXAMPLES_FOO2NATIVE2JAVAPLAINPORT_H_
#define EXAMPLES_FOO2NATIVE2JAVAPLAINPORT_H_ 

#include "examples/Foo.h"
#include <jni.h> 
#include <iostream>
//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_FooNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_FooNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);

#ifdef __cplusplus
  }
#endif




namespace examples { 

     class FooNative2JavaPlainPort;
}

class examples::FooNative2JavaPlainPort: public examples::Foo{
  private:
    JavaVM* _jvm;
    jobject _obj;
  public:
    FooNative2JavaPlainPort(JavaVM* jvm,jobject obj);
    ~FooNative2JavaPlainPort();
    void bar(const int a,const int b);  
    void barParallel(const int a,const int b);
   
};
#endif
