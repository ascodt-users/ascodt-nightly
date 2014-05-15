#include "cca/cfd/NSAbstractImplementation.h"

cca::cfd::NSAbstractImplementation::NSAbstractImplementation(){
     _lb = 0;

}

cca::cfd::NSAbstractImplementation::~NSAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void cca::cfd::NSAbstractImplementation::connectlb(cca::cfd::LBSolverNativeDispatcher* port){
   _lb = port; 
 }
 
 void cca::cfd::NSAbstractImplementation::disconnectlb(){
    //delete _lb;
    _lb=NULL;
 }
 
void cca::cfd::NSAbstractImplementation::retrievePressureCopyParallel(double* pressure, const int pressure_len){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::retrieveJacobianCopyParallel(double* jacobian, const int jacobian_len){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::retrieveVelocitiesSizeParallel(int& memory){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::retrieveTimestepParallel(double& timestep){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::iterateParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::syncrParallel(int& value){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::plotParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::iterateInnerParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::iterateBoundaryParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::closeNSProfilesParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::printNSProfilesParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::printNSPressureParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::solveOneTimestepPhaseTwoParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::solveOneTimestepPhaseOneParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::solveParallel(){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::setupCommForLBRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     // @todo Insert your code here
}
void cca::cfd::NSAbstractImplementation::setupParallel(const std::string inputScenario){
     // @todo Insert your code here
}
