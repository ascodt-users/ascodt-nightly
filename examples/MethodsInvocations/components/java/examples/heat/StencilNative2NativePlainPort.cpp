#include "examples/heat/StencilNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_examples_heat_StencilNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::StencilNative2NativePlainPort *ref=new examples::heat::StencilNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_StencilNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::StencilNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_StencilNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::StencilNative2NativePlainPort*)ref)->connect((examples::heat::Stencil*)destination);
}


examples::heat::StencilNative2NativePlainPort::StencilNative2NativePlainPort():
     _destination(0){

}

examples::heat::StencilNative2NativePlainPort::~StencilNative2NativePlainPort(){

}

void examples::heat::StencilNative2NativePlainPort::connect(examples::heat::Stencil* destination){
  _destination=destination;
}
void examples::heat::StencilNative2NativePlainPort::getStencil(double* stencil, const int stencil_len){
     assert(_destination!=NULL);
     _destination->getStencil(stencil,stencil_len);
}

