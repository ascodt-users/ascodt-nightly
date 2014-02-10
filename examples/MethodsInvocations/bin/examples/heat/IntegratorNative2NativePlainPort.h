#ifndef EXAMPLES_HEAT_INTEGRATORNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_HEAT_INTEGRATORNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/heat/Integrator.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 
namespace heat { 
  
     class IntegratorNative2NativePlainPort;
} 
}

class examples::heat::IntegratorNative2NativePlainPort: public examples::heat::Integrator{
  private:
    examples::heat::Integrator* _destination;
  public:
    IntegratorNative2NativePlainPort();
    ~IntegratorNative2NativePlainPort();
    
    void connect(examples::heat::Integrator*);
    void step(const int* dims, const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,const void* dof);
};

#endif
