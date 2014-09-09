#ifndef CCA_CFD_NSSOLVERC2SOCKETPLAINPORT_H_
#define CCA_CFD_NSSOLVERC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>


extern "C" {
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void cca_cfd_nssolverc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void cca_cfd_nssolverc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void cca_cfd_nssolverc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SETUP(long long* ref,char* inputScenario);

#else
void cca_cfd_nssolverc2socket_plain_port_setup_(long long* ref,char* inputScenario);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SETUPCOMMFORLBREGION(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len);

#else
void cca_cfd_nssolverc2socket_plain_port_setupcommforlbregion_(long long* ref,int* startOfRegion,int* startOfRegion_len,int* endOfRegion,int* endOfRegion_len,char** commids,int* commids_len);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SOLVE(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_solve_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SOLVEONETIMESTEPPHASEONE(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_solveonetimestepphaseone_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SOLVEONETIMESTEPPHASETWO(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_solveonetimestepphasetwo_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SETVELOCITIES(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len);

#else
void cca_cfd_nssolverc2socket_plain_port_setvelocities_(long long* ref,double* velocitiesX, int* velocitiesX_len,double* velocitiesY, int* velocitiesY_len,double* velocitiesZ, int* velocitiesZ_len);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_PRINTNSPRESSURE(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_printnspressure_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_PRINTNSPROFILES(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_printnsprofiles_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_CLOSENSPROFILES(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_closensprofiles_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_ITERATEBOUNDARY(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_iterateboundary_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_ITERATEINNER(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_iterateinner_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_FORWARDVELOCITIES(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn);

#else
void cca_cfd_nssolverc2socket_plain_port_forwardvelocities_(long long* ref,int* keys,int* keys_len,int* offsets,int* offsets_len,int* flips,int* flips_len,double* values, int* values_len,int* ackn);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_PLOT(long long* ref);

#else
void cca_cfd_nssolverc2socket_plain_port_plot_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NSSOLVERC2SOCKET_PLAIN_PORT_SYNCR(long long* ref,int* value);

#else
void cca_cfd_nssolverc2socket_plain_port_syncr_(long long* ref,int* value);

#endif
}
#endif
