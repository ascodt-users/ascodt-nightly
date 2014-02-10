
#include <iostream>
#include <string.h>
#include "examples/heat/StencilC2CxxSocketPlainPort.h"
#include "examples/heat/StencilCxx2SocketPlainPort.h"
#include "examples/heat/Stencil.h"
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_STENCILC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_stencilc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::StencilCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_STENCILC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void examples_heat_stencilc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::StencilCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_STENCILC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void examples_heat_stencilc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     examples::heat::StencilCxx2SocketPlainPort* c_ptr = (examples::heat::StencilCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void EXAMPLES_HEAT_STENCILC2SOCKET_PLAIN_PORT_GETSTENCIL(long long* ref,double* stencil, int* stencil_len){
     
     ((examples::heat::StencilCxx2SocketPlainPort*)*ref)->getStencil(stencil,*stencil_len);
}
#else
void examples_heat_stencilc2socket_plain_port_getstencil_(long long* ref,double* stencil, int* stencil_len){
     
     ((examples::heat::StencilCxx2SocketPlainPort*)*ref)->getStencil(stencil,*stencil_len);
}
#endif
}
