#include "cca/cfd/DriverNative2JavaPlainPort.h"

#ifdef JAVA

JNIEXPORT void JNICALL Java_cca_cfd_DriverNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  cca::cfd::DriverNative2JavaPlainPort *ref=new cca::cfd::DriverNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_cca_cfd_DriverNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::DriverNative2JavaPlainPort*)ref);
  
}



cca::cfd::DriverNative2JavaPlainPort::DriverNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

cca::cfd::DriverNative2JavaPlainPort::~DriverNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void cca::cfd::DriverNative2JavaPlainPort::go(const std::string configFile){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"go","(Ljava/lang/String;)V");
  
  if(mid){
     jobject configFile_jni=env->NewStringUTF(configFile.c_str());

     env->CallVoidMethod(_obj,mid,configFile_jni);
     
  }
}
void cca::cfd::DriverNative2JavaPlainPort::goParallel(const std::string configFile){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"goParallel","(Ljava/lang/String;)V");
  
  if(mid){
     jobject configFile_jni=env->NewStringUTF(configFile.c_str());

     env->CallVoidMethod(_obj,mid,configFile_jni);
     
  }
}
#endif
