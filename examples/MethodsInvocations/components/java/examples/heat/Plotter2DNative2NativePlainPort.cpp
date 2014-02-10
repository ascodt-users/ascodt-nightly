#include "examples/heat/Plotter2DNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::Plotter2DNative2NativePlainPort *ref=new examples::heat::Plotter2DNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::Plotter2DNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::Plotter2DNative2NativePlainPort*)ref)->connect((examples::heat::Plotter2D*)destination);
}


examples::heat::Plotter2DNative2NativePlainPort::Plotter2DNative2NativePlainPort():
     _destination(0){

}

examples::heat::Plotter2DNative2NativePlainPort::~Plotter2DNative2NativePlainPort(){

}

void examples::heat::Plotter2DNative2NativePlainPort::connect(examples::heat::Plotter2D* destination){
  _destination=destination;
}
void examples::heat::Plotter2DNative2NativePlainPort::plotPoint(const std::string name,const double x,const double y){
     assert(_destination!=NULL);
     _destination->plotPoint(name,x,y);
}

