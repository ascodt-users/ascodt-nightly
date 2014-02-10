#include "de/tum/DriverComponentAbstractImplementation.h"

de::tum::DriverComponentAbstractImplementation::DriverComponentAbstractImplementation(){
     _uPort = 0;

}

de::tum::DriverComponentAbstractImplementation::~DriverComponentAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void de::tum::DriverComponentAbstractImplementation::connectuPort(de::tum::FooBarNativeDispatcher* port){
   _uPort = port; 
 }
 
 void de::tum::DriverComponentAbstractImplementation::disconnectuPort(){
    //delete _uPort;
    _uPort=NULL;
 }
 
