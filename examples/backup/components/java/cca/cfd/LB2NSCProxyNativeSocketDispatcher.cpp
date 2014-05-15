
#include "cca/cfd/LB2NSNativeSocketDispatcher.h"
#include "cca/cfd/LB2NS.h"
#include <stdio.h>
#include <string.h>

extern "C" {

#ifdef _WIN32
void CCA_CFD_LB2NS_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_lb2ns_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new cca::cfd::LB2NSNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void CCA_CFD_LB2NS_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void cca_cfd_lb2ns_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     cca::cfd::LB2NSNativeSocketDispatcher* dispatcher =
               ((cca::cfd::LB2NSNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void CCA_CFD_LB2NS_F2C_NSD_ITERATEBOUNDARY(long long* ref){
#else
void cca_cfd_lb2ns_f2c_nsd_iterateboundary_(long long* ref){
#endif
    
     
     ((cca::cfd::LB2NSNativeSocketDispatcher*)*ref)->iterateBoundary();
}
#ifdef _WIN32
void CCA_CFD_LB2NS_F2C_NSD_ITERATEINNER(long long* ref){
#else
void cca_cfd_lb2ns_f2c_nsd_iterateinner_(long long* ref){
#endif
    
     
     ((cca::cfd::LB2NSNativeSocketDispatcher*)*ref)->iterateInner();
}
#ifdef _WIN32
void CCA_CFD_LB2NS_F2C_NSD_RETRIEVETIMESTEP(long long* ref,double* dt){
#else
void cca_cfd_lb2ns_f2c_nsd_retrievetimestep_(long long* ref,double* dt){
#endif
    
     
     ((cca::cfd::LB2NSNativeSocketDispatcher*)*ref)->retrieveTimestep(*dt);
}
#ifdef _WIN32
void CCA_CFD_LB2NS_F2C_NSD_RETRIEVEVELOCITIESSIZE(long long* ref,int* memoryX,int* memoryY,int* memoryZ){
#else
void cca_cfd_lb2ns_f2c_nsd_retrievevelocitiessize_(long long* ref,int* memoryX,int* memoryY,int* memoryZ){
#endif
    
     
     ((cca::cfd::LB2NSNativeSocketDispatcher*)*ref)->retrieveVelocitiesSize(*memoryX,*memoryY,*memoryZ);
}
#ifdef _WIN32
void CCA_CFD_LB2NS_F2C_NSD_RETRIEVEVELOCITIESCOPY(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len){
#else
void cca_cfd_lb2ns_f2c_nsd_retrievevelocitiescopy_(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len){
#endif
    
     
     ((cca::cfd::LB2NSNativeSocketDispatcher*)*ref)->retrieveVelocitiesCopy(velocityX,*velocityX_len,velocityY,*velocityY_len,velocityZ,*velocityZ_len);
}


}
