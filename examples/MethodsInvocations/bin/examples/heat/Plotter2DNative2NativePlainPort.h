#ifndef EXAMPLES_HEAT_PLOTTER2DNATIVE2NATIVEPLAINPORT_H_
#define EXAMPLES_HEAT_PLOTTER2DNATIVE2NATIVEPLAINPORT_H_ 

#include "examples/heat/Plotter2D.h"
#include <jni.h> 
#include <iostream>

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination);


#ifdef __cplusplus
  }
#endif

namespace examples { 
namespace heat { 
  
     class Plotter2DNative2NativePlainPort;
} 
}

class examples::heat::Plotter2DNative2NativePlainPort: public examples::heat::Plotter2D{
  private:
    examples::heat::Plotter2D* _destination;
  public:
    Plotter2DNative2NativePlainPort();
    ~Plotter2DNative2NativePlainPort();
    
    void connect(examples::heat::Plotter2D*);
    void plotPoint(const std::string name,const double x,const double y);
};

#endif
