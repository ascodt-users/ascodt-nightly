#ifndef EXAMPLES_HEAT_INTEGRATORC2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_INTEGRATORC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATORC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void EXAMPLES_HEAT_INTEGRATORC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void EXAMPLES_HEAT_INTEGRATORC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void examples_heat_integratorc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void examples_heat_integratorc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void examples_heat_integratorc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATORC2SOCKET_PLAIN_PORT_STEP(long long* ref,int* dims,int* dims_len,double* dt,double* rhs, int* rhs_len,double* stencil, int* stencil_len,void* dof);

#else
void examples_heat_integratorc2socket_plain_port_step_(long long* ref,int* dims,int* dims_len,double* dt,double* rhs, int* rhs_len,double* stencil, int* stencil_len,void* dof);
#endif
}
#endif
