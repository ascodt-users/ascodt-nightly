#ifndef EXAMPLES_HEAT_SOLVERC2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_SOLVERC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void examples_heat_solverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void examples_heat_solverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void examples_heat_solverc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_SETUP(long long* ref,double* precision,int* iterations);

#else
void examples_heat_solverc2socket_plain_port_setup_(long long* ref,double* precision,int* iterations);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_SOLVE(long long* ref,int* dims,int* dims_len,double* stencil, int* stencil_len,double* rhs, int* rhs_len,void* dof_handle);

#else
void examples_heat_solverc2socket_plain_port_solve_(long long* ref,int* dims,int* dims_len,double* stencil, int* stencil_len,double* rhs, int* rhs_len,void* dof_handle);
#endif
}
#endif
