
#include "cca/cfd/LBSolverNativeSocketDispatcher.h"
#include "cca/cfd/LBSolver.h"
#include <stdio.h>
#include <string.h>

extern "C" {

#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_lbsolver_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new cca::cfd::LBSolverNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void cca_cfd_lbsolver_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     cca::cfd::LBSolverNativeSocketDispatcher* dispatcher =
               ((cca::cfd::LBSolverNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_SETUP(long long* ref,char* inputScenario){
#else
void cca_cfd_lbsolver_f2c_nsd_setup_(long long* ref,char* inputScenario){
#endif
    
     std::string inputScenario_str(inputScenario);

     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->setup(inputScenario_str);
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_SETUPCOMMFORNSREGION(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len){
#else
void cca_cfd_lbsolver_f2c_nsd_setupcommfornsregion_(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len){
#endif
    
     std::string* commids_str=new std::string[*commids_len];
for(int i=0;i<*commids_len;i++)
commids_str[i]=commids[i];

     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->setupCommForNSRegion(startOfRegion,*startOfRegion_len,endOfRegion,*endOfRegion_len,commids_str,*commids_len);
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_SOLVE(long long* ref){
#else
void cca_cfd_lbsolver_f2c_nsd_solve_(long long* ref){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->solve();
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_SOLVEONETIMESTEP(long long* ref){
#else
void cca_cfd_lbsolver_f2c_nsd_solveonetimestep_(long long* ref){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->solveOneTimestep();
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_SETVELOCITIES(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len){
#else
void cca_cfd_lbsolver_f2c_nsd_setvelocities_(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->setVelocities(velocitiesX,*velocitiesX_len,velocitiesY,*velocitiesY_len,velocitiesZ,*velocitiesZ_len);
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_SETPRESSURE(long long* ref,double* pressure, int* pressure_len){
#else
void cca_cfd_lbsolver_f2c_nsd_setpressure_(long long* ref,double* pressure, int* pressure_len){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->setPressure(pressure,*pressure_len);
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_SETGRADIENTS(long long* ref,double* gradients, int* gradients_len){
#else
void cca_cfd_lbsolver_f2c_nsd_setgradients_(long long* ref,double* gradients, int* gradients_len){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->setGradients(gradients,*gradients_len);
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_CLOSELBPROFILES(long long* ref){
#else
void cca_cfd_lbsolver_f2c_nsd_closelbprofiles_(long long* ref){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->closeLBProfiles();
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_PRINTLBDENSITY(long long* ref){
#else
void cca_cfd_lbsolver_f2c_nsd_printlbdensity_(long long* ref){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->printLBDensity();
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_PRINTLBPROFILES(long long* ref){
#else
void cca_cfd_lbsolver_f2c_nsd_printlbprofiles_(long long* ref){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->printLBProfiles();
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_FORWARDVELOCITIES(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
#else
void cca_cfd_lbsolver_f2c_nsd_forwardvelocities_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->forwardVelocities(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_FORWARDPRESSURE(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
#else
void cca_cfd_lbsolver_f2c_nsd_forwardpressure_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->forwardPressure(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_SYNCR(long long* ref,int* value){
#else
void cca_cfd_lbsolver_f2c_nsd_syncr_(long long* ref,int* value){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->syncr(*value);
}
#ifdef _WIN32
void CCA_CFD_LBSOLVER_F2C_NSD_PLOT(long long* ref){
#else
void cca_cfd_lbsolver_f2c_nsd_plot_(long long* ref){
#endif
    
     
     ((cca::cfd::LBSolverNativeSocketDispatcher*)*ref)->plot();
}


}
