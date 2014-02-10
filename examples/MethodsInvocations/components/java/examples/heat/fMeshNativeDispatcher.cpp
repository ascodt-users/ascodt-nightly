#include "examples/heat/fMeshNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_heat_fMeshNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::fMeshNativeDispatcher *ref=new examples::heat::fMeshNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_fMeshNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::fMeshNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_fMeshNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::fMeshNativeDispatcher*)ref)->connect((examples::heat::fMesh*)destination);
}

JNIEXPORT void JNICALL Java_examples_heat_fMeshNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::fMeshNativeDispatcher*)ref)->disconnect((examples::heat::fMesh*)destination);
}


examples::heat::fMeshNativeDispatcher::fMeshNativeDispatcher(){

}

examples::heat::fMeshNativeDispatcher::~fMeshNativeDispatcher(){

}

void examples::heat::fMeshNativeDispatcher::connect(examples::heat::fMesh* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::heat::fMeshNativeDispatcher::disconnect(examples::heat::fMesh* destination){
  std::vector<examples::heat::fMesh*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::heat::fMeshNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::heat::fMeshNativeDispatcher::allocate(const int* dim, const int dim_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->allocate(dim,dim_len);
}
void examples::heat::fMeshNativeDispatcher::copyData(double* data, const int data_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->copyData(data,data_len);
}
void examples::heat::fMeshNativeDispatcher::getData(void*& handle){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->getData(handle);
}

