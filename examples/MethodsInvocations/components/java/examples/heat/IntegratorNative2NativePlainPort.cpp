#include "examples/heat/IntegratorNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::IntegratorNative2NativePlainPort *ref=new examples::heat::IntegratorNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::IntegratorNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::IntegratorNative2NativePlainPort*)ref)->connect((examples::heat::Integrator*)destination);
}


examples::heat::IntegratorNative2NativePlainPort::IntegratorNative2NativePlainPort():
     _destination(0){

}

examples::heat::IntegratorNative2NativePlainPort::~IntegratorNative2NativePlainPort(){

}

void examples::heat::IntegratorNative2NativePlainPort::connect(examples::heat::Integrator* destination){
  _destination=destination;
}
void examples::heat::IntegratorNative2NativePlainPort::step(const int* dims, const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,const void* dof){
     assert(_destination!=NULL);
     _destination->step(dims,dims_len,dt,rhs,rhs_len,stencil,stencil_len,dof);
}

