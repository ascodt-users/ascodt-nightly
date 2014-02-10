
#include "examples/heat/fMeshNativeSocketDispatcher.h"
#include "examples/heat/fMesh.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_FMESH_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_fmesh_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new examples::heat::fMeshNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void EXAMPLES_HEAT_FMESH_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void examples_heat_fmesh_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     examples::heat::fMeshNativeSocketDispatcher* dispatcher =
               ((examples::heat::fMeshNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_FMESH_F2C_NSD_ALLOCATE(long long* ref,int* dim,int* dim_len){
#else
void examples_heat_fmesh_f2c_nsd_allocate_(long long* ref,int* dim,int* dim_len){
#endif
    
     
     ((examples::heat::fMeshNativeSocketDispatcher*)*ref)->allocate(dim,*dim_len);
}
#ifdef _WIN32
void EXAMPLES_HEAT_FMESH_F2C_NSD_COPYDATA(long long* ref,double* data, int* data_len){
#else
void examples_heat_fmesh_f2c_nsd_copydata_(long long* ref,double* data, int* data_len){
#endif
    
     
     ((examples::heat::fMeshNativeSocketDispatcher*)*ref)->copyData(data,*data_len);
}
#ifdef _WIN32
void EXAMPLES_HEAT_FMESH_F2C_NSD_GETDATA(long long* ref,void*& handle){
#else
void examples_heat_fmesh_f2c_nsd_getdata_(long long* ref,void*& handle){
#endif
    
     
     ((examples::heat::fMeshNativeSocketDispatcher*)*ref)->getData(handle);
}


}
