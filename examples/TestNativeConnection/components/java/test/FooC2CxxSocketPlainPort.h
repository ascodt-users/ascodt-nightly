#ifndef TEST_FOOC2SOCKETPLAINPORT_H_
#define TEST_FOOC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>


extern "C" {
#ifdef _WIN32
void TEST_FOOC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void TEST_FOOC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void TEST_FOOC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void test_fooc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void test_fooc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void test_fooc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void TEST_FOOC2SOCKET_PLAIN_PORT_BAR(long long* ref);

#else
void test_fooc2socket_plain_port_bar_(long long* ref);
#endif
}
#endif
