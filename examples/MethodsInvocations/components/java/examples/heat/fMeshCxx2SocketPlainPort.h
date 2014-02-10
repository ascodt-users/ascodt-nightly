#ifndef EXAMPLES_HEAT_FMESHCXX2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_FMESHCXX2SOCKETPLAINPORT_H_ 

#include "examples/heat/fMesh.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace examples { 
namespace heat { 
  
     class fMeshCxx2SocketPlainPort;
} 
}

class examples::heat::fMeshCxx2SocketPlainPort: public examples::heat::fMesh{
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
    fMeshCxx2SocketPlainPort(char* host,int port,int buffer_size);
     fMeshCxx2SocketPlainPort(int port,int buffer_size);
    ~fMeshCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void allocate(const int* dim, const int dim_len);
    void copyData(double* data, const int data_len);
    void getData(void*& handle);
};

#endif
