#include "examples/FooNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_FooNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::FooNativeDispatcher *ref=new examples::FooNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_FooNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::FooNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_FooNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::FooNativeDispatcher*)ref)->connect((examples::Foo*)destination);
}

JNIEXPORT void JNICALL Java_examples_FooNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::FooNativeDispatcher*)ref)->disconnect((examples::Foo*)destination);
}


examples::FooNativeDispatcher::FooNativeDispatcher(){

}

examples::FooNativeDispatcher::~FooNativeDispatcher(){

}

void examples::FooNativeDispatcher::connect(examples::Foo* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::FooNativeDispatcher::disconnect(examples::Foo* destination){
  std::vector<examples::Foo*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::FooNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::FooNativeDispatcher::bar(const int a,const int b){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->bar(a,b);
}

void examples::FooNativeDispatcher::barParallel(const int a,const int b){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->barParallel(a,b);
}

