#ifndef EXAMPLES_HEAT_INTEGRATORCXX2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_INTEGRATORCXX2SOCKETPLAINPORT_H_ 

#include "examples/heat/Integrator.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace examples { 
namespace heat { 
  
     class IntegratorCxx2SocketPlainPort;
} 
}

class examples::heat::IntegratorCxx2SocketPlainPort: public examples::heat::Integrator{
  private:
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    _sockfd;
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif
    _newsockfd;
    int _buffer_size;
    char *_rcvBuffer;
    char *_sendBuffer;
    void open_client(char* hostname,int port,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    &sockfd,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    &newsockfd);
    //void open_server(int port,int &sockfd,int &newsockfd);
    void sendData(char* data, size_t numberOfBytes, char* sendBuffer,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    newsockfd,int bufferSize);
    void readData(char* data,size_t size_of_data,char* readBuffer,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    newsockfd, int bufferSize);
    void close(
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    &sockfd,
    #ifdef _WIN32
    SOCKET
    #else
    int
    #endif 
    &newsockfd);
  public:
    IntegratorCxx2SocketPlainPort(char* host,int port,int buffer_size);
     IntegratorCxx2SocketPlainPort(int port,int buffer_size);
    ~IntegratorCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void step(const int* dims, const int dims_len,const double dt,const double* rhs, const int rhs_len,const double* stencil, const int stencil_len,const void* dof);
};

#endif
