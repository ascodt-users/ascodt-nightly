#ifndef EXAMPLES_HEAT_MESHJNIPROXY_H_ 
#define EXAMPLES_HEAT_MESHJNIPROXY_H_ 
#include <map>
#include <string>
#ifdef __cplusplus
  extern "C" {
#endif

#include "jni.h"
          
JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_allocate(JNIEnv *env, jobject obj,jlong ref,jintArray dim);
JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_copyData(JNIEnv *env, jobject obj,jlong ref,jdoubleArray data);
JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_getData(JNIEnv *env, jobject obj,jlong ref,jlongArray handle);

#ifdef __cplusplus
  }
#endif

#endif
