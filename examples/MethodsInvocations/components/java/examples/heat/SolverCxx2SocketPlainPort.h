#ifndef EXAMPLES_HEAT_SOLVERCXX2SOCKETPLAINPORT_H_
#define EXAMPLES_HEAT_SOLVERCXX2SOCKETPLAINPORT_H_ 

#include "examples/heat/Solver.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace examples { 
namespace heat { 
  
     class SolverCxx2SocketPlainPort;
} 
}

class examples::heat::SolverCxx2SocketPlainPort: public examples::heat::Solver{
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
    SolverCxx2SocketPlainPort(char* host,int port,int buffer_size);
     SolverCxx2SocketPlainPort(int port,int buffer_size);
    ~SolverCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void setup(const double precision,const int iterations);
    void solve(const int* dims, const int dims_len,const double* stencil, const int stencil_len,const double* rhs, const int rhs_len,const void* dof_handle);
};

#endif
