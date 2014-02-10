#ifndef EXAMPLES_HEAT_STENCILCXX2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_STENCILCXX2SOCKETPLAINPORT_H_ 

#include "examples/heat/Stencil.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace examples { 
namespace heat { 
  
     class StencilCxx2SocketPlainPort;
} 
}

class examples::heat::StencilCxx2SocketPlainPort: public examples::heat::Stencil{
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
    StencilCxx2SocketPlainPort(char* host,int port,int buffer_size);
     StencilCxx2SocketPlainPort(int port,int buffer_size);
    ~StencilCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void getStencil(double* stencil, const int stencil_len);
};

#endif
