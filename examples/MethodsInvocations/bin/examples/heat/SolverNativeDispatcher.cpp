#include "examples/heat/SolverNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_heat_SolverNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::SolverNativeDispatcher *ref=new examples::heat::SolverNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_SolverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::SolverNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_SolverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::SolverNativeDispatcher*)ref)->connect((examples::heat::Solver*)destination);
}

JNIEXPORT void JNICALL Java_examples_heat_SolverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::SolverNativeDispatcher*)ref)->disconnect((examples::heat::Solver*)destination);
}


examples::heat::SolverNativeDispatcher::SolverNativeDispatcher(){

}

examples::heat::SolverNativeDispatcher::~SolverNativeDispatcher(){

}

void examples::heat::SolverNativeDispatcher::connect(examples::heat::Solver* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::heat::SolverNativeDispatcher::disconnect(examples::heat::Solver* destination){
  std::vector<examples::heat::Solver*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::heat::SolverNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::heat::SolverNativeDispatcher::setup(const double precision,const int iterations){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setup(precision,iterations);
}
void examples::heat::SolverNativeDispatcher::solve(const int* dims, const int dims_len,const double* stencil, const int stencil_len,const double* rhs, const int rhs_len,const void* dof_handle){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solve(dims,dims_len,stencil,stencil_len,rhs,rhs_len,dof_handle);
}

