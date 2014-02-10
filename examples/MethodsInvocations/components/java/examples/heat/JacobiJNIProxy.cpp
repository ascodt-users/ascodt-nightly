#include "examples/heat/JacobiJNIProxy.h"
#include "examples/heat/JacobiImplementation.h"

#include <fstream>  

JNIEXPORT void JNICALL Java_examples_heat_JacobiAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj){
  examples::heat::JacobiImplementation *ref=new examples::heat::JacobiImplementation();
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_JacobiAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::JacobiImplementation*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_JacobiAbstractJavaNativeImplementation_solve(JNIEnv *env, jobject obj,jlong ref,jintArray dims,jdoubleArray stencil,jdoubleArray rhs,jlong dof_handle){
  jint* dims_jni = env->GetIntArrayElements(dims,0);
int dims_jni_len = env->GetArrayLength(dims);
jdouble* stencil_jni = env->GetDoubleArrayElements(stencil,0);
int stencil_jni_len = env->GetArrayLength(stencil);
jdouble* rhs_jni = env->GetDoubleArrayElements(rhs,0);
int rhs_jni_len = env->GetArrayLength(rhs);

  ((examples::heat::JacobiImplementation*)ref)->solve(dims_jni,dims_jni_len,stencil_jni,stencil_jni_len,rhs_jni,rhs_jni_len,(void*&)dof_handle);
  env->ReleaseIntArrayElements(dims,dims_jni,JNI_ABORT);
env->ReleaseDoubleArrayElements(stencil,stencil_jni,JNI_ABORT);
env->ReleaseDoubleArrayElements(rhs,rhs_jni,JNI_ABORT);

}

JNIEXPORT void JNICALL Java_examples_heat_JacobiAbstractJavaNativeImplementation_setup(JNIEnv *env, jobject obj,jlong ref,jdouble precision,jint iterations){
  
  ((examples::heat::JacobiImplementation*)ref)->setup(precision,iterations);
  
}
