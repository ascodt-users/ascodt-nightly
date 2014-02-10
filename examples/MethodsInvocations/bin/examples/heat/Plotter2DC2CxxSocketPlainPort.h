#ifndef EXAMPLES_HEAT_PLOTTER2DC2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_PLOTTER2DC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2DC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void EXAMPLES_HEAT_PLOTTER2DC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void EXAMPLES_HEAT_PLOTTER2DC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void examples_heat_plotter2dc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void examples_heat_plotter2dc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void examples_heat_plotter2dc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2DC2SOCKET_PLAIN_PORT_PLOTPOINT(long long* ref,char* name,double* x,double* y);

#else
void examples_heat_plotter2dc2socket_plain_port_plotpoint_(long long* ref,char* name,double* x,double* y);
#endif
}
#endif
