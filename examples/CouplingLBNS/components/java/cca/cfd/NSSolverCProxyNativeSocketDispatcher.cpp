
#include "cca/cfd/NSSolverNativeSocketDispatcher.h"
#include "cca/cfd/NSSolver.h"
#include <stdio.h>
#include <string.h>

extern "C" {

#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_nssolver_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new cca::cfd::NSSolverNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void cca_cfd_nssolver_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     cca::cfd::NSSolverNativeSocketDispatcher* dispatcher =
               ((cca::cfd::NSSolverNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_SETUP(long long* ref,char* inputScenario){
#else
void cca_cfd_nssolver_f2c_nsd_setup_(long long* ref,char* inputScenario){
#endif
    
     std::string inputScenario_str(inputScenario);

     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->setup(inputScenario_str);
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_SETUPCOMMFORLBREGION(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len){
#else
void cca_cfd_nssolver_f2c_nsd_setupcommforlbregion_(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len){
#endif
    
     std::string* commids_str=new std::string[*commids_len];
for(int i=0;i<*commids_len;i++)
commids_str[i]=commids[i];

     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->setupCommForLBRegion(startOfRegion,*startOfRegion_len,endOfRegion,*endOfRegion_len,commids_str,*commids_len);
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_SOLVE(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_solve_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->solve();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_SOLVEONETIMESTEPPHASEONE(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_solveonetimestepphaseone_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->solveOneTimestepPhaseOne();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_SOLVEONETIMESTEPPHASETWO(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_solveonetimestepphasetwo_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->solveOneTimestepPhaseTwo();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_SETVELOCITIES(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len){
#else
void cca_cfd_nssolver_f2c_nsd_setvelocities_(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->setVelocities(velocitiesX,*velocitiesX_len,velocitiesY,*velocitiesY_len,velocitiesZ,*velocitiesZ_len);
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_PRINTNSPRESSURE(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_printnspressure_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->printNSPressure();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_PRINTNSPROFILES(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_printnsprofiles_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->printNSProfiles();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_CLOSENSPROFILES(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_closensprofiles_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->closeNSProfiles();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_ITERATEBOUNDARY(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_iterateboundary_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->iterateBoundary();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_ITERATEINNER(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_iterateinner_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->iterateInner();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_FORWARDVELOCITIES(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
#else
void cca_cfd_nssolver_f2c_nsd_forwardvelocities_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->forwardVelocities(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_PLOT(long long* ref){
#else
void cca_cfd_nssolver_f2c_nsd_plot_(long long* ref){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->plot();
}
#ifdef _WIN32
void CCA_CFD_NSSOLVER_F2C_NSD_SYNCR(long long* ref,int* value){
#else
void cca_cfd_nssolver_f2c_nsd_syncr_(long long* ref,int* value){
#endif
    
     
     ((cca::cfd::NSSolverNativeSocketDispatcher*)*ref)->syncr(*value);
}


}
