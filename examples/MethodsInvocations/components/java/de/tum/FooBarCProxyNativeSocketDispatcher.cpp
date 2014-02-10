
#include "de/tum/FooBarNativeSocketDispatcher.h"
#include "de/tum/FooBar.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void DE_TUM_FOOBAR_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void de_tum_foobar_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new de::tum::FooBarNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void DE_TUM_FOOBAR_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void de_tum_foobar_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     de::tum::FooBarNativeSocketDispatcher* dispatcher =
               ((de::tum::FooBarNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void DE_TUM_FOOBAR_F2C_NSD_FOO(long long* ref,double* data, int* data_len){
#else
void de_tum_foobar_f2c_nsd_foo_(long long* ref,double* data, int* data_len){
#endif
    
     
     ((de::tum::FooBarNativeSocketDispatcher*)*ref)->foo(data,*data_len);
}
#ifdef _WIN32
void DE_TUM_FOOBAR_F2C_NSD_BAR(long long* ref,double* data, int* data_len){
#else
void de_tum_foobar_f2c_nsd_bar_(long long* ref,double* data, int* data_len){
#endif
    
     
     ((de::tum::FooBarNativeSocketDispatcher*)*ref)->bar(data,*data_len);
}
#ifdef _WIN32
void DE_TUM_FOOBAR_F2C_NSD_RESET(long long* ref){
#else
void de_tum_foobar_f2c_nsd_reset_(long long* ref){
#endif
    
     
     ((de::tum::FooBarNativeSocketDispatcher*)*ref)->reset();
}


}
