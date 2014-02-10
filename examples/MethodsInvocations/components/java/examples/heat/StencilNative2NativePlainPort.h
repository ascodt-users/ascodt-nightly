#ifndef EXAMPLES_HEAT_STENCILNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_HEAT_STENCILNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/heat/Stencil.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_StencilNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_StencilNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_StencilNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 
namespace heat { 
  
     class StencilNative2NativePlainPort;
} 
}

class examples::heat::StencilNative2NativePlainPort: public examples::heat::Stencil{
  private:
    examples::heat::Stencil* _destination;
  public:
    StencilNative2NativePlainPort();
    ~StencilNative2NativePlainPort();
    
    void connect(examples::heat::Stencil*);
    void getStencil(double* stencil, const int stencil_len);
};

#endif
