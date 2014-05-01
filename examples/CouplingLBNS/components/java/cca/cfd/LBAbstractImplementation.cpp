#include "cca/cfd/LBAbstractImplementation.h"

cca::cfd::LBAbstractImplementation::LBAbstractImplementation(){
     _ns = 0;

}

cca::cfd::LBAbstractImplementation::~LBAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void cca::cfd::LBAbstractImplementation::connectns(cca::cfd::NSSolverNativeDispatcher* port){
   _ns = port; 
 }
 
 void cca::cfd::LBAbstractImplementation::disconnectns(){
    //delete _ns;
    _ns=NULL;
 }
 
void cca::cfd::LBAbstractImplementation::retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::retrieveVelocitiesSizeParallel(int& memoryX,int& memoryY,int& memoryZ){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::retrieveTimestepParallel(double& dt){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::iterateInnerParallel(){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::iterateBoundaryParallel(){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::plotParallel(){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::syncrParallel(int& value){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::forwardPressureParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::printLBProfilesParallel(){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::printLBDensityParallel(){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::closeLBProfilesParallel(){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::setGradientsParallel(const double* gradients, const int gradients_len){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::setPressureParallel(const double* pressure, const int pressure_len){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::solveOneTimestepParallel(){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::solveParallel(){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::setupCommForNSRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     // @todo Insert your code here
}
void cca::cfd::LBAbstractImplementation::setupParallel(const std::string inputScenario){
     // @todo Insert your code here
}
