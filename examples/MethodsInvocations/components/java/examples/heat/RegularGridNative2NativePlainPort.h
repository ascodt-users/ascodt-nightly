#ifndef EXAMPLES_HEAT_REGULARGRIDNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_HEAT_REGULARGRIDNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/heat/RegularGrid.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_RegularGridNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_RegularGridNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_RegularGridNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 
namespace heat { 
  
     class RegularGridNative2NativePlainPort;
} 
}

class examples::heat::RegularGridNative2NativePlainPort: public examples::heat::RegularGrid{
  private:
    examples::heat::RegularGrid* _destination;
  public:
    RegularGridNative2NativePlainPort();
    ~RegularGridNative2NativePlainPort();
    
    void connect(examples::heat::RegularGrid*);
    void setOffset(const double* offset, const int offset_len);
    void setDomain(const double* domain, const int domain_len);
    void setDimensions(const int* dimensions, const int dimensions_len);
    void addCellScalars(const std::string variableName,const double* scalars, const int scalars_len);
    void render();
};

#endif
