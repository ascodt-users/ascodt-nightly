#ifndef TEST_FOONATIVEDISPATCHER_H_
#define TEST_FOONATIVEDISPATCHER_H_ 

#include "test/Foo.h"
#include <iostream>
#include <vector>

namespace test { 

     class FooNativeDispatcher;
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_test_FooNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_test_FooNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_test_FooNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_test_FooNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class test::FooNativeDispatcher: public test::Foo{
  protected:
    std::vector<test::Foo*> _destinations;
  public:
    FooNativeDispatcher();
    virtual ~FooNativeDispatcher();
    
    void connect(test::Foo* ref);
    void disconnect(test::Foo* ref);
    bool isConnected() const;
    void bar();
};

#endif
