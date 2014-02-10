#include "de/tum/FooBarNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_de_tum_FooBarNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::FooBarNativeDispatcher *ref=new de::tum::FooBarNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_FooBarNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::FooBarNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_FooBarNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::FooBarNativeDispatcher*)ref)->connect((de::tum::FooBar*)destination);
}

JNIEXPORT void JNICALL Java_de_tum_FooBarNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::FooBarNativeDispatcher*)ref)->disconnect((de::tum::FooBar*)destination);
}


de::tum::FooBarNativeDispatcher::FooBarNativeDispatcher(){

}

de::tum::FooBarNativeDispatcher::~FooBarNativeDispatcher(){

}

void de::tum::FooBarNativeDispatcher::connect(de::tum::FooBar* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void de::tum::FooBarNativeDispatcher::disconnect(de::tum::FooBar* destination){
  std::vector<de::tum::FooBar*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool de::tum::FooBarNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void de::tum::FooBarNativeDispatcher::foo(const double* data, const int data_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->foo(data,data_len);
}
void de::tum::FooBarNativeDispatcher::bar(double* data, const int data_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->bar(data,data_len);
}
void de::tum::FooBarNativeDispatcher::reset(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->reset();
}

