#ifndef EXAMPLES_HEAT_FMESHNATIVEDISPATCHER_H_
#define EXAMPLES_HEAT_FMESHNATIVEDISPATCHER_H_ 

#include "examples/heat/fMesh.h"
#include <iostream>
#include <vector>

namespace examples { 
namespace heat { 
  
     class fMeshNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_fMeshNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_fMeshNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_fMeshNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_heat_fMeshNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::heat::fMeshNativeDispatcher: public examples::heat::fMesh{
  protected:
    std::vector<examples::heat::fMesh*> _destinations;
  public:
    fMeshNativeDispatcher();
    virtual ~fMeshNativeDispatcher();
    
    void connect(examples::heat::fMesh* ref);
    void disconnect(examples::heat::fMesh* ref);
    bool isConnected() const;
    void allocate(const int* dim, const int dim_len);
    void copyData(double* data, const int data_len);
    void getData(void*& handle);
};

#endif
