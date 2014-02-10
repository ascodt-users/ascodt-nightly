#include "examples/heat/AdamsMoultonAbstractImplementation.h"

examples::heat::AdamsMoultonAbstractImplementation::AdamsMoultonAbstractImplementation(){
     _solver = 0;

}

examples::heat::AdamsMoultonAbstractImplementation::~AdamsMoultonAbstractImplementation(){

}

/**
 * @see Case class 
 */
 void examples::heat::AdamsMoultonAbstractImplementation::connectsolver(examples::heat::SolverNativeDispatcher* port){
   _solver = port; 
 }
 
 void examples::heat::AdamsMoultonAbstractImplementation::disconnectsolver(){
    //delete _solver;
    _solver=NULL;
 }
 
