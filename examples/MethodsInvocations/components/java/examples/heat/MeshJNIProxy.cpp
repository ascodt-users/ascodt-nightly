#include "examples/heat/MeshJNIProxy.h"
#include "examples/heat/MeshImplementation.h"

#include <fstream>  

JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj){
  examples::heat::MeshImplementation *ref=new examples::heat::MeshImplementation();
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::MeshImplementation*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_getData(JNIEnv *env, jobject obj,jlong ref,jlongArray handle){
  jlong* handle_jni = env->GetLongArrayElements(handle,0);

  ((examples::heat::MeshImplementation*)ref)->getData((void*&)handle_jni[0]);
  env->ReleaseLongArrayElements(handle,handle_jni,JNI_COMMIT);

}

JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_copyData(JNIEnv *env, jobject obj,jlong ref,jdoubleArray data){
  jdouble* data_jni = env->GetDoubleArrayElements(data,0);
int data_jni_len = env->GetArrayLength(data);

  ((examples::heat::MeshImplementation*)ref)->copyData(data_jni,data_jni_len);
  env->ReleaseDoubleArrayElements(data,data_jni,JNI_COMMIT);

}

JNIEXPORT void JNICALL Java_examples_heat_MeshAbstractJavaNativeImplementation_allocate(JNIEnv *env, jobject obj,jlong ref,jintArray dim){
  jint* dim_jni = env->GetIntArrayElements(dim,0);
int dim_jni_len = env->GetArrayLength(dim);

  ((examples::heat::MeshImplementation*)ref)->allocate(dim_jni,dim_jni_len);
  env->ReleaseIntArrayElements(dim,dim_jni,JNI_ABORT);

}
