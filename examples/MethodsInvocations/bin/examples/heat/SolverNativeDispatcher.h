#ifndef EXAMPLES_HEAT_SOLVERNATIVEDISPATCHER_H_
#define EXAMPLES_HEAT_SOLVERNATIVEDISPATCHER_H_ 

#include "examples/heat/Solver.h"
#include <iostream>
#include <vector>

namespace examples { 
namespace heat { 
  
     class SolverNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_SolverNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_SolverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_SolverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_heat_SolverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::heat::SolverNativeDispatcher: public examples::heat::Solver{
  protected:
    std::vector<examples::heat::Solver*> _destinations;
  public:
    SolverNativeDispatcher();
    virtual ~SolverNativeDispatcher();
    
    void connect(examples::heat::Solver* ref);
    void disconnect(examples::heat::Solver* ref);
    bool isConnected() const;
    void setup(const double precision,const int iterations);
    void solve(const int* dims, const int dims_len,const double* stencil, const int stencil_len,const double* rhs, const int rhs_len,const void* dof_handle);
};

#endif
