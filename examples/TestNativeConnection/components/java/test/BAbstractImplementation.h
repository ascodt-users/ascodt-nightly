#ifndef TEST_BABSTRACTIMPLEMENTATION_H_
#define TEST_BABSTRACTIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//

#include "test/Foo.h"

#include "Component.h"
namespace test { 

     class BAbstractImplementation;
}



class test::BAbstractImplementation: public Component ,public test::Foo{
     protected:
          
     public:
       BAbstractImplementation();
       virtual ~BAbstractImplementation();
};     


#endif
