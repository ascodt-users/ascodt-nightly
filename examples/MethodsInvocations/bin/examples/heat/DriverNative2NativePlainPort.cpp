#include "examples/heat/DriverNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_examples_heat_DriverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::DriverNative2NativePlainPort *ref=new examples::heat::DriverNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_DriverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::DriverNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_DriverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::DriverNative2NativePlainPort*)ref)->connect((examples::heat::Driver*)destination);
}


examples::heat::DriverNative2NativePlainPort::DriverNative2NativePlainPort():
     _destination(0){

}

examples::heat::DriverNative2NativePlainPort::~DriverNative2NativePlainPort(){

}

void examples::heat::DriverNative2NativePlainPort::connect(examples::heat::Driver* destination){
  _destination=destination;
}
void examples::heat::DriverNative2NativePlainPort::go(){
     assert(_destination!=NULL);
     _destination->go();
}

