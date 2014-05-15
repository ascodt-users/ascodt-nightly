
#include <iostream>
#include <string.h>
#include "cca/cfd/DriverC2CxxSocketPlainPort.h"
#include "cca/cfd/DriverCxx2SocketPlainPort.h"
#include "cca/cfd/Driver.h"
extern "C" {

#ifdef _WIN32
void CCA_CFD_DRIVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_driverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::DriverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_DRIVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void cca_cfd_driverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::DriverCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_DRIVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void cca_cfd_driverc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     cca::cfd::DriverCxx2SocketPlainPort* c_ptr = (cca::cfd::DriverCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void CCA_CFD_DRIVERC2SOCKET_PLAIN_PORT_GO(long long* ref,char* configFile){
     std::string configFile_str(configFile);

     ((cca::cfd::DriverCxx2SocketPlainPort*)*ref)->go(configFile_str);
}
#else
void cca_cfd_driverc2socket_plain_port_go_(long long* ref,char* configFile){
     std::string configFile_str(configFile);

     ((cca::cfd::DriverCxx2SocketPlainPort*)*ref)->go(configFile_str);
}
#endif
}
