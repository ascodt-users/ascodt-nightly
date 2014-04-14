#include "examples/DriverNative2NativePlainPort.h"
#include <assert.h>
#include "Component.h"

JNIEXPORT void JNICALL Java_examples_DriverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::DriverNative2NativePlainPort *ref=new examples::DriverNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_DriverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::DriverNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_DriverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  
  ((examples::DriverNative2NativePlainPort*)ref)->connect(dynamic_cast<examples::Driver*>((Component*)destination));
}


examples::DriverNative2NativePlainPort::DriverNative2NativePlainPort():
     _destination(0){

}

examples::DriverNative2NativePlainPort::~DriverNative2NativePlainPort(){

}

void examples::DriverNative2NativePlainPort::connect(examples::Driver* destination){
  _destination=destination;
}
void examples::DriverNative2NativePlainPort::go(){
     assert(_destination!=NULL);
     _destination->go();
}
void examples::DriverNative2NativePlainPort::goParallel(){
     assert(_destination!=NULL);
     _destination->goParallel();
}

