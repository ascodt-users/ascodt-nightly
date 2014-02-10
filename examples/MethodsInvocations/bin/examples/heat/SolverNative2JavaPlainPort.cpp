#include "examples/heat/SolverNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_examples_heat_SolverNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  examples::heat::SolverNative2JavaPlainPort *ref=new examples::heat::SolverNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_examples_heat_SolverNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::SolverNative2JavaPlainPort*)ref);
  
}

examples::heat::SolverNative2JavaPlainPort::SolverNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

examples::heat::SolverNative2JavaPlainPort::~SolverNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void examples::heat::SolverNative2JavaPlainPort::setup(const double precision,const int iterations){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/SolverDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/SolverDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setup","(DI)V");
  
  if(mid){
     jdouble precision_jni=precision;
jint iterations_jni=iterations;

     env->CallVoidMethod(_obj,mid,precision_jni,iterations_jni);
     
  }
}
void examples::heat::SolverNative2JavaPlainPort::solve(const int* dims, const int dims_len,const double* stencil, const int stencil_len,const double* rhs, const int rhs_len,const void* dof_handle){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/SolverDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/SolverDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solve","([I[D[DJ)V");
  
  if(mid){
     jintArray dims_jni=env->NewIntArray(dims_len);
env->SetIntArrayRegion(dims_jni,0,dims_len,(jint*)dims);
jdoubleArray stencil_jni=env->NewDoubleArray(stencil_len);
env->SetDoubleArrayRegion(stencil_jni,0,stencil_len,(jdouble*)stencil);
jdoubleArray rhs_jni=env->NewDoubleArray(rhs_len);
env->SetDoubleArrayRegion(rhs_jni,0,rhs_len,(jdouble*)rhs);
jlong dof_handle_jni=(long long)dof_handle;

     env->CallVoidMethod(_obj,mid,dims_jni,stencil_jni,rhs_jni,dof_handle_jni);
     
  }
}
