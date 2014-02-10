#include "examples/heat/MeshNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_heat_MeshNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::MeshNativeDispatcher *ref=new examples::heat::MeshNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_MeshNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::MeshNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_MeshNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::MeshNativeDispatcher*)ref)->connect((examples::heat::Mesh*)destination);
}

JNIEXPORT void JNICALL Java_examples_heat_MeshNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::MeshNativeDispatcher*)ref)->disconnect((examples::heat::Mesh*)destination);
}


examples::heat::MeshNativeDispatcher::MeshNativeDispatcher(){

}

examples::heat::MeshNativeDispatcher::~MeshNativeDispatcher(){

}

void examples::heat::MeshNativeDispatcher::connect(examples::heat::Mesh* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::heat::MeshNativeDispatcher::disconnect(examples::heat::Mesh* destination){
  std::vector<examples::heat::Mesh*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::heat::MeshNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::heat::MeshNativeDispatcher::allocate(const int* dim, const int dim_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->allocate(dim,dim_len);
}
void examples::heat::MeshNativeDispatcher::getData(double* data, const int data_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->getData(data,data_len);
}

