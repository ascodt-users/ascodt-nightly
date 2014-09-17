#include "cca/cfd/LB2NSNative2NativePlainPort.h"
#include <assert.h>
#include "Component.h"

#ifdef JAVA
JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::LB2NSNative2NativePlainPort *ref=new cca::cfd::LB2NSNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::LB2NSNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  
  ((cca::cfd::LB2NSNative2NativePlainPort*)ref)->connect(dynamic_cast<cca::cfd::LB2NS*>((Component*)destination));
}

#endif 

cca::cfd::LB2NSNative2NativePlainPort::LB2NSNative2NativePlainPort():
     _destination(0){

}

cca::cfd::LB2NSNative2NativePlainPort::~LB2NSNative2NativePlainPort(){

}

void cca::cfd::LB2NSNative2NativePlainPort::connect(cca::cfd::LB2NS* destination){
  _destination=destination;
}
void cca::cfd::LB2NSNative2NativePlainPort::iterateBoundary(){
     assert(_destination!=NULL);
     _destination->iterateBoundary();
}
void cca::cfd::LB2NSNative2NativePlainPort::iterateBoundaryParallel(){
     assert(_destination!=NULL);
     _destination->iterateBoundaryParallel();
}
void cca::cfd::LB2NSNative2NativePlainPort::iterateInner(){
     assert(_destination!=NULL);
     _destination->iterateInner();
}
void cca::cfd::LB2NSNative2NativePlainPort::iterateInnerParallel(){
     assert(_destination!=NULL);
     _destination->iterateInnerParallel();
}
void cca::cfd::LB2NSNative2NativePlainPort::retrieveTimestep(double& dt){
     assert(_destination!=NULL);
     _destination->retrieveTimestep(dt);
}
void cca::cfd::LB2NSNative2NativePlainPort::retrieveTimestepParallel(double& dt){
     assert(_destination!=NULL);
     _destination->retrieveTimestepParallel(dt);
}
void cca::cfd::LB2NSNative2NativePlainPort::retrieveVelocitiesSize(int& memoryX,int& memoryY,int& memoryZ){
     assert(_destination!=NULL);
     _destination->retrieveVelocitiesSize(memoryX,memoryY,memoryZ);
}
void cca::cfd::LB2NSNative2NativePlainPort::retrieveVelocitiesSizeParallel(int& memoryX,int& memoryY,int& memoryZ){
     assert(_destination!=NULL);
     _destination->retrieveVelocitiesSizeParallel(memoryX,memoryY,memoryZ);
}
void cca::cfd::LB2NSNative2NativePlainPort::retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
     assert(_destination!=NULL);
     _destination->retrieveVelocitiesCopy(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
}
void cca::cfd::LB2NSNative2NativePlainPort::retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
     assert(_destination!=NULL);
     _destination->retrieveVelocitiesCopyParallel(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
}

