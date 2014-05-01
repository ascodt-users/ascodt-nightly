#ifndef CCA_CFD_NS2LBC2SOCKETPLAINPORT_H_
#define CCA_CFD_NS2LBC2SOCKETPLAINPORT_H_ 

#include <map>
#include <string>


extern "C" {
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size);
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size);
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long* ptr);
#else
void cca_cfd_ns2lbc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size);
void cca_cfd_ns2lbc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size);
void cca_cfd_ns2lbc2socket_plain_port_destroy_instance_(long long* ptr);
#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_ITERATE(long long* ref);

#else
void cca_cfd_ns2lbc2socket_plain_port_iterate_(long long* ref);

#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVETIMESTEP(long long* ref,double* timestep);

#else
void cca_cfd_ns2lbc2socket_plain_port_retrievetimestep_(long long* ref,double* timestep);

#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVEVELOCITIESSIZE(long long* ref,int* memory);

#else
void cca_cfd_ns2lbc2socket_plain_port_retrievevelocitiessize_(long long* ref,int* memory);

#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVEVELOCITIESCOPY(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len);

#else
void cca_cfd_ns2lbc2socket_plain_port_retrievevelocitiescopy_(long long* ref,double* velocityX, int* velocityX_len,double* velocityY, int* velocityY_len,double* velocityZ, int* velocityZ_len);

#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVEJACOBIANCOPY(long long* ref,double* jacobian, int* jacobian_len);

#else
void cca_cfd_ns2lbc2socket_plain_port_retrievejacobiancopy_(long long* ref,double* jacobian, int* jacobian_len);

#endif
#ifdef _WIN32
void CCA_CFD_NS2LBC2SOCKET_PLAIN_PORT_RETRIEVEPRESSURECOPY(long long* ref,double* pressure, int* pressure_len);

#else
void cca_cfd_ns2lbc2socket_plain_port_retrievepressurecopy_(long long* ref,double* pressure, int* pressure_len);

#endif
}
#endif
