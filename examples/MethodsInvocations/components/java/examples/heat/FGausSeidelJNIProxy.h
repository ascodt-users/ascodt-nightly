#ifndef EXAMPLES_HEAT_FGAUSSEIDELJNIPROXY_H_ 
#define EXAMPLES_HEAT_FGAUSSEIDELJNIPROXY_H_ 
#include <map>
#include <string>
#ifdef __cplusplus
  extern "C" {
#endif

#include "jni.h"
          
JNIEXPORT void JNICALL Java_examples_heat_FGausSeidelAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_FGausSeidelAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_FGausSeidelAbstractJavaNativeImplementation_setup(JNIEnv *env, jobject obj,jlong ref,jdouble precision,jint iterations);
JNIEXPORT void JNICALL Java_examples_heat_FGausSeidelAbstractJavaNativeImplementation_solve(JNIEnv *env, jobject obj,jlong ref,jintArray dims,jdoubleArray stencil,jdoubleArray rhs,jlong dof_handle);

#ifdef __cplusplus
  }
#endif

#endif
