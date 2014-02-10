#ifndef EXAMPLES_HEAT_REGULARGRIDCXX2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_REGULARGRIDCXX2SOCKETPLAINPORT_H_ 

#include "examples/heat/RegularGrid.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace examples { 
namespace heat { 
  
     class RegularGridCxx2SocketPlainPort;
} 
}

class examples::heat::RegularGridCxx2SocketPlainPort: public examples::heat::RegularGrid{
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
    RegularGridCxx2SocketPlainPort(char* host,int port,int buffer_size);
     RegularGridCxx2SocketPlainPort(int port,int buffer_size);
    ~RegularGridCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void setOffset(const double* offset, const int offset_len);
    void setDomain(const double* domain, const int domain_len);
    void setDimensions(const int* dimensions, const int dimensions_len);
    void addCellScalars(const std::string variableName,const double* scalars, const int scalars_len);
    void render();
};

#endif
