
#include "examples/heat/IntegratorNativeSocketDispatcher.h"
#include "examples/heat/Integrator.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATOR_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_integrator_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new examples::heat::IntegratorNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATOR_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void examples_heat_integrator_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     examples::heat::IntegratorNativeSocketDispatcher* dispatcher =
               ((examples::heat::IntegratorNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_INTEGRATOR_F2C_NSD_STEP(long long* ref,int* dims,int* dims_len,double* dt,double* rhs, int* rhs_len,double* stencil, int* stencil_len,void* dof){
#else
void examples_heat_integrator_f2c_nsd_step_(long long* ref,int* dims,int* dims_len,double* dt,double* rhs, int* rhs_len,double* stencil, int* stencil_len,void* dof){
#endif
    
     
     ((examples::heat::IntegratorNativeSocketDispatcher*)*ref)->step(dims,*dims_len,*dt,rhs,*rhs_len,stencil,*stencil_len,dof);
}


}
