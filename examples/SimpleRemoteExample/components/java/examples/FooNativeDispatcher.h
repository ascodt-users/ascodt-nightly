#ifndef EXAMPLES_FOONATIVEDISPATCHER_H_
#define EXAMPLES_FOONATIVEDISPATCHER_H_ 

#include "examples/Foo.h"
#include <iostream>
#include <vector>

namespace examples { 

     class FooNativeDispatcher;
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_FooNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_FooNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_FooNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_FooNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::FooNativeDispatcher: public examples::Foo{
  protected:
    std::vector<examples::Foo*> _destinations;
  public:
    FooNativeDispatcher();
    virtual ~FooNativeDispatcher();
    
    void connect(examples::Foo* ref);
    void disconnect(examples::Foo* ref);
    bool isConnected() const;
    void bar(const int a,const int b);  
    void barParallel(const int a,const int b);
   
};

#endif
