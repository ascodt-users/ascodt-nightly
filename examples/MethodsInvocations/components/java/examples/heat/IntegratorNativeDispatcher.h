#ifndef EXAMPLES_HEAT_INTEGRATORNATIVEDISPATCHER_H_
#define EXAMPLES_HEAT_INTEGRATORNATIVEDISPATCHER_H_ 

#include "examples/heat/Integrator.h"
#include <iostream>
#include <vector>

namespace examples { 
namespace heat { 
  
     class IntegratorNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_heat_IntegratorNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::heat::IntegratorNativeDispatcher: public examples::heat::Integrator{
  protected:
    std::vector<examples::heat::Integrator*> _destinations;
  public:
    IntegratorNativeDispatcher();
    virtual ~IntegratorNativeDispatcher();
    
    void connect(examples::heat::Integrator* ref);
    void disconnect(examples::heat::Integrator* ref);
    bool isConnected() const;
    void step(const int* dims, const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,const void* dof);
};

#endif
