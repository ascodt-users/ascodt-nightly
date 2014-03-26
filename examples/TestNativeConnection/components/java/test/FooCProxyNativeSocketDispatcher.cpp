
#include "test/FooNativeSocketDispatcher.h"
#include "test/Foo.h"
#include <stdio.h>
#include <string.h>

extern "C" {

#ifdef _WIN32
void TEST_FOO_F2C_NSD_CREATE_CLIENT_INSTANCE(long long* ptr,char* host,int& port,int& buffer_size){
#else
void test_foo_f2c_nsd_create_client_instance_(long long* ptr,char* host,int& port,int& buffer_size){
#endif     
     *ptr=(long long)new test::FooNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
     

}




#ifdef _WIN32
void TEST_FOO_F2C_NSD_DESTROY_INSTANCE(long long* ptr){

#else
void test_foo_f2c_nsd_destroy_instance_(long long* ptr){
#endif
     test::FooNativeSocketDispatcher* dispatcher =
               ((test::FooNativeSocketDispatcher*)*ptr);
     if(dispatcher!=NULL){
          delete dispatcher;
          dispatcher=NULL;
     }
     

}

#ifdef _WIN32
void TEST_FOO_F2C_NSD_BAR(long long* ref){
#else
void test_foo_f2c_nsd_bar_(long long* ref){
#endif
    
     
     ((test::FooNativeSocketDispatcher*)*ref)->bar();
}


}
