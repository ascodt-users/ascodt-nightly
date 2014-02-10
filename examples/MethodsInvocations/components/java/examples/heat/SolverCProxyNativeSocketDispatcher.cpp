
#include "examples/heat/SolverNativeSocketDispatcher.h"
#include "examples/heat/Solver.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_SOLVER_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_solver_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new examples::heat::SolverNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void EXAMPLES_HEAT_SOLVER_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void examples_heat_solver_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     examples::heat::SolverNativeSocketDispatcher* dispatcher =
               ((examples::heat::SolverNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_SOLVER_F2C_NSD_SETUP(long long* ref,double* precision,int* iterations){
#else
void examples_heat_solver_f2c_nsd_setup_(long long* ref,double* precision,int* iterations){
#endif
    
     
     ((examples::heat::SolverNativeSocketDispatcher*)*ref)->setup(*precision,*iterations);
}
#ifdef _WIN32
void EXAMPLES_HEAT_SOLVER_F2C_NSD_SOLVE(long long* ref,int* dims,int* dims_len,double* stencil, int* stencil_len,double* rhs, int* rhs_len,void* dof_handle){
#else
void examples_heat_solver_f2c_nsd_solve_(long long* ref,int* dims,int* dims_len,double* stencil, int* stencil_len,double* rhs, int* rhs_len,void* dof_handle){
#endif
    
     
     ((examples::heat::SolverNativeSocketDispatcher*)*ref)->solve(dims,*dims_len,stencil,*stencil_len,rhs,*rhs_len,dof_handle);
}


}
