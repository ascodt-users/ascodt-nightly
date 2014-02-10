#include "de/tum/FooBarNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_de_tum_FooBarNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::FooBarNative2NativePlainPort *ref=new de::tum::FooBarNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_FooBarNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::FooBarNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_FooBarNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::FooBarNative2NativePlainPort*)ref)->connect((de::tum::FooBar*)destination);
}


de::tum::FooBarNative2NativePlainPort::FooBarNative2NativePlainPort():
     _destination(0){

}

de::tum::FooBarNative2NativePlainPort::~FooBarNative2NativePlainPort(){

}

void de::tum::FooBarNative2NativePlainPort::connect(de::tum::FooBar* destination){
  _destination=destination;
}
void de::tum::FooBarNative2NativePlainPort::foo(const double* data, const int data_len){
     assert(_destination!=NULL);
     _destination->foo(data,data_len);
}
void de::tum::FooBarNative2NativePlainPort::bar(double* data, const int data_len){
     assert(_destination!=NULL);
     _destination->bar(data,data_len);
}
void de::tum::FooBarNative2NativePlainPort::reset(){
     assert(_destination!=NULL);
     _destination->reset();
}

