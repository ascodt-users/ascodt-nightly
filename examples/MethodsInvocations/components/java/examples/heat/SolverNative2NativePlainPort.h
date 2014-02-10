#ifndef EXAMPLES_HEAT_SOLVERNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_HEAT_SOLVERNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/heat/Solver.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_SolverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_SolverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_SolverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 
namespace heat { 
  
     class SolverNative2NativePlainPort;
} 
}

class examples::heat::SolverNative2NativePlainPort: public examples::heat::Solver{
  private:
    examples::heat::Solver* _destination;
  public:
    SolverNative2NativePlainPort();
    ~SolverNative2NativePlainPort();
    
    void connect(examples::heat::Solver*);
    void setup(const double precision,const int iterations);
    void solve(const int* dims, const int dims_len,const double* stencil, const int stencil_len,const double* rhs, const int rhs_len,const void* dof_handle);
};

#endif
