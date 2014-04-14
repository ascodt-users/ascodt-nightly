
#include <iostream>
#include <string.h>
#include "examples/FooC2CxxSocketPlainPort.h"
#include "examples/FooCxx2SocketPlainPort.h"
#include "examples/Foo.h"
extern "C" {

#ifdef _WIN32
void EXAMPLES_FOOC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_fooc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::FooCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_FOOC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void examples_fooc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::FooCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_FOOC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void examples_fooc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     examples::FooCxx2SocketPlainPort* c_ptr = (examples::FooCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void EXAMPLES_FOOC2SOCKET_PLAIN_PORT_BAR(long long* ref,int* a,int* b){
     
     ((examples::FooCxx2SocketPlainPort*)*ref)->bar(*a,*b);
}
#else
void examples_fooc2socket_plain_port_bar_(long long* ref,int* a,int* b){
     
     ((examples::FooCxx2SocketPlainPort*)*ref)->bar(*a,*b);
}
#endif
}
