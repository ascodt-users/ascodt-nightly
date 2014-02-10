#ifndef EXAMPLES_HEAT_FMESHNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_HEAT_FMESHNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/heat/fMesh.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_fMeshNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_fMeshNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_fMeshNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 
namespace heat { 
  
     class fMeshNative2NativePlainPort;
} 
}

class examples::heat::fMeshNative2NativePlainPort: public examples::heat::fMesh{
  private:
    examples::heat::fMesh* _destination;
  public:
    fMeshNative2NativePlainPort();
    ~fMeshNative2NativePlainPort();
    
    void connect(examples::heat::fMesh*);
    void allocate(const int* dim, const int dim_len);
    void copyData(double* data, const int data_len);
    void getData(void*& handle);
};

#endif
