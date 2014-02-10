
#include <iostream>
#include <string.h>
#include "de/tum/FooBarC2CxxSocketPlainPort.h"
#include "de/tum/FooBarCxx2SocketPlainPort.h"
#include "de/tum/FooBar.h"
extern "C" {

#ifdef _WIN32
void DE_TUM_FOOBARC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void de_tum_foobarc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new de::tum::FooBarCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void DE_TUM_FOOBARC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void de_tum_foobarc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new de::tum::FooBarCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void DE_TUM_FOOBARC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void de_tum_foobarc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     de::tum::FooBarCxx2SocketPlainPort* c_ptr = (de::tum::FooBarCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void DE_TUM_FOOBARC2SOCKET_PLAIN_PORT_FOO(long long* ref,double* data, int* data_len){
     
     ((de::tum::FooBarCxx2SocketPlainPort*)*ref)->foo(data,*data_len);
}
#else
void de_tum_foobarc2socket_plain_port_foo_(long long* ref,double* data, int* data_len){
     
     ((de::tum::FooBarCxx2SocketPlainPort*)*ref)->foo(data,*data_len);
}
#endif
#ifdef _WIN32
void DE_TUM_FOOBARC2SOCKET_PLAIN_PORT_BAR(long long* ref,double* data, int* data_len){
     
     ((de::tum::FooBarCxx2SocketPlainPort*)*ref)->bar(data,*data_len);
}
#else
void de_tum_foobarc2socket_plain_port_bar_(long long* ref,double* data, int* data_len){
     
     ((de::tum::FooBarCxx2SocketPlainPort*)*ref)->bar(data,*data_len);
}
#endif
#ifdef _WIN32
void DE_TUM_FOOBARC2SOCKET_PLAIN_PORT_RESET(long long* ref){
     
     ((de::tum::FooBarCxx2SocketPlainPort*)*ref)->reset();
}
#else
void de_tum_foobarc2socket_plain_port_reset_(long long* ref){
     
     ((de::tum::FooBarCxx2SocketPlainPort*)*ref)->reset();
}
#endif
}
