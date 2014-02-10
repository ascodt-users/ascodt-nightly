#ifndef EXAMPLES_HEAT_MESHC2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_MESHC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void examples_heat_meshc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void examples_heat_meshc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void examples_heat_meshc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_ALLOCATE(long long* ref,int* dim,int* dim_len);

#else
void examples_heat_meshc2socket_plain_port_allocate_(long long* ref,int* dim,int* dim_len);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_MESHC2SOCKET_PLAIN_PORT_GETDATA(long long* ref,double* data, int* data_len);

#else
void examples_heat_meshc2socket_plain_port_getdata_(long long* ref,double* data, int* data_len);
#endif
}
#endif
