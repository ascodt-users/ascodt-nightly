#include "test/FooNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_test_FooNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  test::FooNativeDispatcher *ref=new test::FooNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_test_FooNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((test::FooNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_test_FooNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((test::FooNativeDispatcher*)ref)->connect((test::Foo*)destination);
}

JNIEXPORT void JNICALL Java_test_FooNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((test::FooNativeDispatcher*)ref)->disconnect((test::Foo*)destination);
}


test::FooNativeDispatcher::FooNativeDispatcher(){

}

test::FooNativeDispatcher::~FooNativeDispatcher(){

}

void test::FooNativeDispatcher::connect(test::Foo* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void test::FooNativeDispatcher::disconnect(test::Foo* destination){
  std::vector<test::Foo*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool test::FooNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void test::FooNativeDispatcher::bar(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->bar();
}

