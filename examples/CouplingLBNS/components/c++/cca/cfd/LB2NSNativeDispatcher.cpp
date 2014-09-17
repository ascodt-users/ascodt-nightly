#include "cca/cfd/LB2NSNativeDispatcher.h"
#include <algorithm>

#ifdef JAVA
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::LB2NSNativeDispatcher *ref=new cca::cfd::LB2NSNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::LB2NSNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::LB2NSNativeDispatcher*)ref)->connect((cca::cfd::LB2NS*)destination);
}

JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::LB2NSNativeDispatcher*)ref)->disconnect((cca::cfd::LB2NS*)destination);
}
#endif

cca::cfd::LB2NSNativeDispatcher::LB2NSNativeDispatcher(){

}

cca::cfd::LB2NSNativeDispatcher::~LB2NSNativeDispatcher(){

}

void cca::cfd::LB2NSNativeDispatcher::connect(cca::cfd::LB2NS* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void cca::cfd::LB2NSNativeDispatcher::disconnect(cca::cfd::LB2NS* destination){
  std::vector<cca::cfd::LB2NS*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool cca::cfd::LB2NSNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void cca::cfd::LB2NSNativeDispatcher::iterateBoundary(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateBoundary();
}

void cca::cfd::LB2NSNativeDispatcher::iterateBoundaryParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateBoundaryParallel();
}
void cca::cfd::LB2NSNativeDispatcher::iterateInner(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateInner();
}

void cca::cfd::LB2NSNativeDispatcher::iterateInnerParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateInnerParallel();
}
void cca::cfd::LB2NSNativeDispatcher::retrieveTimestep(double& dt){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveTimestep(dt);
}

void cca::cfd::LB2NSNativeDispatcher::retrieveTimestepParallel(double& dt){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveTimestepParallel(dt);
}
void cca::cfd::LB2NSNativeDispatcher::retrieveVelocitiesSize(int& memoryX,int& memoryY,int& memoryZ){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveVelocitiesSize(memoryX,memoryY,memoryZ);
}

void cca::cfd::LB2NSNativeDispatcher::retrieveVelocitiesSizeParallel(int& memoryX,int& memoryY,int& memoryZ){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveVelocitiesSizeParallel(memoryX,memoryY,memoryZ);
}
void cca::cfd::LB2NSNativeDispatcher::retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveVelocitiesCopy(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
}

void cca::cfd::LB2NSNativeDispatcher::retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveVelocitiesCopyParallel(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
}

