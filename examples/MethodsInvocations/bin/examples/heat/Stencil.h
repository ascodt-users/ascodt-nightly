#ifndef EXAMPLES_HEAT_STENCIL_H_
#define EXAMPLES_HEAT_STENCIL_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include <iostream>
#include <string>



namespace examples { 
namespace heat { 
  
     class Stencil;
} 
}

class examples::heat::Stencil {
  public:
    virtual ~Stencil(){}
     virtual void getStencil(double* stencil, const int stencil_len)=0;


};

#endif