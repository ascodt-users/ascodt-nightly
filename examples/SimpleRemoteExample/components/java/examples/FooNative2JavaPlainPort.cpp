#include "examples/FooNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_examples_FooNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  examples::FooNative2JavaPlainPort *ref=new examples::FooNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_examples_FooNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::FooNative2JavaPlainPort*)ref);
  
}

examples::FooNative2JavaPlainPort::FooNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

examples::FooNative2JavaPlainPort::~FooNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void examples::FooNative2JavaPlainPort::bar(const int a,const int b){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"bar","(II)V");
  
  if(mid){
     jint a_jni=a;
jint b_jni=b;

     env->CallVoidMethod(_obj,mid,a_jni,b_jni);
     
  }
}
void examples::FooNative2JavaPlainPort::barParallel(const int a,const int b){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"barParallel","(II)V");
  
  if(mid){
     jint a_jni=a;
jint b_jni=b;

     env->CallVoidMethod(_obj,mid,a_jni,b_jni);
     
  }
}
