#ifndef EXAMPLES_HEAT_IMPLICITEULERIMPLEMENTATION_H_
#define EXAMPLES_HEAT_IMPLICITEULERIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include "examples/heat/ImplicitEulerAbstractImplementation.h"
#include <string>
namespace examples { 
namespace heat { 
  
     class ImplicitEulerImplementation;
} 
}

class examples::heat::ImplicitEulerImplementation : public examples::heat::ImplicitEulerAbstractImplementation{
private:
	double _stencil[5];
	public:
          ImplicitEulerImplementation();
          ~ImplicitEulerImplementation();
          void step(const int* dims,const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,const void* dof);
};     


#endif
