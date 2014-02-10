#include "examples/heat/MeshNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_examples_heat_MeshNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::MeshNative2NativePlainPort *ref=new examples::heat::MeshNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_MeshNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::MeshNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_MeshNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::MeshNative2NativePlainPort*)ref)->connect((examples::heat::Mesh*)destination);
}


examples::heat::MeshNative2NativePlainPort::MeshNative2NativePlainPort():
     _destination(0){

}

examples::heat::MeshNative2NativePlainPort::~MeshNative2NativePlainPort(){

}

void examples::heat::MeshNative2NativePlainPort::connect(examples::heat::Mesh* destination){
  _destination=destination;
}
void examples::heat::MeshNative2NativePlainPort::allocate(const int* dim, const int dim_len){
     assert(_destination!=NULL);
     _destination->allocate(dim,dim_len);
}
void examples::heat::MeshNative2NativePlainPort::getData(double* data, const int data_len){
     assert(_destination!=NULL);
     _destination->getData(data,data_len);
}

