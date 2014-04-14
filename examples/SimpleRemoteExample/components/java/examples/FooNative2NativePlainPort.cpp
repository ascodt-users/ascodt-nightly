#include "examples/FooNative2NativePlainPort.h"
#include <assert.h>
#include "Component.h"

JNIEXPORT void JNICALL Java_examples_FooNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::FooNative2NativePlainPort *ref=new examples::FooNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_FooNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::FooNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_FooNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  
  ((examples::FooNative2NativePlainPort*)ref)->connect(dynamic_cast<examples::Foo*>((Component*)destination));
}


examples::FooNative2NativePlainPort::FooNative2NativePlainPort():
     _destination(0){

}

examples::FooNative2NativePlainPort::~FooNative2NativePlainPort(){

}

void examples::FooNative2NativePlainPort::connect(examples::Foo* destination){
  _destination=destination;
}
void examples::FooNative2NativePlainPort::bar(const int a,const int b){
     assert(_destination!=NULL);
     _destination->bar(a,b);
}
void examples::FooNative2NativePlainPort::barParallel(const int a,const int b){
     assert(_destination!=NULL);
     _destination->barParallel(a,b);
}

