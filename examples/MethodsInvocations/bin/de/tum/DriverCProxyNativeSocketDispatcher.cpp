
#include "de/tum/DriverNativeSocketDispatcher.h"
#include "de/tum/Driver.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void DE_TUM_DRIVER_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void de_tum_driver_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new de::tum::DriverNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void DE_TUM_DRIVER_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void de_tum_driver_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     de::tum::DriverNativeSocketDispatcher* dispatcher =
               ((de::tum::DriverNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void DE_TUM_DRIVER_F2C_NSD_GO(long long* ref){
#else
void de_tum_driver_f2c_nsd_go_(long long* ref){
#endif
    
     
     ((de::tum::DriverNativeSocketDispatcher*)*ref)->go();
}


}
