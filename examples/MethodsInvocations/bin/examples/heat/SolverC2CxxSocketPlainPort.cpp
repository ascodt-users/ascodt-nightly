
#include <iostream>
#include <string.h>
#include "examples/heat/SolverC2CxxSocketPlainPort.h"
#include "examples/heat/SolverCxx2SocketPlainPort.h"
#include "examples/heat/Solver.h"
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_solverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::SolverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void examples_heat_solverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::SolverCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void examples_heat_solverc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     examples::heat::SolverCxx2SocketPlainPort* c_ptr = (examples::heat::SolverCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_SETUP(long long* ref,double* precision,int* iterations){
     
     ((examples::heat::SolverCxx2SocketPlainPort*)*ref)->setup(*precision,*iterations);
}
#else
void examples_heat_solverc2socket_plain_port_setup_(long long* ref,double* precision,int* iterations){
     
     ((examples::heat::SolverCxx2SocketPlainPort*)*ref)->setup(*precision,*iterations);
}
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_SOLVERC2SOCKET_PLAIN_PORT_SOLVE(long long* ref,int* dims,int* dims_len,double* stencil, int* stencil_len,double* rhs, int* rhs_len,void* dof_handle){
     
     ((examples::heat::SolverCxx2SocketPlainPort*)*ref)->solve(dims,*dims_len,stencil,*stencil_len,rhs,*rhs_len,dof_handle);
}
#else
void examples_heat_solverc2socket_plain_port_solve_(long long* ref,int* dims,int* dims_len,double* stencil, int* stencil_len,double* rhs, int* rhs_len,void* dof_handle){
     
     ((examples::heat::SolverCxx2SocketPlainPort*)*ref)->solve(dims,*dims_len,stencil,*stencil_len,rhs,*rhs_len,dof_handle);
}
#endif
}
