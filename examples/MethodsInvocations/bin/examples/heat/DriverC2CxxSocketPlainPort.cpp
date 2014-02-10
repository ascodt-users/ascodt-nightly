
#include <iostream>
#include <string.h>
#include "examples/heat/DriverC2CxxSocketPlainPort.h"
#include "examples/heat/DriverCxx2SocketPlainPort.h"
#include "examples/heat/Driver.h"
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_DRIVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_driverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::DriverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_DRIVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void examples_heat_driverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::DriverCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_DRIVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void examples_heat_driverc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     examples::heat::DriverCxx2SocketPlainPort* c_ptr = (examples::heat::DriverCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void EXAMPLES_HEAT_DRIVERC2SOCKET_PLAIN_PORT_GO(long long* ref){
     
     ((examples::heat::DriverCxx2SocketPlainPort*)*ref)->go();
}
#else
void examples_heat_driverc2socket_plain_port_go_(long long* ref){
     
     ((examples::heat::DriverCxx2SocketPlainPort*)*ref)->go();
}
#endif
}
