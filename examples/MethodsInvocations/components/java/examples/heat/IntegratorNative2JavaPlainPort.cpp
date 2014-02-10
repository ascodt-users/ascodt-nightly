#include "examples/heat/IntegratorNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  examples::heat::IntegratorNative2JavaPlainPort *ref=new examples::heat::IntegratorNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::IntegratorNative2JavaPlainPort*)ref);
  
}

examples::heat::IntegratorNative2JavaPlainPort::IntegratorNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

examples::heat::IntegratorNative2JavaPlainPort::~IntegratorNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void examples::heat::IntegratorNative2JavaPlainPort::step(const int* dims, const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,const void* dof){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/IntegratorDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/IntegratorDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"step","([ID[D[DJ)V");
  
  if(mid){
     jintArray dims_jni=env->NewIntArray(dims_len);
env->SetIntArrayRegion(dims_jni,0,dims_len,(jint*)dims);
jdouble dt_jni=dt;
jdoubleArray rhs_jni=env->NewDoubleArray(rhs_len);
env->SetDoubleArrayRegion(rhs_jni,0,rhs_len,(jdouble*)rhs);
jdoubleArray stencil_jni=env->NewDoubleArray(stencil_len);
env->SetDoubleArrayRegion(stencil_jni,0,stencil_len,(jdouble*)stencil);
jlong dof_jni=(long long)dof;

     env->CallVoidMethod(_obj,mid,dims_jni,dt_jni,rhs_jni,stencil_jni,dof_jni);
     
  }
}
