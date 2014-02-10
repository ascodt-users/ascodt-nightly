#include "examples/heat/SolverNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_examples_heat_SolverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::SolverNative2NativePlainPort *ref=new examples::heat::SolverNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_SolverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::SolverNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_SolverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::SolverNative2NativePlainPort*)ref)->connect((examples::heat::Solver*)destination);
}


examples::heat::SolverNative2NativePlainPort::SolverNative2NativePlainPort():
     _destination(0){

}

examples::heat::SolverNative2NativePlainPort::~SolverNative2NativePlainPort(){

}

void examples::heat::SolverNative2NativePlainPort::connect(examples::heat::Solver* destination){
  _destination=destination;
}
void examples::heat::SolverNative2NativePlainPort::setup(const double precision,const int iterations){
     assert(_destination!=NULL);
     _destination->setup(precision,iterations);
}
void examples::heat::SolverNative2NativePlainPort::solve(const int* dims, const int dims_len,const double* stencil, const int stencil_len,const double* rhs, const int rhs_len,const void* dof_handle){
     assert(_destination!=NULL);
     _destination->solve(dims,dims_len,stencil,stencil_len,rhs,rhs_len,dof_handle);
}

