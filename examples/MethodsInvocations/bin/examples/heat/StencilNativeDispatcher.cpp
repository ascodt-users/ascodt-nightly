#include "examples/heat/StencilNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_heat_StencilNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::StencilNativeDispatcher *ref=new examples::heat::StencilNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_StencilNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::StencilNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_StencilNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::StencilNativeDispatcher*)ref)->connect((examples::heat::Stencil*)destination);
}

JNIEXPORT void JNICALL Java_examples_heat_StencilNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::StencilNativeDispatcher*)ref)->disconnect((examples::heat::Stencil*)destination);
}


examples::heat::StencilNativeDispatcher::StencilNativeDispatcher(){

}

examples::heat::StencilNativeDispatcher::~StencilNativeDispatcher(){

}

void examples::heat::StencilNativeDispatcher::connect(examples::heat::Stencil* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::heat::StencilNativeDispatcher::disconnect(examples::heat::Stencil* destination){
  std::vector<examples::heat::Stencil*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::heat::StencilNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::heat::StencilNativeDispatcher::getStencil(double* stencil, const int stencil_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->getStencil(stencil,stencil_len);
}

