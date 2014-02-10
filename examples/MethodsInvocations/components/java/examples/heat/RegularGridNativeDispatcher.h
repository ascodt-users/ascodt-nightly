#ifndef EXAMPLES_HEAT_REGULARGRIDNATIVEDISPATCHER_H_
#define EXAMPLES_HEAT_REGULARGRIDNATIVEDISPATCHER_H_ 

#include "examples/heat/RegularGrid.h"
#include <iostream>
#include <vector>

namespace examples { 
namespace heat { 
  
     class RegularGridNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_RegularGridNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_RegularGridNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_RegularGridNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_heat_RegularGridNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::heat::RegularGridNativeDispatcher: public examples::heat::RegularGrid{
  protected:
    std::vector<examples::heat::RegularGrid*> _destinations;
  public:
    RegularGridNativeDispatcher();
    virtual ~RegularGridNativeDispatcher();
    
    void connect(examples::heat::RegularGrid* ref);
    void disconnect(examples::heat::RegularGrid* ref);
    bool isConnected() const;
    void setOffset(const double* offset, const int offset_len);
    void setDomain(const double* domain, const int domain_len);
    void setDimensions(const int* dimensions, const int dimensions_len);
    void addCellScalars(const std::string variableName,const double* scalars, const int scalars_len);
    void render();
};

#endif
