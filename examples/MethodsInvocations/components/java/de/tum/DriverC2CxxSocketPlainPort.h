#ifndef DE_TUM_DRIVERC2SOCKETPLAINPORT_H_
#define DE_TUM_DRIVERC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>

extern "C" {
#ifdef _WIN32
void DE_TUM_DRIVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void DE_TUM_DRIVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void DE_TUM_DRIVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void de_tum_driverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void de_tum_driverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void de_tum_driverc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void DE_TUM_DRIVERC2SOCKET_PLAIN_PORT_GO(long long* ref);

#else
void de_tum_driverc2socket_plain_port_go_(long long* ref);
#endif
}
#endif
