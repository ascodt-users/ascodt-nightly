#ifndef TEST_MYCOMPONENTJNIPROXY_H_ 
#define TEST_MYCOMPONENTJNIPROXY_H_ 
#include <map>
#include <string>
#ifdef __cplusplus
  extern "C" {
#endif

#include "jni.h"
          
JNIEXPORT void JNICALL Java_test_MyComponentAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_test_MyComponentAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref);

#ifdef __cplusplus
  }
#endif

#endif
