
#include <iostream>
#include <string.h>
#include "examples/heat/RegularGridC2CxxSocketPlainPort.h"
#include "examples/heat/RegularGridCxx2SocketPlainPort.h"
#include "examples/heat/RegularGrid.h"
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_regulargridc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::RegularGridCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void examples_heat_regulargridc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::RegularGridCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void examples_heat_regulargridc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     examples::heat::RegularGridCxx2SocketPlainPort* c_ptr = (examples::heat::RegularGridCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_SETOFFSET(long long* ref,double* offset, int* offset_len){
     
     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->setOffset(offset,*offset_len);
}
#else
void examples_heat_regulargridc2socket_plain_port_setoffset_(long long* ref,double* offset, int* offset_len){
     
     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->setOffset(offset,*offset_len);
}
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_SETDOMAIN(long long* ref,double* domain, int* domain_len){
     
     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->setDomain(domain,*domain_len);
}
#else
void examples_heat_regulargridc2socket_plain_port_setdomain_(long long* ref,double* domain, int* domain_len){
     
     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->setDomain(domain,*domain_len);
}
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_SETDIMENSIONS(long long* ref,int* dimensions,int* dimensions_len){
     
     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->setDimensions(dimensions,*dimensions_len);
}
#else
void examples_heat_regulargridc2socket_plain_port_setdimensions_(long long* ref,int* dimensions,int* dimensions_len){
     
     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->setDimensions(dimensions,*dimensions_len);
}
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_ADDCELLSCALARS(long long* ref,char* variableName,double* scalars, int* scalars_len){
     std::string variableName_str(variableName);

     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->addCellScalars(variableName_str,scalars,*scalars_len);
}
#else
void examples_heat_regulargridc2socket_plain_port_addcellscalars_(long long* ref,char* variableName,double* scalars, int* scalars_len){
     std::string variableName_str(variableName);

     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->addCellScalars(variableName_str,scalars,*scalars_len);
}
#endif
#ifdef _WIN32
void EXAMPLES_HEAT_REGULARGRIDC2SOCKET_PLAIN_PORT_RENDER(long long* ref){
     
     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->render();
}
#else
void examples_heat_regulargridc2socket_plain_port_render_(long long* ref){
     
     ((examples::heat::RegularGridCxx2SocketPlainPort*)*ref)->render();
}
#endif
}
