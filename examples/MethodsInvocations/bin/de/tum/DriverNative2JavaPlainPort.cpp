#include "de/tum/DriverNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_de_tum_DriverNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  de::tum::DriverNative2JavaPlainPort *ref=new de::tum::DriverNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_de_tum_DriverNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::DriverNative2JavaPlainPort*)ref);
  
}

de::tum::DriverNative2JavaPlainPort::DriverNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

de::tum::DriverNative2JavaPlainPort::~DriverNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void de::tum::DriverNative2JavaPlainPort::go(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lde/tum/DriverDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lde/tum/DriverDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"go","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
