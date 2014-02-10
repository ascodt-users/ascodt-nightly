
#include <iostream>
#include <string.h>
#include "examples/heat/MeshC2CxxSocketPlainPort.h"
#include "examples/heat/MeshCxx2SocketPlainPort.h"
#include "examples/heat/Mesh.h"
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_meshc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::MeshCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void examples_heat_meshc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::MeshCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void examples_heat_meshc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     examples::heat::MeshCxx2SocketPlainPort* c_ptr = (examples::heat::MeshCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_ALLOCATE(long long* ref,int* dim,int* dim_len){
     
     ((examples::heat::MeshCxx2SocketPlainPort*)*ref)->allocate(dim,*dim_len);
}
#else
void examples_heat_meshc2socket_plain_port_allocate_(long long* ref,int* dim,int* dim_len){
     
     ((examples::heat::MeshCxx2SocketPlainPort*)*ref)->allocate(dim,*dim_len);
}
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_GETDATA(long long* ref,double* data, int* data_len){
     
     ((examples::heat::MeshCxx2SocketPlainPort*)*ref)->getData(data,*data_len);
}
#else
void examples_heat_meshc2socket_plain_port_getdata_(long long* ref,double* data, int* data_len){
     
     ((examples::heat::MeshCxx2SocketPlainPort*)*ref)->getData(data,*data_len);
}
#endif
}
