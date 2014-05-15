#include "cca/cfd/NSSolverNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::NSSolverNativeDispatcher *ref=new cca::cfd::NSSolverNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::NSSolverNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::NSSolverNativeDispatcher*)ref)->connect((cca::cfd::NSSolver*)destination);
}

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::NSSolverNativeDispatcher*)ref)->disconnect((cca::cfd::NSSolver*)destination);
}


cca::cfd::NSSolverNativeDispatcher::NSSolverNativeDispatcher(){

}

cca::cfd::NSSolverNativeDispatcher::~NSSolverNativeDispatcher(){

}

void cca::cfd::NSSolverNativeDispatcher::connect(cca::cfd::NSSolver* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void cca::cfd::NSSolverNativeDispatcher::disconnect(cca::cfd::NSSolver* destination){
  std::vector<cca::cfd::NSSolver*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool cca::cfd::NSSolverNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void cca::cfd::NSSolverNativeDispatcher::setup(const std::string inputScenario){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setup(inputScenario);
}

void cca::cfd::NSSolverNativeDispatcher::setupParallel(const std::string inputScenario){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setupParallel(inputScenario);
}
void cca::cfd::NSSolverNativeDispatcher::setupCommForLBRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setupCommForLBRegion(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids,commids_len);
}

void cca::cfd::NSSolverNativeDispatcher::setupCommForLBRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setupCommForLBRegionParallel(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids,commids_len);
}
void cca::cfd::NSSolverNativeDispatcher::solve(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solve();
}

void cca::cfd::NSSolverNativeDispatcher::solveParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solveParallel();
}
void cca::cfd::NSSolverNativeDispatcher::solveOneTimestepPhaseOne(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solveOneTimestepPhaseOne();
}

void cca::cfd::NSSolverNativeDispatcher::solveOneTimestepPhaseOneParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solveOneTimestepPhaseOneParallel();
}
void cca::cfd::NSSolverNativeDispatcher::solveOneTimestepPhaseTwo(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solveOneTimestepPhaseTwo();
}

void cca::cfd::NSSolverNativeDispatcher::solveOneTimestepPhaseTwoParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solveOneTimestepPhaseTwoParallel();
}
void cca::cfd::NSSolverNativeDispatcher::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setVelocities(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
}

void cca::cfd::NSSolverNativeDispatcher::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setVelocitiesParallel(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
}
void cca::cfd::NSSolverNativeDispatcher::printNSPressure(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->printNSPressure();
}

void cca::cfd::NSSolverNativeDispatcher::printNSPressureParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->printNSPressureParallel();
}
void cca::cfd::NSSolverNativeDispatcher::printNSProfiles(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->printNSProfiles();
}

void cca::cfd::NSSolverNativeDispatcher::printNSProfilesParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->printNSProfilesParallel();
}
void cca::cfd::NSSolverNativeDispatcher::closeNSProfiles(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->closeNSProfiles();
}

void cca::cfd::NSSolverNativeDispatcher::closeNSProfilesParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->closeNSProfilesParallel();
}
void cca::cfd::NSSolverNativeDispatcher::iterateBoundary(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateBoundary();
}

void cca::cfd::NSSolverNativeDispatcher::iterateBoundaryParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateBoundaryParallel();
}
void cca::cfd::NSSolverNativeDispatcher::iterateInner(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateInner();
}

void cca::cfd::NSSolverNativeDispatcher::iterateInnerParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->iterateInnerParallel();
}
void cca::cfd::NSSolverNativeDispatcher::forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->forwardVelocities(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
}

void cca::cfd::NSSolverNativeDispatcher::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->forwardVelocitiesParallel(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
}
void cca::cfd::NSSolverNativeDispatcher::plot(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->plot();
}

void cca::cfd::NSSolverNativeDispatcher::plotParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->plotParallel();
}
void cca::cfd::NSSolverNativeDispatcher::syncr(int& value){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->syncr(value);
}

void cca::cfd::NSSolverNativeDispatcher::syncrParallel(int& value){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->syncrParallel(value);
}

