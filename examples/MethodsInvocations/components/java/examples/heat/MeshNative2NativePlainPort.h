#ifndef EXAMPLES_HEAT_MESHNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_HEAT_MESHNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/heat/Mesh.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_MeshNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_MeshNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_MeshNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 
namespace heat { 
  
     class MeshNative2NativePlainPort;
} 
}

class examples::heat::MeshNative2NativePlainPort: public examples::heat::Mesh{
  private:
    examples::heat::Mesh* _destination;
  public:
    MeshNative2NativePlainPort();
    ~MeshNative2NativePlainPort();
    
    void connect(examples::heat::Mesh*);
    void allocate(const int* dim, const int dim_len);
    void getData(double* data, const int data_len);
};

#endif
