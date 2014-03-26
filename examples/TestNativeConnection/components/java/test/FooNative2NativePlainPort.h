#ifndef TEST_FOONATIVE2NATIVEPLAINPORT_H_
#define TEST_FOONATIVE2NATIVEPLAINPORT_H_ 

#include "test/Foo.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_test_FooNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_test_FooNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_test_FooNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace test { 

     class FooNative2NativePlainPort;
}

class test::FooNative2NativePlainPort: public test::Foo{
  private:
    test::Foo* _destination;
  public:
    FooNative2NativePlainPort();
    ~FooNative2NativePlainPort();
    
    void connect(test::Foo*);
    void bar();
};

#endif
