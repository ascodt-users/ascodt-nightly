#ifndef TEST_BJNIPROXY_H_ 
#define TEST_BJNIPROXY_H_ 
#include <map>
#include <string>
#ifdef __cplusplus
  extern "C" {
#endif

#include "jni.h"
          
JNIEXPORT void JNICALL Java_test_BAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_test_BAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_test_BAbstractJavaNativeImplementation_bar(JNIEnv *env, jobject obj,jlong ref);

#ifdef __cplusplus
  }
#endif

#endif
