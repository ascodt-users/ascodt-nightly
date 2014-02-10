
#include "examples/heat/RegularGridNativeSocketDispatcher.h"
#include "examples/heat/RegularGrid.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRID_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_regulargrid_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new examples::heat::RegularGridNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRID_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void examples_heat_regulargrid_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     examples::heat::RegularGridNativeSocketDispatcher* dispatcher =
               ((examples::heat::RegularGridNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRID_F2C_NSD_SETOFFSET(long long* ref,double* offset, int* offset_len){
#else
void examples_heat_regulargrid_f2c_nsd_setoffset_(long long* ref,double* offset, int* offset_len){
#endif
    
     
     ((examples::heat::RegularGridNativeSocketDispatcher*)*ref)->setOffset(offset,*offset_len);
}
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRID_F2C_NSD_SETDOMAIN(long long* ref,double* domain, int* domain_len){
#else
void examples_heat_regulargrid_f2c_nsd_setdomain_(long long* ref,double* domain, int* domain_len){
#endif
    
     
     ((examples::heat::RegularGridNativeSocketDispatcher*)*ref)->setDomain(domain,*domain_len);
}
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRID_F2C_NSD_SETDIMENSIONS(long long* ref,int* dimensions,int* dimensions_len){
#else
void examples_heat_regulargrid_f2c_nsd_setdimensions_(long long* ref,int* dimensions,int* dimensions_len){
#endif
    
     
     ((examples::heat::RegularGridNativeSocketDispatcher*)*ref)->setDimensions(dimensions,*dimensions_len);
}
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRID_F2C_NSD_ADDCELLSCALARS(long long* ref,char* variableName,double* scalars, int* scalars_len){
#else
void examples_heat_regulargrid_f2c_nsd_addcellscalars_(long long* ref,char* variableName,double* scalars, int* scalars_len){
#endif
    
     std::string variableName_str(variableName);

     ((examples::heat::RegularGridNativeSocketDispatcher*)*ref)->addCellScalars(variableName_str,scalars,*scalars_len);
}
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRID_F2C_NSD_RENDER(long long* ref){
#else
void examples_heat_regulargrid_f2c_nsd_render_(long long* ref){
#endif
    
     
     ((examples::heat::RegularGridNativeSocketDispatcher*)*ref)->render();
}


}
