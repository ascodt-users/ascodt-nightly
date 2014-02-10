
#include "examples/heat/Plotter2DNativeSocketDispatcher.h"
#include "examples/heat/Plotter2D.h"
#include <stdio.h>
#include <string.h>
extern "C" {

#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2D_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_heat_plotter2d_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new examples::heat::Plotter2DNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2D_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void examples_heat_plotter2d_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     examples::heat::Plotter2DNativeSocketDispatcher* dispatcher =
               ((examples::heat::Plotter2DNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void EXAMPLES_HEAT_PLOTTER2D_F2C_NSD_PLOTPOINT(long long* ref,char* name,double* x,double* y){
#else
void examples_heat_plotter2d_f2c_nsd_plotpoint_(long long* ref,char* name,double* x,double* y){
#endif
    
     std::string name_str(name);

     ((examples::heat::Plotter2DNativeSocketDispatcher*)*ref)->plotPoint(name_str,*x,*y);
}


}
