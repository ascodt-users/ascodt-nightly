#include "cca/cfd/LBSolverNative2NativePlainPort.h"
#include <assert.h>
#include "Component.h"

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::LBSolverNative2NativePlainPort *ref=new cca::cfd::LBSolverNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::LBSolverNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  
  ((cca::cfd::LBSolverNative2NativePlainPort*)ref)->connect(dynamic_cast<cca::cfd::LBSolver*>((Component*)destination));
}


cca::cfd::LBSolverNative2NativePlainPort::LBSolverNative2NativePlainPort():
     _destination(0){

}

cca::cfd::LBSolverNative2NativePlainPort::~LBSolverNative2NativePlainPort(){

}

void cca::cfd::LBSolverNative2NativePlainPort::connect(cca::cfd::LBSolver* destination){
  _destination=destination;
}
void cca::cfd::LBSolverNative2NativePlainPort::setup(const std::string inputScenario){
     assert(_destination!=NULL);
     _destination->setup(inputScenario);
}
void cca::cfd::LBSolverNative2NativePlainPort::setupParallel(const std::string inputScenario){
     assert(_destination!=NULL);
     _destination->setupParallel(inputScenario);
}
void cca::cfd::LBSolverNative2NativePlainPort::setupCommForNSRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     assert(_destination!=NULL);
     _destination->setupCommForNSRegion(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids,commids_len);
}
void cca::cfd::LBSolverNative2NativePlainPort::setupCommForNSRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     assert(_destination!=NULL);
     _destination->setupCommForNSRegionParallel(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids,commids_len);
}
void cca::cfd::LBSolverNative2NativePlainPort::solve(){
     assert(_destination!=NULL);
     _destination->solve();
}
void cca::cfd::LBSolverNative2NativePlainPort::solveParallel(){
     assert(_destination!=NULL);
     _destination->solveParallel();
}
void cca::cfd::LBSolverNative2NativePlainPort::solveOneTimestep(){
     assert(_destination!=NULL);
     _destination->solveOneTimestep();
}
void cca::cfd::LBSolverNative2NativePlainPort::solveOneTimestepParallel(){
     assert(_destination!=NULL);
     _destination->solveOneTimestepParallel();
}
void cca::cfd::LBSolverNative2NativePlainPort::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     assert(_destination!=NULL);
     _destination->setVelocities(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
}
void cca::cfd::LBSolverNative2NativePlainPort::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     assert(_destination!=NULL);
     _destination->setVelocitiesParallel(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
}
void cca::cfd::LBSolverNative2NativePlainPort::setPressure(const double* pressure, const int pressure_len){
     assert(_destination!=NULL);
     _destination->setPressure(pressure,pressure_len);
}
void cca::cfd::LBSolverNative2NativePlainPort::setPressureParallel(const double* pressure, const int pressure_len){
     assert(_destination!=NULL);
     _destination->setPressureParallel(pressure,pressure_len);
}
void cca::cfd::LBSolverNative2NativePlainPort::setGradients(const double* gradients, const int gradients_len){
     assert(_destination!=NULL);
     _destination->setGradients(gradients,gradients_len);
}
void cca::cfd::LBSolverNative2NativePlainPort::setGradientsParallel(const double* gradients, const int gradients_len){
     assert(_destination!=NULL);
     _destination->setGradientsParallel(gradients,gradients_len);
}
void cca::cfd::LBSolverNative2NativePlainPort::closeLBProfiles(){
     assert(_destination!=NULL);
     _destination->closeLBProfiles();
}
void cca::cfd::LBSolverNative2NativePlainPort::closeLBProfilesParallel(){
     assert(_destination!=NULL);
     _destination->closeLBProfilesParallel();
}
void cca::cfd::LBSolverNative2NativePlainPort::printLBDensity(){
     assert(_destination!=NULL);
     _destination->printLBDensity();
}
void cca::cfd::LBSolverNative2NativePlainPort::printLBDensityParallel(){
     assert(_destination!=NULL);
     _destination->printLBDensityParallel();
}
void cca::cfd::LBSolverNative2NativePlainPort::printLBProfiles(){
     assert(_destination!=NULL);
     _destination->printLBProfiles();
}
void cca::cfd::LBSolverNative2NativePlainPort::printLBProfilesParallel(){
     assert(_destination!=NULL);
     _destination->printLBProfilesParallel();
}
void cca::cfd::LBSolverNative2NativePlainPort::forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn){
     assert(_destination!=NULL);
     _destination->forwardVelocities(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,componentSize,componentSize_len,ackn);
}
void cca::cfd::LBSolverNative2NativePlainPort::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn){
     assert(_destination!=NULL);
     _destination->forwardVelocitiesParallel(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,componentSize,componentSize_len,ackn);
}
void cca::cfd::LBSolverNative2NativePlainPort::forwardPressure(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     assert(_destination!=NULL);
     _destination->forwardPressure(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
}
void cca::cfd::LBSolverNative2NativePlainPort::forwardPressureParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     assert(_destination!=NULL);
     _destination->forwardPressureParallel(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
}
void cca::cfd::LBSolverNative2NativePlainPort::syncr(int& value){
     assert(_destination!=NULL);
     _destination->syncr(value);
}
void cca::cfd::LBSolverNative2NativePlainPort::syncrParallel(int& value){
     assert(_destination!=NULL);
     _destination->syncrParallel(value);
}
void cca::cfd::LBSolverNative2NativePlainPort::plot(){
     assert(_destination!=NULL);
     _destination->plot();
}
void cca::cfd::LBSolverNative2NativePlainPort::plotParallel(){
     assert(_destination!=NULL);
     _destination->plotParallel();
}

