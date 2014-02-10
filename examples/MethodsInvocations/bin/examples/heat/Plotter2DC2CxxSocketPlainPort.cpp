
#include <iostream>
#include <string.h>
#include "examples/heat/Plotter2DC2CxxSocketPlainPort.h"
#include "examples/heat/Plotter2DCxx2SocketPlainPort.h"
#include "examples/heat/Plotter2D.h"
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2DC2SOCKET_PLAIN_PORT_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_plotter2dc2socket_plain_port_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::Plotter2DCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2DC2SOCKET_PLAIN_PORT_CREATE_SERVER_INSTANCE(long long* ptr,int& port,int& buffer_size){
#else
void examples_heat_plotter2dc2socket_plain_port_create_server_instance_(long long* ptr,int& port,int& buffer_size){
#endif
   *ptr=(long long)new examples::heat::Plotter2DCxx2SocketPlainPort(
        port,
        buffer_size
   );
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2DC2SOCKET_PLAIN_PORT_DESTROY_INSTANCE(long long *ptr){
#else
void examples_heat_plotter2dc2socket_plain_port_destroy_instance_(long long *ptr){
#endif
     examples::heat::Plotter2DCxx2SocketPlainPort* c_ptr = (examples::heat::Plotter2DCxx2SocketPlainPort*)*ptr;
     if(c_ptr!=NULL){
         delete c_ptr;
         c_ptr = NULL;
     }
}




#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2DC2SOCKET_PLAIN_PORT_PLOTPOINT(long long* ref,char* name,double* x,double* y){
     std::string name_str(name);

     ((examples::heat::Plotter2DCxx2SocketPlainPort*)*ref)->plotPoint(name_str,*x,*y);
}
#else
void examples_heat_plotter2dc2socket_plain_port_plotpoint_(long long* ref,char* name,double* x,double* y){
     std::string name_str(name);

     ((examples::heat::Plotter2DCxx2SocketPlainPort*)*ref)->plotPoint(name_str,*x,*y);
}
#endif
}
