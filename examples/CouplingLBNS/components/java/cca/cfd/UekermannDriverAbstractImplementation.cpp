#include "cca/cfd/UekermannDriverAbstractImplementation.h"

cca::cfd::UekermannDriverAbstractImplementation::UekermannDriverAbstractImplementation(){
     _lb = 0;
_lb2ns = 0;
_ns2lb = 0;
_ns = 0;

}

cca::cfd::UekermannDriverAbstractImplementation::~UekermannDriverAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void cca::cfd::UekermannDriverAbstractImplementation::connectns(cca::cfd::NSSolverNativeDispatcher* port){
   _ns = port; 
 }
 
 void cca::cfd::UekermannDriverAbstractImplementation::disconnectns(){
    //delete _ns;
    _ns=NULL;
 }
 
/**
 * @see Case class 
 */
 void cca::cfd::UekermannDriverAbstractImplementation::connectns2lb(cca::cfd::NS2LBNativeDispatcher* port){
   _ns2lb = port; 
 }
 
 void cca::cfd::UekermannDriverAbstractImplementation::disconnectns2lb(){
    //delete _ns2lb;
    _ns2lb=NULL;
 }
 
/**
 * @see Case class 
 */
 void cca::cfd::UekermannDriverAbstractImplementation::connectlb2ns(cca::cfd::LB2NSNativeDispatcher* port){
   _lb2ns = port; 
 }
 
 void cca::cfd::UekermannDriverAbstractImplementation::disconnectlb2ns(){
    //delete _lb2ns;
    _lb2ns=NULL;
 }
 
/**
 * @see Case class 
 */
 void cca::cfd::UekermannDriverAbstractImplementation::connectlb(cca::cfd::LBSolverNativeDispatcher* port){
   _lb = port; 
 }
 
 void cca::cfd::UekermannDriverAbstractImplementation::disconnectlb(){
    //delete _lb;
    _lb=NULL;
 }
 
void cca::cfd::UekermannDriverAbstractImplementation::goParallel(const std::string configFile){
     // @todo Insert your code here
}
