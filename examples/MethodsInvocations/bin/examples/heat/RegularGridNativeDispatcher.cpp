#include "examples/heat/RegularGridNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_heat_RegularGridNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::RegularGridNativeDispatcher *ref=new examples::heat::RegularGridNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_RegularGridNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::RegularGridNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_RegularGridNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::RegularGridNativeDispatcher*)ref)->connect((examples::heat::RegularGrid*)destination);
}

JNIEXPORT void JNICALL Java_examples_heat_RegularGridNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::RegularGridNativeDispatcher*)ref)->disconnect((examples::heat::RegularGrid*)destination);
}


examples::heat::RegularGridNativeDispatcher::RegularGridNativeDispatcher(){

}

examples::heat::RegularGridNativeDispatcher::~RegularGridNativeDispatcher(){

}

void examples::heat::RegularGridNativeDispatcher::connect(examples::heat::RegularGrid* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::heat::RegularGridNativeDispatcher::disconnect(examples::heat::RegularGrid* destination){
  std::vector<examples::heat::RegularGrid*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::heat::RegularGridNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::heat::RegularGridNativeDispatcher::setOffset(const double* offset, const int offset_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setOffset(offset,offset_len);
}
void examples::heat::RegularGridNativeDispatcher::setDomain(const double* domain, const int domain_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setDomain(domain,domain_len);
}
void examples::heat::RegularGridNativeDispatcher::setDimensions(const int* dimensions, const int dimensions_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setDimensions(dimensions,dimensions_len);
}
void examples::heat::RegularGridNativeDispatcher::addCellScalars(const std::string variableName,const double* scalars, const int scalars_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->addCellScalars(variableName,scalars,scalars_len);
}
void examples::heat::RegularGridNativeDispatcher::render(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->render();
}

