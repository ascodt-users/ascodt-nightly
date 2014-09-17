#include "cca/cfd/NS2LBNative2NativePlainPort.h"
#include <assert.h>
#include "Component.h"

#ifdef JAVA
JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::NS2LBNative2NativePlainPort *ref=new cca::cfd::NS2LBNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::NS2LBNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  
  ((cca::cfd::NS2LBNative2NativePlainPort*)ref)->connect(dynamic_cast<cca::cfd::NS2LB*>((Component*)destination));
}

#endif 

cca::cfd::NS2LBNative2NativePlainPort::NS2LBNative2NativePlainPort():
     _destination(0){

}

cca::cfd::NS2LBNative2NativePlainPort::~NS2LBNative2NativePlainPort(){

}

void cca::cfd::NS2LBNative2NativePlainPort::connect(cca::cfd::NS2LB* destination){
  _destination=destination;
}
void cca::cfd::NS2LBNative2NativePlainPort::iterate(){
     assert(_destination!=NULL);
     _destination->iterate();
}
void cca::cfd::NS2LBNative2NativePlainPort::iterateParallel(){
     assert(_destination!=NULL);
     _destination->iterateParallel();
}
void cca::cfd::NS2LBNative2NativePlainPort::retrieveTimestep(double& timestep){
     assert(_destination!=NULL);
     _destination->retrieveTimestep(timestep);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrieveTimestepParallel(double& timestep){
     assert(_destination!=NULL);
     _destination->retrieveTimestepParallel(timestep);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrieveVelocitiesSize(int& memory){
     assert(_destination!=NULL);
     _destination->retrieveVelocitiesSize(memory);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrieveVelocitiesSizeParallel(int& memory){
     assert(_destination!=NULL);
     _destination->retrieveVelocitiesSizeParallel(memory);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
     assert(_destination!=NULL);
     _destination->retrieveVelocitiesCopy(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
     assert(_destination!=NULL);
     _destination->retrieveVelocitiesCopyParallel(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrieveJacobianCopy(double* jacobian, const int jacobian_len){
     assert(_destination!=NULL);
     _destination->retrieveJacobianCopy(jacobian,jacobian_len);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrieveJacobianCopyParallel(double* jacobian, const int jacobian_len){
     assert(_destination!=NULL);
     _destination->retrieveJacobianCopyParallel(jacobian,jacobian_len);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrievePressureCopy(double* pressure, const int pressure_len){
     assert(_destination!=NULL);
     _destination->retrievePressureCopy(pressure,pressure_len);
}
void cca::cfd::NS2LBNative2NativePlainPort::retrievePressureCopyParallel(double* pressure, const int pressure_len){
     assert(_destination!=NULL);
     _destination->retrievePressureCopyParallel(pressure,pressure_len);
}

