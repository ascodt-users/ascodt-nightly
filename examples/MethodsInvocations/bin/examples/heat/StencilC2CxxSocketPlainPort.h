#ifndef EXAMPLES_HEAT_STENCILC2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_STENCILC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void EXAMPLES_HEAT_STENCILC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void EXAMPLES_HEAT_STENCILC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void EXAMPLES_HEAT_STENCILC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void examples_heat_stencilc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void examples_heat_stencilc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void examples_heat_stencilc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_STENCILC2SOCKET_PLAIN_PORT_GETSTENCIL(long long* ref,double* stencil, int* stencil_len);

#else
void examples_heat_stencilc2socket_plain_port_getstencil_(long long* ref,double* stencil, int* stencil_len);
#endif
}
#endif
