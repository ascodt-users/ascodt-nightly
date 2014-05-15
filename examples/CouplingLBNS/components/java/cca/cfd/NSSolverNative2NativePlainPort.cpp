#include "cca/cfd/NSSolverNative2NativePlainPort.h"
#include <assert.h>
#include "Component.h"

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::NSSolverNative2NativePlainPort *ref=new cca::cfd::NSSolverNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::NSSolverNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  
  ((cca::cfd::NSSolverNative2NativePlainPort*)ref)->connect(dynamic_cast<cca::cfd::NSSolver*>((Component*)destination));
}


cca::cfd::NSSolverNative2NativePlainPort::NSSolverNative2NativePlainPort():
     _destination(0){

}

cca::cfd::NSSolverNative2NativePlainPort::~NSSolverNative2NativePlainPort(){

}

void cca::cfd::NSSolverNative2NativePlainPort::connect(cca::cfd::NSSolver* destination){
  _destination=destination;
}
void cca::cfd::NSSolverNative2NativePlainPort::setup(const std::string inputScenario){
     assert(_destination!=NULL);
     _destination->setup(inputScenario);
}
void cca::cfd::NSSolverNative2NativePlainPort::setupParallel(const std::string inputScenario){
     assert(_destination!=NULL);
     _destination->setupParallel(inputScenario);
}
void cca::cfd::NSSolverNative2NativePlainPort::setupCommForLBRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     assert(_destination!=NULL);
     _destination->setupCommForLBRegion(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids,commids_len);
}
void cca::cfd::NSSolverNative2NativePlainPort::setupCommForLBRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     assert(_destination!=NULL);
     _destination->setupCommForLBRegionParallel(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids,commids_len);
}
void cca::cfd::NSSolverNative2NativePlainPort::solve(){
     assert(_destination!=NULL);
     _destination->solve();
}
void cca::cfd::NSSolverNative2NativePlainPort::solveParallel(){
     assert(_destination!=NULL);
     _destination->solveParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::solveOneTimestepPhaseOne(){
     assert(_destination!=NULL);
     _destination->solveOneTimestepPhaseOne();
}
void cca::cfd::NSSolverNative2NativePlainPort::solveOneTimestepPhaseOneParallel(){
     assert(_destination!=NULL);
     _destination->solveOneTimestepPhaseOneParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::solveOneTimestepPhaseTwo(){
     assert(_destination!=NULL);
     _destination->solveOneTimestepPhaseTwo();
}
void cca::cfd::NSSolverNative2NativePlainPort::solveOneTimestepPhaseTwoParallel(){
     assert(_destination!=NULL);
     _destination->solveOneTimestepPhaseTwoParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     assert(_destination!=NULL);
     _destination->setVelocities(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
}
void cca::cfd::NSSolverNative2NativePlainPort::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     assert(_destination!=NULL);
     _destination->setVelocitiesParallel(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
}
void cca::cfd::NSSolverNative2NativePlainPort::printNSPressure(){
     assert(_destination!=NULL);
     _destination->printNSPressure();
}
void cca::cfd::NSSolverNative2NativePlainPort::printNSPressureParallel(){
     assert(_destination!=NULL);
     _destination->printNSPressureParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::printNSProfiles(){
     assert(_destination!=NULL);
     _destination->printNSProfiles();
}
void cca::cfd::NSSolverNative2NativePlainPort::printNSProfilesParallel(){
     assert(_destination!=NULL);
     _destination->printNSProfilesParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::closeNSProfiles(){
     assert(_destination!=NULL);
     _destination->closeNSProfiles();
}
void cca::cfd::NSSolverNative2NativePlainPort::closeNSProfilesParallel(){
     assert(_destination!=NULL);
     _destination->closeNSProfilesParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::iterateBoundary(){
     assert(_destination!=NULL);
     _destination->iterateBoundary();
}
void cca::cfd::NSSolverNative2NativePlainPort::iterateBoundaryParallel(){
     assert(_destination!=NULL);
     _destination->iterateBoundaryParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::iterateInner(){
     assert(_destination!=NULL);
     _destination->iterateInner();
}
void cca::cfd::NSSolverNative2NativePlainPort::iterateInnerParallel(){
     assert(_destination!=NULL);
     _destination->iterateInnerParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     assert(_destination!=NULL);
     _destination->forwardVelocities(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
}
void cca::cfd::NSSolverNative2NativePlainPort::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     assert(_destination!=NULL);
     _destination->forwardVelocitiesParallel(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
}
void cca::cfd::NSSolverNative2NativePlainPort::plot(){
     assert(_destination!=NULL);
     _destination->plot();
}
void cca::cfd::NSSolverNative2NativePlainPort::plotParallel(){
     assert(_destination!=NULL);
     _destination->plotParallel();
}
void cca::cfd::NSSolverNative2NativePlainPort::syncr(int& value){
     assert(_destination!=NULL);
     _destination->syncr(value);
}
void cca::cfd::NSSolverNative2NativePlainPort::syncrParallel(int& value){
     assert(_destination!=NULL);
     _destination->syncrParallel(value);
}

