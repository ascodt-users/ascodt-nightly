
#include <iostream>
#include <string.h>
#include "cca/cfd/LBSolverC2CxxSocketPlainPort.h"
#include "cca/cfd/LBSolverCxx2SocketPlainPort.h"
#include "cca/cfd/LBSolver.h"
extern "C" {

#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_lbsolverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::LBSolverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void cca_cfd_lbsolverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::LBSolverCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void cca_cfd_lbsolverc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     cca::cfd::LBSolverCxx2SocketPlainPort* c_ptr = (cca::cfd::LBSolverCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETUP(long long* ref,char* inputScenario){
     std::string inputScenario_str(inputScenario);

     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setup(inputScenario_str);
}
#else
void cca_cfd_lbsolverc2socket_plain_port_setup_(long long* ref,char* inputScenario){
     std::string inputScenario_str(inputScenario);

     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setup(inputScenario_str);
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETUPCOMMFORNSREGION(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len){
     std::string* commids_str=new std::string[*commids_len];
for(int i=0;i<*commids_len;i++)
commids_str[i]=commids[i];

     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setupCommForNSRegion(startOfRegion,*startOfRegion_len,endOfRegion,*endOfRegion_len,commids_str,*commids_len);
}
#else
void cca_cfd_lbsolverc2socket_plain_port_setupcommfornsregion_(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len){
     std::string* commids_str=new std::string[*commids_len];
for(int i=0;i<*commids_len;i++)
commids_str[i]=commids[i];

     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setupCommForNSRegion(startOfRegion,*startOfRegion_len,endOfRegion,*endOfRegion_len,commids_str,*commids_len);
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SOLVE(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->solve();
}
#else
void cca_cfd_lbsolverc2socket_plain_port_solve_(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->solve();
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SOLVEONETIMESTEP(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->solveOneTimestep();
}
#else
void cca_cfd_lbsolverc2socket_plain_port_solveonetimestep_(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->solveOneTimestep();
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETVELOCITIES(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setVelocities(velocitiesX,*velocitiesX_len,velocitiesY,*velocitiesY_len,velocitiesZ,*velocitiesZ_len);
}
#else
void cca_cfd_lbsolverc2socket_plain_port_setvelocities_(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setVelocities(velocitiesX,*velocitiesX_len,velocitiesY,*velocitiesY_len,velocitiesZ,*velocitiesZ_len);
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETPRESSURE(long long* ref,double* pressure, int* pressure_len){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setPressure(pressure,*pressure_len);
}
#else
void cca_cfd_lbsolverc2socket_plain_port_setpressure_(long long* ref,double* pressure, int* pressure_len){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setPressure(pressure,*pressure_len);
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETGRADIENTS(long long* ref,double* gradients, int* gradients_len){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setGradients(gradients,*gradients_len);
}
#else
void cca_cfd_lbsolverc2socket_plain_port_setgradients_(long long* ref,double* gradients, int* gradients_len){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->setGradients(gradients,*gradients_len);
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_CLOSELBPROFILES(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->closeLBProfiles();
}
#else
void cca_cfd_lbsolverc2socket_plain_port_closelbprofiles_(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->closeLBProfiles();
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_PRINTLBDENSITY(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->printLBDensity();
}
#else
void cca_cfd_lbsolverc2socket_plain_port_printlbdensity_(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->printLBDensity();
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_PRINTLBPROFILES(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->printLBProfiles();
}
#else
void cca_cfd_lbsolverc2socket_plain_port_printlbprofiles_(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->printLBProfiles();
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_FORWARDVELOCITIES(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->forwardVelocities(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#else
void cca_cfd_lbsolverc2socket_plain_port_forwardvelocities_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->forwardVelocities(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_FORWARDPRESSURE(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->forwardPressure(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#else
void cca_cfd_lbsolverc2socket_plain_port_forwardpressure_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->forwardPressure(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SYNCR(long long* ref,int* value){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->syncr(*value);
}
#else
void cca_cfd_lbsolverc2socket_plain_port_syncr_(long long* ref,int* value){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->syncr(*value);
}
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_PLOT(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->plot();
}
#else
void cca_cfd_lbsolverc2socket_plain_port_plot_(long long* ref){
     
     ((cca::cfd::LBSolverCxx2SocketPlainPort*)*ref)->plot();
}
#endif
}
