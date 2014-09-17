#include "cca/cfd/NS2LBNativeDispatcher.h"
#include <algorithm>

#ifdef JAVA
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::NS2LBNativeDispatcher *ref=new cca::cfd::NS2LBNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::NS2LBNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::NS2LBNativeDispatcher*)ref)->connect((cca::cfd::NS2LB*)destination);
}

JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::NS2LBNativeDispatcher*)ref)->disconnect((cca::cfd::NS2LB*)destination);
}
#endif

cca::cfd::NS2LBNativeDispatcher::NS2LBNativeDispatcher(){

}

cca::cfd::NS2LBNativeDispatcher::~NS2LBNativeDispatcher(){

}

void cca::cfd::NS2LBNativeDispatcher::connect(cca::cfd::NS2LB* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void cca::cfd::NS2LBNativeDispatcher::disconnect(cca::cfd::NS2LB* destination){
  std::vector<cca::cfd::NS2LB*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool cca::cfd::NS2LBNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void cca::cfd::NS2LBNativeDispatcher::iterate(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterate();
}

void cca::cfd::NS2LBNativeDispatcher::iterateParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateParallel();
}
void cca::cfd::NS2LBNativeDispatcher::retrieveTimestep(double& timestep){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveTimestep(timestep);
}

void cca::cfd::NS2LBNativeDispatcher::retrieveTimestepParallel(double& timestep){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveTimestepParallel(timestep);
}
void cca::cfd::NS2LBNativeDispatcher::retrieveVelocitiesSize(int& memory){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveVelocitiesSize(memory);
}

void cca::cfd::NS2LBNativeDispatcher::retrieveVelocitiesSizeParallel(int& memory){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveVelocitiesSizeParallel(memory);
}
void cca::cfd::NS2LBNativeDispatcher::retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveVelocitiesCopy(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
}

void cca::cfd::NS2LBNativeDispatcher::retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveVelocitiesCopyParallel(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
}
void cca::cfd::NS2LBNativeDispatcher::retrieveJacobianCopy(double* jacobian, const int jacobian_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveJacobianCopy(jacobian,jacobian_len);
}

void cca::cfd::NS2LBNativeDispatcher::retrieveJacobianCopyParallel(double* jacobian, const int jacobian_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrieveJacobianCopyParallel(jacobian,jacobian_len);
}
void cca::cfd::NS2LBNativeDispatcher::retrievePressureCopy(double* pressure, const int pressure_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrievePressureCopy(pressure,pressure_len);
}

void cca::cfd::NS2LBNativeDispatcher::retrievePressureCopyParallel(double* pressure, const int pressure_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->retrievePressureCopyParallel(pressure,pressure_len);
}

