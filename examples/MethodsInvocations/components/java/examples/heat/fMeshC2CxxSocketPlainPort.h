#ifndef EXAMPLES_HEAT_FMESHC2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_FMESHC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void EXAMPLES_HEAT_FMESHC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void EXAMPLES_HEAT_FMESHC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void EXAMPLES_HEAT_FMESHC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void examples_heat_fmeshc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void examples_heat_fmeshc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void examples_heat_fmeshc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_FMESHC2SOCKET_PLAIN_PORT_ALLOCATE(long long* ref,int* dim,int* dim_len);

#else
void examples_heat_fmeshc2socket_plain_port_allocate_(long long* ref,int* dim,int* dim_len);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_FMESHC2SOCKET_PLAIN_PORT_COPYDATA(long long* ref,double* data, int* data_len);

#else
void examples_heat_fmeshc2socket_plain_port_copydata_(long long* ref,double* data, int* data_len);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_FMESHC2SOCKET_PLAIN_PORT_GETDATA(long long* ref,void*& handle);

#else
void examples_heat_fmeshc2socket_plain_port_getdata_(long long* ref,void*& handle);
#endif
}
#endif
