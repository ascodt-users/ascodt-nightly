#ifndef CCA_CFD_UEKERMANNDRIVERIMPLEMENTATION_H_
#define CCA_CFD_UEKERMANNDRIVERIMPLEMENTATION_H_ 

//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
#include <mpi.h>
#include "cca/cfd/UekermannDriverAbstractImplementation.h"
#include <string>
#include <vector>
namespace cca { 
namespace cfd { 

class UekermannDriverImplementation;
} 
}

class cca::cfd::UekermannDriverImplementation : public cca::cfd::UekermannDriverAbstractImplementation{
private:
	std::vector<double>  _lbVelocityX;
	std::vector<double>  _lbVelocityY;
	std::vector<double>  _lbVelocityZ;
	std::vector<double>  _nsVelocityX;
	std::vector<double>  _nsVelocityY;
	std::vector<double>  _nsVelocityZ;
	std::vector<double>  _nsPressure;
	std::vector<double>  _nsJacobian;
	void exchangeBoundaries();
public:
	UekermannDriverImplementation();
	~UekermannDriverImplementation();
	void go(const std::string configFile);
};     


#endif
