#include "examples/AAbstractImplementation.h"

examples::AAbstractImplementation::AAbstractImplementation(){
     _fooHandler = 0;

}

examples::AAbstractImplementation::~AAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void examples::AAbstractImplementation::connectfooHandler(examples::FooNativeDispatcher* port){
   _fooHandler = port; 
 }
 
 void examples::AAbstractImplementation::disconnectfooHandler(){
    //delete _fooHandler;
    _fooHandler=NULL;
 }
 
void examples::AAbstractImplementation::goParallel(){
     // @todo Insert your code here
}
