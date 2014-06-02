
#include <iostream>
#include <string.h>
#include "cca/cfd/NS2LBC2CxxSocketPlainPort.h"
#include "cca/cfd/NS2LBCxx2SocketPlainPort.h"
#include "cca/cfd/NS2LB.h"
extern "C" {

#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_ns2lbc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::NS2LBCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void cca_cfd_ns2lbc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::NS2LBCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void cca_cfd_ns2lbc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     cca::cfd::NS2LBCxx2SocketPlainPort* c_ptr = (cca::cfd::NS2LBCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_ITERATE(long long* ref){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->iterate();
}
#else
void cca_cfd_ns2lbc2socket_plain_port_iterate_(long long* ref){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->iterate();
}
#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVETIMESTEP(long long* ref,double* timestep){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrieveTimestep(*timestep);
}
#else
void cca_cfd_ns2lbc2socket_plain_port_retrievetimestep_(long long* ref,double* timestep){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrieveTimestep(*timestep);
}
#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVEVELOCITIESSIZE(long long* ref,int* memory){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrieveVelocitiesSize(*memory);
}
#else
void cca_cfd_ns2lbc2socket_plain_port_retrievevelocitiessize_(long long* ref,int* memory){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrieveVelocitiesSize(*memory);
}
#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVEVELOCITIESCOPY(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrieveVelocitiesCopy(velocityX,*velocityX_len,velocityY,*velocityY_len,velocityZ,*velocityZ_len);
}
#else
void cca_cfd_ns2lbc2socket_plain_port_retrievevelocitiescopy_(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrieveVelocitiesCopy(velocityX,*velocityX_len,velocityY,*velocityY_len,velocityZ,*velocityZ_len);
}
#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVEJACOBIANCOPY(long long* ref,double* jacobian, int* jacobian_len){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrieveJacobianCopy(jacobian,*jacobian_len);
}
#else
void cca_cfd_ns2lbc2socket_plain_port_retrievejacobiancopy_(long long* ref,double* jacobian, int* jacobian_len){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrieveJacobianCopy(jacobian,*jacobian_len);
}
#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVEPRESSURECOPY(long long* ref,double* pressure, int* pressure_len){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrievePressureCopy(pressure,*pressure_len);
}
#else
void cca_cfd_ns2lbc2socket_plain_port_retrievepressurecopy_(long long* ref,double* pressure, int* pressure_len){
     
     ((cca::cfd::NS2LBCxx2SocketPlainPort*)*ref)->retrievePressureCopy(pressure,*pressure_len);
}
#endif
}
