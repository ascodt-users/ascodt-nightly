#ifndef EXAMPLES_HEAT_MESH_H_
#define EXAMPLES_HEAT_MESH_H_ 

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
  
     class Mesh;
} 
}

class examples::heat::Mesh {
  public:
    virtual ~Mesh(){}
     virtual void getData(double* data, const int data_len)=0;
     virtual void allocate(const int* dim, const int dim_len)=0;


};

#endif