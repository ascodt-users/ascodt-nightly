
#include <iostream>
#include <string.h>
#include "cca/cfd/NSSolverC2CxxSocketPlainPort.h"
#include "cca/cfd/NSSolverCxx2SocketPlainPort.h"
#include "cca/cfd/NSSolver.h"
extern "C" {

#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void cca_cfd_nssolverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::NSSolverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void cca_cfd_nssolverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new cca::cfd::NSSolverCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void cca_cfd_nssolverc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     cca::cfd::NSSolverCxx2SocketPlainPort* c_ptr = (cca::cfd::NSSolverCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SETUP(long long* ref,char* inputScenario){
     std::string inputScenario_str(inputScenario);

     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->setup(inputScenario_str);
}
#else
void cca_cfd_nssolverc2socket_plain_port_setup_(long long* ref,char* inputScenario){
     std::string inputScenario_str(inputScenario);

     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->setup(inputScenario_str);
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SETUPCOMMFORLBREGION(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len){
     std::string* commids_str=new std::string[*commids_len];
for(int i=0;i<*commids_len;i++)
commids_str[i]=commids[i];

     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->setupCommForLBRegion(startOfRegion,*startOfRegion_len,endOfRegion,*endOfRegion_len,commids_str,*commids_len);
}
#else
void cca_cfd_nssolverc2socket_plain_port_setupcommforlbregion_(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len){
     std::string* commids_str=new std::string[*commids_len];
for(int i=0;i<*commids_len;i++)
commids_str[i]=commids[i];

     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->setupCommForLBRegion(startOfRegion,*startOfRegion_len,endOfRegion,*endOfRegion_len,commids_str,*commids_len);
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SOLVE(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->solve();
}
#else
void cca_cfd_nssolverc2socket_plain_port_solve_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->solve();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SOLVEONETIMESTEPPHASEONE(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->solveOneTimestepPhaseOne();
}
#else
void cca_cfd_nssolverc2socket_plain_port_solveonetimestepphaseone_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->solveOneTimestepPhaseOne();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SOLVEONETIMESTEPPHASETWO(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->solveOneTimestepPhaseTwo();
}
#else
void cca_cfd_nssolverc2socket_plain_port_solveonetimestepphasetwo_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->solveOneTimestepPhaseTwo();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SETVELOCITIES(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->setVelocities(velocitiesX,*velocitiesX_len,velocitiesY,*velocitiesY_len,velocitiesZ,*velocitiesZ_len);
}
#else
void cca_cfd_nssolverc2socket_plain_port_setvelocities_(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->setVelocities(velocitiesX,*velocitiesX_len,velocitiesY,*velocitiesY_len,velocitiesZ,*velocitiesZ_len);
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_PRINTNSPRESSURE(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->printNSPressure();
}
#else
void cca_cfd_nssolverc2socket_plain_port_printnspressure_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->printNSPressure();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_PRINTNSPROFILES(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->printNSProfiles();
}
#else
void cca_cfd_nssolverc2socket_plain_port_printnsprofiles_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->printNSProfiles();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_CLOSENSPROFILES(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->closeNSProfiles();
}
#else
void cca_cfd_nssolverc2socket_plain_port_closensprofiles_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->closeNSProfiles();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_ITERATEBOUNDARY(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->iterateBoundary();
}
#else
void cca_cfd_nssolverc2socket_plain_port_iterateboundary_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->iterateBoundary();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_ITERATEINNER(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->iterateInner();
}
#else
void cca_cfd_nssolverc2socket_plain_port_iterateinner_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->iterateInner();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_FORWARDVELOCITIES(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->forwardVelocities(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#else
void cca_cfd_nssolverc2socket_plain_port_forwardvelocities_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->forwardVelocities(keys,*keys_len,offsets,*offsets_len,flips,*flips_len,values,*values_len,*ackn);
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_PLOT(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->plot();
}
#else
void cca_cfd_nssolverc2socket_plain_port_plot_(long long* ref){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->plot();
}
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SYNCR(long long* ref,int* value){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->syncr(*value);
}
#else
void cca_cfd_nssolverc2socket_plain_port_syncr_(long long* ref,int* value){
     
     ((cca::cfd::NSSolverCxx2SocketPlainPort*)*ref)->syncr(*value);
}
#endif
}
