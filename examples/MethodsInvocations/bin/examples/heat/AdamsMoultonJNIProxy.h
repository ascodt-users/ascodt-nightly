#ifndef EXAMPLES_HEAT_ADAMSMOULTONJNIPROXY_H_ 
#define EXAMPLES_HEAT_ADAMSMOULTONJNIPROXY_H_ 
#include <map>
#include <string>
#ifdef __cplusplus
  extern "C" {
#endif

#include "jni.h"
          
JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_step(JNIEnv *env, jobject obj,jlong ref,jintArray dims,jdouble dt,jdoubleArray rhs,jdoubleArray stencil,jlong dof);
JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_connectsolver(JNIEnv *env, jobject obj,jlong ref,jlong portRef);
JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_disconnectsolver(JNIEnv *env, jobject obj,jlong ref);

#ifdef __cplusplus
  }
#endif

#endif
