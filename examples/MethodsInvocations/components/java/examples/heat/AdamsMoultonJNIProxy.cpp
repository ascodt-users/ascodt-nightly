#include "examples/heat/AdamsMoultonJNIProxy.h"
#include "examples/heat/AdamsMoultonImplementation.h"
#include "examples/heat/Solver.h"

#include <fstream>  

JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj){
  examples::heat::AdamsMoultonImplementation *ref=new examples::heat::AdamsMoultonImplementation();
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::AdamsMoultonImplementation*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_connectsolver(JNIEnv *env, jobject obj,jlong ref,jlong portRef){
  ((examples::heat::AdamsMoultonImplementation*)ref)->connectsolver(
     ((examples::heat::SolverNativeDispatcher*) portRef)
  );    
}

JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_disconnectsolver(JNIEnv *env, jobject obj,jlong ref){
   ((examples::heat::AdamsMoultonImplementation*)ref)->disconnectsolver();   
}

JNIEXPORT void JNICALL Java_examples_heat_AdamsMoultonAbstractJavaNativeImplementation_step(JNIEnv *env, jobject obj,jlong ref,jintArray dims,jdouble dt,jdoubleArray rhs,jdoubleArray stencil,jlong dof){
  jint* dims_jni = env->GetIntArrayElements(dims,0);
int dims_jni_len = env->GetArrayLength(dims);
jdouble* rhs_jni = env->GetDoubleArrayElements(rhs,0);
int rhs_jni_len = env->GetArrayLength(rhs);
jdouble* stencil_jni = env->GetDoubleArrayElements(stencil,0);
int stencil_jni_len = env->GetArrayLength(stencil);

  ((examples::heat::AdamsMoultonImplementation*)ref)->step(dims_jni,dims_jni_len,dt,rhs_jni,rhs_jni_len,stencil_jni,stencil_jni_len,(void*&)dof);
  env->ReleaseIntArrayElements(dims,dims_jni,JNI_ABORT);
env->ReleaseDoubleArrayElements(rhs,rhs_jni,JNI_ABORT);
env->ReleaseDoubleArrayElements(stencil,stencil_jni,JNI_ABORT);

}
