#ifndef EXAMPLES_HEAT_INTEGRATOR2NATIVE2JAVAPLAINPORT_H_
#define EXAMPLES_HEAT_INTEGRATOR2NATIVE2JAVAPLAINPORT_H_ 

#include "examples/heat/Integrator.h"
#include <jni.h> 
#include <iostream>
//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);

#ifdef __cplusplus
  }
#endif




namespace examples { 
namespace heat { 
  
     class IntegratorNative2JavaPlainPort;
} 
}

class examples::heat::IntegratorNative2JavaPlainPort: public examples::heat::Integrator{
  private:
    JavaVM* _jvm;
    jobject _obj;
  public:
    IntegratorNative2JavaPlainPort(JavaVM* jvm,jobject obj);
    ~IntegratorNative2JavaPlainPort();
    void step(const int* dims, const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,const void* dof);
};
#endif
