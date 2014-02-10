#include "examples/heat/Plotter2DNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::Plotter2DNativeDispatcher *ref=new examples::heat::Plotter2DNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::Plotter2DNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::Plotter2DNativeDispatcher*)ref)->connect((examples::heat::Plotter2D*)destination);
}

JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::Plotter2DNativeDispatcher*)ref)->disconnect((examples::heat::Plotter2D*)destination);
}


examples::heat::Plotter2DNativeDispatcher::Plotter2DNativeDispatcher(){

}

examples::heat::Plotter2DNativeDispatcher::~Plotter2DNativeDispatcher(){

}

void examples::heat::Plotter2DNativeDispatcher::connect(examples::heat::Plotter2D* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::heat::Plotter2DNativeDispatcher::disconnect(examples::heat::Plotter2D* destination){
  std::vector<examples::heat::Plotter2D*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::heat::Plotter2DNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::heat::Plotter2DNativeDispatcher::plotPoint(const std::string name,const double x,const double y){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->plotPoint(name,x,y);
}

