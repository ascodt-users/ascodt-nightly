#include "examples/heat/StencilNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_examples_heat_StencilNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  examples::heat::StencilNative2JavaPlainPort *ref=new examples::heat::StencilNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_examples_heat_StencilNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::StencilNative2JavaPlainPort*)ref);
  
}

examples::heat::StencilNative2JavaPlainPort::StencilNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

examples::heat::StencilNative2JavaPlainPort::~StencilNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void examples::heat::StencilNative2JavaPlainPort::getStencil(double* stencil, const int stencil_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/StencilDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/StencilDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"getStencil","([D)V");
  
  if(mid){
     jdoubleArray stencil_jni=env->NewDoubleArray(stencil_len);
env->SetDoubleArrayRegion(stencil_jni,0,stencil_len,(jdouble*)stencil);

     env->CallVoidMethod(_obj,mid,stencil_jni);
     env->GetDoubleArrayRegion(stencil_jni,0,stencil_len,(jdouble*)stencil);

  }
}
