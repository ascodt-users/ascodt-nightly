#ifndef CCA_CFD_LBSOLVERC2SOCKETPLAINPORT_H_
#define CCA_CFD_LBSOLVERC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>


extern "C" {
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void cca_cfd_lbsolverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void cca_cfd_lbsolverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void cca_cfd_lbsolverc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETUP(long long* ref,char* inputScenario);

#else
void cca_cfd_lbsolverc2socket_plain_port_setup_(long long* ref,char* inputScenario);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETUPCOMMFORNSREGION(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len);

#else
void cca_cfd_lbsolverc2socket_plain_port_setupcommfornsregion_(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SOLVE(long long* ref);

#else
void cca_cfd_lbsolverc2socket_plain_port_solve_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SOLVEONETIMESTEP(long long* ref);

#else
void cca_cfd_lbsolverc2socket_plain_port_solveonetimestep_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETVELOCITIES(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len);

#else
void cca_cfd_lbsolverc2socket_plain_port_setvelocities_(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETPRESSURE(long long* ref,double* pressure, int* pressure_len);

#else
void cca_cfd_lbsolverc2socket_plain_port_setpressure_(long long* ref,double* pressure, int* pressure_len);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SETGRADIENTS(long long* ref,double* gradients, int* gradients_len);

#else
void cca_cfd_lbsolverc2socket_plain_port_setgradients_(long long* ref,double* gradients, int* gradients_len);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_CLOSELBPROFILES(long long* ref);

#else
void cca_cfd_lbsolverc2socket_plain_port_closelbprofiles_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_PRINTLBDENSITY(long long* ref);

#else
void cca_cfd_lbsolverc2socket_plain_port_printlbdensity_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_PRINTLBPROFILES(long long* ref);

#else
void cca_cfd_lbsolverc2socket_plain_port_printlbprofiles_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_FORWARDVELOCITIES(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* componentSize,int* componentSize_len,int* ackn);

#else
void cca_cfd_lbsolverc2socket_plain_port_forwardvelocities_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* componentSize,int* componentSize_len,int* ackn);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_FORWARDPRESSURE(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn);

#else
void cca_cfd_lbsolverc2socket_plain_port_forwardpressure_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_SYNCR(long long* ref,int* value);

#else
void cca_cfd_lbsolverc2socket_plain_port_syncr_(long long* ref,int* value);

#endif
#ifdef _WIN32
void CCA_CFD_LBSOLVERC2SOCKET_PLAIN_PORT_PLOT(long long* ref);

#else
void cca_cfd_lbsolverc2socket_plain_port_plot_(long long* ref);

#endif
}
#endif
