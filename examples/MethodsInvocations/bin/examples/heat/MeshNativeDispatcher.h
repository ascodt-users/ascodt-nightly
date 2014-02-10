#ifndef EXAMPLES_HEAT_MESHNATIVEDISPATCHER_H_
#define EXAMPLES_HEAT_MESHNATIVEDISPATCHER_H_ 

#include "examples/heat/Mesh.h"
#include <iostream>
#include <vector>

namespace examples { 
namespace heat { 
  
     class MeshNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_MeshNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_MeshNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_MeshNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_heat_MeshNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::heat::MeshNativeDispatcher: public examples::heat::Mesh{
  protected:
    std::vector<examples::heat::Mesh*> _destinations;
  public:
    MeshNativeDispatcher();
    virtual ~MeshNativeDispatcher();
    
    void connect(examples::heat::Mesh* ref);
    void disconnect(examples::heat::Mesh* ref);
    bool isConnected() const;
    void allocate(const int* dim, const int dim_len);
    void getData(double* data, const int data_len);
};

#endif
