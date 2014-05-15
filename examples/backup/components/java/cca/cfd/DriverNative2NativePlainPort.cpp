#include "cca/cfd/DriverNative2NativePlainPort.h"
#include <assert.h>
#include "Component.h"

JNIEXPORT void JNICALL Java_cca_cfd_DriverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::DriverNative2NativePlainPort *ref=new cca::cfd::DriverNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_DriverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::DriverNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_DriverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  
  ((cca::cfd::DriverNative2NativePlainPort*)ref)->connect(dynamic_cast<cca::cfd::Driver*>((Component*)destination));
}


cca::cfd::DriverNative2NativePlainPort::DriverNative2NativePlainPort():
     _destination(0){

}

cca::cfd::DriverNative2NativePlainPort::~DriverNative2NativePlainPort(){

}

void cca::cfd::DriverNative2NativePlainPort::connect(cca::cfd::Driver* destination){
  _destination=destination;
}
void cca::cfd::DriverNative2NativePlainPort::go(const std::string configFile){
     assert(_destination!=NULL);
     _destination->go(configFile);
}
void cca::cfd::DriverNative2NativePlainPort::goParallel(const std::string configFile){
     assert(_destination!=NULL);
     _destination->goParallel(configFile);
}

