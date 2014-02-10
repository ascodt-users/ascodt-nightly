#include "de/tum/DriverNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_de_tum_DriverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::DriverNative2NativePlainPort *ref=new de::tum::DriverNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_DriverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::DriverNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_DriverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::DriverNative2NativePlainPort*)ref)->connect((de::tum::Driver*)destination);
}


de::tum::DriverNative2NativePlainPort::DriverNative2NativePlainPort():
     _destination(0){

}

de::tum::DriverNative2NativePlainPort::~DriverNative2NativePlainPort(){

}

void de::tum::DriverNative2NativePlainPort::connect(de::tum::Driver* destination){
  _destination=destination;
}
void de::tum::DriverNative2NativePlainPort::go(){
     assert(_destination!=NULL);
     _destination->go();
}

