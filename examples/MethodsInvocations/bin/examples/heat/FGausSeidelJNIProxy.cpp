#include "examples/heat/FGausSeidelJNIProxy.h"

extern "C" {

     
     void fgausseidel_fproxy_createinstance_(void* &self);
     void fgausseidel_fproxy_destroyinstance_(void* &self);
     
} 

JNIEXPORT void JNICALL Java_examples_heat_FGausSeidelAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj){
  void* ref=NULL;
  fgausseidel_fproxy_createinstance_(ref);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_FGausSeidelAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  void* cref = (void*) ref;
  fgausseidel_fproxy_destroyinstance_(cref);
}


extern "C" {
     void fgausseidel_fproxy_solve_(void*& ref,const int* dims, const int& dims_len,const double* stencil, const int& stencil_len,const double* rhs, const int& rhs_len,void*& dof_handle);
}

JNIEXPORT void JNICALL Java_examples_heat_FGausSeidelAbstractJavaNativeImplementation_solve(JNIEnv *env, jobject obj,jlong ref,jintArray dims,jdoubleArray stencil,jdoubleArray rhs,jlong dof_handle){
  jint* dims_jni = env->GetIntArrayElements(dims,0);
int dims_jni_len = env->GetArrayLength(dims);
jdouble* stencil_jni = env->GetDoubleArrayElements(stencil,0);
int stencil_jni_len = env->GetArrayLength(stencil);
jdouble* rhs_jni = env->GetDoubleArrayElements(rhs,0);
int rhs_jni_len = env->GetArrayLength(rhs);
void* dof_handle_c2f = (void*)dof_handle;

  void* cref = (void*) ref;
  fgausseidel_fproxy_solve_(cref,dims_jni,dims_jni_len,stencil_jni,stencil_jni_len,rhs_jni,rhs_jni_len,(void*&)dof_handle_c2f);
  env->ReleaseIntArrayElements(dims,dims_jni,JNI_ABORT);
env->ReleaseDoubleArrayElements(stencil,stencil_jni,JNI_ABORT);
env->ReleaseDoubleArrayElements(rhs,rhs_jni,JNI_ABORT);

}

extern "C" {
     void fgausseidel_fproxy_setup_(void*& ref,const double& precision,const int& iterations);
}

JNIEXPORT void JNICALL Java_examples_heat_FGausSeidelAbstractJavaNativeImplementation_setup(JNIEnv *env, jobject obj,jlong ref,jdouble precision,jint iterations){
  
  void* cref = (void*) ref;
  fgausseidel_fproxy_setup_(cref,precision,iterations);
  
}
