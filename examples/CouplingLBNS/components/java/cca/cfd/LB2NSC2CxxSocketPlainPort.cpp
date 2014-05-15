
#include <iostream>
#include <string.h>
#include "cca/cfd/LB2NSC2CxxSocketPlainPort.h"
#include "cca/cfd/LB2NSCxx2SocketPlainPort.h"
#include "cca/cfd/LB2NS.h"
extern "C" {

#ifdef _WIN32
void CCA_CFD_LB2NSC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_lb2nsc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::LB2NSCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_LB2NSC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void cca_cfd_lb2nsc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::LB2NSCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_LB2NSC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void cca_cfd_lb2nsc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     cca::cfd::LB2NSCxx2SocketPlainPort* c_ptr = (cca::cfd::LB2NSCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void CCA_CFD_LB2NSC2SOCKET_PLAIN_PORT_ITERATEBOUNDARY(long long* ref){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->iterateBoundary();
}
#else
void cca_cfd_lb2nsc2socket_plain_port_iterateboundary_(long long* ref){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->iterateBoundary();
}
#endif
#ifdef _WIN32
void CCA_CFD_LB2NSC2SOCKET_PLAIN_PORT_ITERATEINNER(long long* ref){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->iterateInner();
}
#else
void cca_cfd_lb2nsc2socket_plain_port_iterateinner_(long long* ref){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->iterateInner();
}
#endif
#ifdef _WIN32
void CCA_CFD_LB2NSC2SOCKET_PLAIN_PORT_RETRIEVETIMESTEP(long long* ref,double* dt){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->retrieveTimestep(*dt);
}
#else
void cca_cfd_lb2nsc2socket_plain_port_retrievetimestep_(long long* ref,double* dt){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->retrieveTimestep(*dt);
}
#endif
#ifdef _WIN32
void CCA_CFD_LB2NSC2SOCKET_PLAIN_PORT_RETRIEVEVELOCITIESSIZE(long long* ref,int* memoryX,int* memoryY,int* memoryZ){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->retrieveVelocitiesSize(*memoryX,*memoryY,*memoryZ);
}
#else
void cca_cfd_lb2nsc2socket_plain_port_retrievevelocitiessize_(long long* ref,int* memoryX,int* memoryY,int* memoryZ){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->retrieveVelocitiesSize(*memoryX,*memoryY,*memoryZ);
}
#endif
#ifdef _WIN32
void CCA_CFD_LB2NSC2SOCKET_PLAIN_PORT_RETRIEVEVELOCITIESCOPY(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->retrieveVelocitiesCopy(velocityX,*velocityX_len,velocityY,*velocityY_len,velocityZ,*velocityZ_len);
}
#else
void cca_cfd_lb2nsc2socket_plain_port_retrievevelocitiescopy_(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len){
     
     ((cca::cfd::LB2NSCxx2SocketPlainPort*)*ref)->retrieveVelocitiesCopy(velocityX,*velocityX_len,velocityY,*velocityY_len,velocityZ,*velocityZ_len);
}
#endif
}
