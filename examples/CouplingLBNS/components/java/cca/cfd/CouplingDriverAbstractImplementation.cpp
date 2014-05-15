#include "cca/cfd/CouplingDriverAbstractImplementation.h"

cca::cfd::CouplingDriverAbstractImplementation::CouplingDriverAbstractImplementation(){
     _lb = 0;
_lb2ns = 0;
_ns2lb = 0;
_ns = 0;

}

cca::cfd::CouplingDriverAbstractImplementation::~CouplingDriverAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void cca::cfd::CouplingDriverAbstractImplementation::connectns(cca::cfd::NSSolverNativeDispatcher* port){
   _ns = port; 
 }
 
 void cca::cfd::CouplingDriverAbstractImplementation::disconnectns(){
    //delete _ns;
    _ns=NULL;
 }
 
/**
 * @see Case class 
 */
 void cca::cfd::CouplingDriverAbstractImplementation::connectns2lb(cca::cfd::NS2LBNativeDispatcher* port){
   _ns2lb = port; 
 }
 
 void cca::cfd::CouplingDriverAbstractImplementation::disconnectns2lb(){
    //delete _ns2lb;
    _ns2lb=NULL;
 }
 
/**
 * @see Case class 
 */
 void cca::cfd::CouplingDriverAbstractImplementation::connectlb2ns(cca::cfd::LB2NSNativeDispatcher* port){
   _lb2ns = port; 
 }
 
 void cca::cfd::CouplingDriverAbstractImplementation::disconnectlb2ns(){
    //delete _lb2ns;
    _lb2ns=NULL;
 }
 
/**
 * @see Case class 
 */
 void cca::cfd::CouplingDriverAbstractImplementation::connectlb(cca::cfd::LBSolverNativeDispatcher* port){
   _lb = port; 
 }
 
 void cca::cfd::CouplingDriverAbstractImplementation::disconnectlb(){
    //delete _lb;
    _lb=NULL;
 }
 
void cca::cfd::CouplingDriverAbstractImplementation::goParallel(const std::string configFile){
     // @todo Insert your code here
}
