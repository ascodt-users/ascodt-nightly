
#include "examples/heat/StencilNativeSocketDispatcher.h"
#include "examples/heat/Stencil.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_STENCIL_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_stencil_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new examples::heat::StencilNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void EXAMPLES_HEAT_STENCIL_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void examples_heat_stencil_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     examples::heat::StencilNativeSocketDispatcher* dispatcher =
               ((examples::heat::StencilNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_STENCIL_F2C_NSD_GETSTENCIL(long long* ref,double* stencil, int* stencil_len){
#else
void examples_heat_stencil_f2c_nsd_getstencil_(long long* ref,double* stencil, int* stencil_len){
#endif
    
     
     ((examples::heat::StencilNativeSocketDispatcher*)*ref)->getStencil(stencil,*stencil_len);
}


}
