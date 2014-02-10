#ifndef EXAMPLES_HEAT_PLOTTER2DNATIVEDISPATCHER_H_
#define EXAMPLES_HEAT_PLOTTER2DNATIVEDISPATCHER_H_ 

#include "examples/heat/Plotter2D.h"
#include <iostream>
#include <vector>

namespace examples { 
namespace heat { 
  
     class Plotter2DNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class examples::heat::Plotter2DNativeDispatcher: public examples::heat::Plotter2D{
  protected:
    std::vector<examples::heat::Plotter2D*> _destinations;
  public:
    Plotter2DNativeDispatcher();
    virtual ~Plotter2DNativeDispatcher();
    
    void connect(examples::heat::Plotter2D* ref);
    void disconnect(examples::heat::Plotter2D* ref);
    bool isConnected() const;
    void plotPoint(const std::string name,const double x,const double y);
};

#endif
