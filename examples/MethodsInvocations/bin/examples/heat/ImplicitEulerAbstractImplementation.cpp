#include "examples/heat/ImplicitEulerAbstractImplementation.h"

examples::heat::ImplicitEulerAbstractImplementation::ImplicitEulerAbstractImplementation(){
     _solver = 0;

}

examples::heat::ImplicitEulerAbstractImplementation::~ImplicitEulerAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void examples::heat::ImplicitEulerAbstractImplementation::connectsolver(examples::heat::SolverNativeDispatcher* port){
   _solver = port; 
 }
 
 void examples::heat::ImplicitEulerAbstractImplementation::disconnectsolver(){
    //delete _solver;
    _solver=NULL;
 }
 
