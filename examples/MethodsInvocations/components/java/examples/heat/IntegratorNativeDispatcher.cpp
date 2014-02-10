#include "examples/heat/IntegratorNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_heat_IntegratorNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::IntegratorNativeDispatcher *ref=new examples::heat::IntegratorNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_IntegratorNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::IntegratorNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_IntegratorNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::IntegratorNativeDispatcher*)ref)->connect((examples::heat::Integrator*)destination);
}

JNIEXPORT void JNICALL Java_examples_heat_IntegratorNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::IntegratorNativeDispatcher*)ref)->disconnect((examples::heat::Integrator*)destination);
}


examples::heat::IntegratorNativeDispatcher::IntegratorNativeDispatcher(){

}

examples::heat::IntegratorNativeDispatcher::~IntegratorNativeDispatcher(){

}

void examples::heat::IntegratorNativeDispatcher::connect(examples::heat::Integrator* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::heat::IntegratorNativeDispatcher::disconnect(examples::heat::Integrator* destination){
  std::vector<examples::heat::Integrator*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::heat::IntegratorNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::heat::IntegratorNativeDispatcher::step(const int* dims, const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,const void* dof){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->step(dims,dims_len,dt,rhs,rhs_len,stencil,stencil_len,dof);
}

