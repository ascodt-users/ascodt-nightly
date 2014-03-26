#include "test/AAbstractImplementation.h"

test::AAbstractImplementation::AAbstractImplementation(){
     _foo = 0;

}

test::AAbstractImplementation::~AAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void test::AAbstractImplementation::connectfoo(test::FooNativeDispatcher* port){
   _foo = port; 
 }
 
 void test::AAbstractImplementation::disconnectfoo(){
    //delete _foo;
    _foo=NULL;
 }
 
