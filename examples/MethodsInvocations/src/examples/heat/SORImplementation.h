#ifndef EXAMPLES_HEAT_SORIMPLEMENTATION_H_
#define EXAMPLES_HEAT_SORIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include "examples/heat/SORAbstractImplementation.h"
#include <string>
namespace examples { 
namespace heat { 
  
     class SORImplementation;
} 
}

class examples::heat::SORImplementation : public examples::heat::SORAbstractImplementation{
private:
	double _precision;
	int _iterations;
public:
          SORImplementation();
          ~SORImplementation();
          void setup(const double precision,const int iterations);
          void solve(const int* dims, const int dims_len,const double* stencil, const int stencil_len,const double* rhs, const int rhs_len,const void* dof_handle);
};     


#endif