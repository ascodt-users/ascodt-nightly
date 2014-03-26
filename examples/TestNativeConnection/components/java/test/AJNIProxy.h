#ifndef TEST_AJNIPROXY_H_ 
#define TEST_AJNIPROXY_H_ 
#include <map>
#include <string>
#ifdef __cplusplus
  extern "C" {
#endif

#include "jni.h"
          
JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_bar(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_connectfoo(JNIEnv *env, jobject obj,jlong ref,jlong portRef);
JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_disconnectfoo(JNIEnv *env, jobject obj,jlong ref);

#ifdef __cplusplus
  }
#endif

#endif
