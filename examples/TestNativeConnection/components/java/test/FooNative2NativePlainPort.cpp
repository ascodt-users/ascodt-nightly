#include "test/FooNative2NativePlainPort.h"
#include <assert.h>
#include "Component.h"

JNIEXPORT void JNICALL Java_test_FooNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  test::FooNative2NativePlainPort *ref=new test::FooNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_test_FooNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((test::FooNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_test_FooNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  
  ((test::FooNative2NativePlainPort*)ref)->connect(dynamic_cast<test::Foo*>((Component*)destination));
}


test::FooNative2NativePlainPort::FooNative2NativePlainPort():
     _destination(0){

}

test::FooNative2NativePlainPort::~FooNative2NativePlainPort(){

}

void test::FooNative2NativePlainPort::connect(test::Foo* destination){
  _destination=destination;
}
void test::FooNative2NativePlainPort::bar(){
     assert(_destination!=NULL);
     _destination->bar();
}

