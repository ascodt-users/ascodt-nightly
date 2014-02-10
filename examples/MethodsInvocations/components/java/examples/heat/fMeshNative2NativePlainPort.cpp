#include "examples/heat/fMeshNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_examples_heat_fMeshNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::fMeshNative2NativePlainPort *ref=new examples::heat::fMeshNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_fMeshNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::fMeshNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_fMeshNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::fMeshNative2NativePlainPort*)ref)->connect((examples::heat::fMesh*)destination);
}


examples::heat::fMeshNative2NativePlainPort::fMeshNative2NativePlainPort():
     _destination(0){

}

examples::heat::fMeshNative2NativePlainPort::~fMeshNative2NativePlainPort(){

}

void examples::heat::fMeshNative2NativePlainPort::connect(examples::heat::fMesh* destination){
  _destination=destination;
}
void examples::heat::fMeshNative2NativePlainPort::allocate(const int* dim, const int dim_len){
     assert(_destination!=NULL);
     _destination->allocate(dim,dim_len);
}
void examples::heat::fMeshNative2NativePlainPort::copyData(double* data, const int data_len){
     assert(_destination!=NULL);
     _destination->copyData(data,data_len);
}
void examples::heat::fMeshNative2NativePlainPort::getData(void*& handle){
     assert(_destination!=NULL);
     _destination->getData(handle);
}

