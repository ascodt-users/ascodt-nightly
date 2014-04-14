
#include "examples/FooNativeSocketDispatcher.h"
#include "examples/Foo.h"
#include <stdio.h>
#include <string.h>

extern "C" {

#ifdef _WIN32
void EXAMPLES_FOO_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void examples_foo_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new examples::FooNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void EXAMPLES_FOO_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void examples_foo_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     examples::FooNativeSocketDispatcher* dispatcher =
               ((examples::FooNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void EXAMPLES_FOO_F2C_NSD_BAR(long long* ref,int* a,int* b){
#else
void examples_foo_f2c_nsd_bar_(long long* ref,int* a,int* b){
#endif
    
     
     ((examples::FooNativeSocketDispatcher*)*ref)->bar(*a,*b);
}


}
