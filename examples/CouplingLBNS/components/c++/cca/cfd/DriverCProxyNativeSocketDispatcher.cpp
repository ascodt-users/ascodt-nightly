
#include "cca/cfd/DriverNativeSocketDispatcher.h"
#include "cca/cfd/Driver.h"
#include <stdio.h>
#include <string.h>

extern "C" {

#ifdef _WIN32
void CCA_CFD_DRIVER_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_driver_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new cca::cfd::DriverNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void CCA_CFD_DRIVER_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void cca_cfd_driver_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     cca::cfd::DriverNativeSocketDispatcher* dispatcher =
               ((cca::cfd::DriverNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void CCA_CFD_DRIVER_F2C_NSD_GO(long long* ref,char* configFile){
#else
void cca_cfd_driver_f2c_nsd_go_(long long* ref,char* configFile){
#endif
    
     std::string configFile_str(configFile);

     ((cca::cfd::DriverNativeSocketDispatcher*)*ref)->go(configFile_str);
}


}
