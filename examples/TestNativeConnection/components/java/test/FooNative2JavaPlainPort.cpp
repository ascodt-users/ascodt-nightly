#include "test/FooNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_test_FooNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  test::FooNative2JavaPlainPort *ref=new test::FooNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_test_FooNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((test::FooNative2JavaPlainPort*)ref);
  
}

test::FooNative2JavaPlainPort::FooNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

test::FooNative2JavaPlainPort::~FooNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void test::FooNative2JavaPlainPort::bar(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Ltest/FooDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Ltest/FooDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"bar","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
