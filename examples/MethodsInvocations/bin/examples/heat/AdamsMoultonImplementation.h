#ifndef EXAMPLES_HEAT_ADAMSMOULTONIMPLEMENTATION_H_
#define EXAMPLES_HEAT_ADAMSMOULTONIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include "examples/heat/AdamsMoultonAbstractImplementation.h"
#include <string>
namespace examples { 
namespace heat { 
  
     class AdamsMoultonImplementation;
} 
}

class examples::heat::AdamsMoultonImplementation : public examples::heat::AdamsMoultonAbstractImplementation{
     public:
          AdamsMoultonImplementation();
          ~AdamsMoultonImplementation();
          void step(const int* dims,const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,double* dof, const int dof_len);
};     


#endif