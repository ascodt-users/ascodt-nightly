#include "cca/cfd/LBSolverNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::LBSolverNativeDispatcher *ref=new cca::cfd::LBSolverNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::LBSolverNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::LBSolverNativeDispatcher*)ref)->connect((cca::cfd::LBSolver*)destination);
}

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::LBSolverNativeDispatcher*)ref)->disconnect((cca::cfd::LBSolver*)destination);
}


cca::cfd::LBSolverNativeDispatcher::LBSolverNativeDispatcher(){

}

cca::cfd::LBSolverNativeDispatcher::~LBSolverNativeDispatcher(){

}

void cca::cfd::LBSolverNativeDispatcher::connect(cca::cfd::LBSolver* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void cca::cfd::LBSolverNativeDispatcher::disconnect(cca::cfd::LBSolver* destination){
  std::vector<cca::cfd::LBSolver*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool cca::cfd::LBSolverNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void cca::cfd::LBSolverNativeDispatcher::setup(const std::string inputScenario){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setup(inputScenario);
}

void cca::cfd::LBSolverNativeDispatcher::setupParallel(const std::string inputScenario){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setupParallel(inputScenario);
}
void cca::cfd::LBSolverNativeDispatcher::setupCommForNSRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setupCommForNSRegion(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids,commids_len);
}

void cca::cfd::LBSolverNativeDispatcher::setupCommForNSRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setupCommForNSRegionParallel(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids,commids_len);
}
void cca::cfd::LBSolverNativeDispatcher::solve(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solve();
}

void cca::cfd::LBSolverNativeDispatcher::solveParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solveParallel();
}
void cca::cfd::LBSolverNativeDispatcher::solveOneTimestep(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solveOneTimestep();
}

void cca::cfd::LBSolverNativeDispatcher::solveOneTimestepParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->solveOneTimestepParallel();
}
void cca::cfd::LBSolverNativeDispatcher::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setVelocities(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
}

void cca::cfd::LBSolverNativeDispatcher::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setVelocitiesParallel(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
}
void cca::cfd::LBSolverNativeDispatcher::setPressure(const double* pressure, const int pressure_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setPressure(pressure,pressure_len);
}

void cca::cfd::LBSolverNativeDispatcher::setPressureParallel(const double* pressure, const int pressure_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setPressureParallel(pressure,pressure_len);
}
void cca::cfd::LBSolverNativeDispatcher::setGradients(const double* gradients, const int gradients_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setGradients(gradients,gradients_len);
}

void cca::cfd::LBSolverNativeDispatcher::setGradientsParallel(const double* gradients, const int gradients_len){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->setGradientsParallel(gradients,gradients_len);
}
void cca::cfd::LBSolverNativeDispatcher::closeLBProfiles(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->closeLBProfiles();
}

void cca::cfd::LBSolverNativeDispatcher::closeLBProfilesParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->closeLBProfilesParallel();
}
void cca::cfd::LBSolverNativeDispatcher::printLBDensity(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->printLBDensity();
}

void cca::cfd::LBSolverNativeDispatcher::printLBDensityParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->printLBDensityParallel();
}
void cca::cfd::LBSolverNativeDispatcher::printLBProfiles(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->printLBProfiles();
}

void cca::cfd::LBSolverNativeDispatcher::printLBProfilesParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->printLBProfilesParallel();
}
void cca::cfd::LBSolverNativeDispatcher::forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->forwardVelocities(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,componentSize,componentSize_len,ackn);
}

void cca::cfd::LBSolverNativeDispatcher::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->forwardVelocitiesParallel(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,componentSize,componentSize_len,ackn);
}
void cca::cfd::LBSolverNativeDispatcher::forwardPressure(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->forwardPressure(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
}

void cca::cfd::LBSolverNativeDispatcher::forwardPressureParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->forwardPressureParallel(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
}
void cca::cfd::LBSolverNativeDispatcher::syncr(int& value){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->syncr(value);
}

void cca::cfd::LBSolverNativeDispatcher::syncrParallel(int& value){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->syncrParallel(value);
}
void cca::cfd::LBSolverNativeDispatcher::plot(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->plot();
}

void cca::cfd::LBSolverNativeDispatcher::plotParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->plotParallel();
}

