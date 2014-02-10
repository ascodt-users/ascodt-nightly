#ifndef EXAMPLES_HEAT_REGULARGRIDC2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_REGULARGRIDC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void examples_heat_regulargridc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void examples_heat_regulargridc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void examples_heat_regulargridc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_SETOFFSET(long long* ref,double* offset, int* offset_len);

#else
void examples_heat_regulargridc2socket_plain_port_setoffset_(long long* ref,double* offset, int* offset_len);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_SETDOMAIN(long long* ref,double* domain, int* domain_len);

#else
void examples_heat_regulargridc2socket_plain_port_setdomain_(long long* ref,double* domain, int* domain_len);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_SETDIMENSIONS(long long* ref,int* dimensions,int* dimensions_len);

#else
void examples_heat_regulargridc2socket_plain_port_setdimensions_(long long* ref,int* dimensions,int* dimensions_len);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_ADDCELLSCALARS(long long* ref,char* variableName,double* scalars, int* scalars_len);

#else
void examples_heat_regulargridc2socket_plain_port_addcellscalars_(long long* ref,char* variableName,double* scalars, int* scalars_len);
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_RENDER(long long* ref);

#else
void examples_heat_regulargridc2socket_plain_port_render_(long long* ref);
#endif
}
#endif
