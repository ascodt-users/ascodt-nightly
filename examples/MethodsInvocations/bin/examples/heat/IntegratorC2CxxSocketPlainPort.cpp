
#include <iostream>
#include <string.h>
#include "examples/heat/IntegratorC2CxxSocketPlainPort.h"
#include "examples/heat/IntegratorCxx2SocketPlainPort.h"
#include "examples/heat/Integrator.h"
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATORC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_integratorc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::IntegratorCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATORC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void examples_heat_integratorc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::IntegratorCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATORC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void examples_heat_integratorc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     examples::heat::IntegratorCxx2SocketPlainPort* c_ptr = (examples::heat::IntegratorCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATORC2SOCKET_PLAIN_PORT_STEP(long long* ref,int* dims,int* dims_len,double* dt,double* rhs, int* rhs_len,double* stencil, int* stencil_len,void* dof){
     
     ((examples::heat::IntegratorCxx2SocketPlainPort*)*ref)->step(dims,*dims_len,*dt,rhs,*rhs_len,stencil,*stencil_len,dof);
}
#else
void examples_heat_integratorc2socket_plain_port_step_(long long* ref,int* dims,int* dims_len,double* dt,double* rhs, int* rhs_len,double* stencil, int* stencil_len,void* dof){
     
     ((examples::heat::IntegratorCxx2SocketPlainPort*)*ref)->step(dims,*dims_len,*dt,rhs,*rhs_len,stencil,*stencil_len,dof);
}
#endif
}
