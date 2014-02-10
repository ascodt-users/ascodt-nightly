#include "examples/heat/SORJNIProxy.h"
#include "examples/heat/SORImplementation.h"

#include <fstream>  

JNIEXPORT void JNICALL Java_examples_heat_SORAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj){
  examples::heat::SORImplementation *ref=new examples::heat::SORImplementation();
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_SORAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::SORImplementation*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_SORAbstractJavaNativeImplementation_solve(JNIEnv *env, jobject obj,jlong ref,jintArray dims,jdoubleArray stencil,jdoubleArray rhs,jlong dof_handle){
  jint* dims_jni = env->GetIntArrayElements(dims,0);
int dims_jni_len = env->GetArrayLength(dims);
jdouble* stencil_jni = env->GetDoubleArrayElements(stencil,0);
int stencil_jni_len = env->GetArrayLength(stencil);
jdouble* rhs_jni = env->GetDoubleArrayElements(rhs,0);
int rhs_jni_len = env->GetArrayLength(rhs);

  ((examples::heat::SORImplementation*)ref)->solve(dims_jni,dims_jni_len,stencil_jni,stencil_jni_len,rhs_jni,rhs_jni_len,(void*&)dof_handle);
  env->ReleaseIntArrayElements(dims,dims_jni,JNI_ABORT);
env->ReleaseDoubleArrayElements(stencil,stencil_jni,JNI_ABORT);
env->ReleaseDoubleArrayElements(rhs,rhs_jni,JNI_ABORT);

}

JNIEXPORT void JNICALL Java_examples_heat_SORAbstractJavaNativeImplementation_setup(JNIEnv *env, jobject obj,jlong ref,jdouble precision,jint iterations){
  
  ((examples::heat::SORImplementation*)ref)->setup(precision,iterations);
  
}
