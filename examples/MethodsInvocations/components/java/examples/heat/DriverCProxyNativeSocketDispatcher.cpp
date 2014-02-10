
#include "examples/heat/DriverNativeSocketDispatcher.h"
#include "examples/heat/Driver.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_DRIVER_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_driver_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new examples::heat::DriverNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void EXAMPLES_HEAT_DRIVER_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void examples_heat_driver_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     examples::heat::DriverNativeSocketDispatcher* dispatcher =
               ((examples::heat::DriverNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_DRIVER_F2C_NSD_GO(long long* ref){
#else
void examples_heat_driver_f2c_nsd_go_(long long* ref){
#endif
    
     
     ((examples::heat::DriverNativeSocketDispatcher*)*ref)->go();
}


}
