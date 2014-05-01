
#include "cca/cfd/NS2LBNativeSocketDispatcher.h"
#include "cca/cfd/NS2LB.h"
#include <stdio.h>
#include <string.h>

extern "C" {

#ifdef _WIN32
void CCA_CFD_NS2LB_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_ns2lb_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new cca::cfd::NS2LBNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void CCA_CFD_NS2LB_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void cca_cfd_ns2lb_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     cca::cfd::NS2LBNativeSocketDispatcher* dispatcher =
               ((cca::cfd::NS2LBNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void CCA_CFD_NS2LB_F2C_NSD_ITERATE(long long* ref){
#else
void cca_cfd_ns2lb_f2c_nsd_iterate_(long long* ref){
#endif
    
     
     ((cca::cfd::NS2LBNativeSocketDispatcher*)*ref)->iterate();
}
#ifdef _WIN32
void CCA_CFD_NS2LB_F2C_NSD_RETRIEVETIMESTEP(long long* ref,double* timestep){
#else
void cca_cfd_ns2lb_f2c_nsd_retrievetimestep_(long long* ref,double* timestep){
#endif
    
     
     ((cca::cfd::NS2LBNativeSocketDispatcher*)*ref)->retrieveTimestep(*timestep);
}
#ifdef _WIN32
void CCA_CFD_NS2LB_F2C_NSD_RETRIEVEVELOCITIESSIZE(long long* ref,int* memory){
#else
void cca_cfd_ns2lb_f2c_nsd_retrievevelocitiessize_(long long* ref,int* memory){
#endif
    
     
     ((cca::cfd::NS2LBNativeSocketDispatcher*)*ref)->retrieveVelocitiesSize(*memory);
}
#ifdef _WIN32
void CCA_CFD_NS2LB_F2C_NSD_RETRIEVEVELOCITIESCOPY(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len){
#else
void cca_cfd_ns2lb_f2c_nsd_retrievevelocitiescopy_(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len){
#endif
    
     
     ((cca::cfd::NS2LBNativeSocketDispatcher*)*ref)->retrieveVelocitiesCopy(velocityX,*velocityX_len,velocityY,*velocityY_len,velocityZ,*velocityZ_len);
}
#ifdef _WIN32
void CCA_CFD_NS2LB_F2C_NSD_RETRIEVEJACOBIANCOPY(long long* ref,double* jacobian, int* jacobian_len){
#else
void cca_cfd_ns2lb_f2c_nsd_retrievejacobiancopy_(long long* ref,double* jacobian, int* jacobian_len){
#endif
    
     
     ((cca::cfd::NS2LBNativeSocketDispatcher*)*ref)->retrieveJacobianCopy(jacobian,*jacobian_len);
}
#ifdef _WIN32
void CCA_CFD_NS2LB_F2C_NSD_RETRIEVEPRESSURECOPY(long long* ref,double* pressure, int* pressure_len){
#else
void cca_cfd_ns2lb_f2c_nsd_retrievepressurecopy_(long long* ref,double* pressure, int* pressure_len){
#endif
    
     
     ((cca::cfd::NS2LBNativeSocketDispatcher*)*ref)->retrievePressureCopy(pressure,*pressure_len);
}


}
