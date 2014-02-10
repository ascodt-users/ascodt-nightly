#ifndef EXAMPLES_HEAT_STENCILNATIVEDISPATCHER_H_
#define EXAMPLES_HEAT_STENCILNATIVEDISPATCHER_H_ 

#include "examples/heat/Stencil.h"
#include <iostream>
#include <vector>

namespace examples { 
namespace heat { 
  
     class StencilNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_StencilNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_StencilNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_StencilNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_heat_StencilNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::heat::StencilNativeDispatcher: public examples::heat::Stencil{
  protected:
    std::vector<examples::heat::Stencil*> _destinations;
  public:
    StencilNativeDispatcher();
    virtual ~StencilNativeDispatcher();
    
    void connect(examples::heat::Stencil* ref);
    void disconnect(examples::heat::Stencil* ref);
    bool isConnected() const;
    void getStencil(double* stencil, const int stencil_len);
};

#endif
