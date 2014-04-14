#ifndef EXAMPLES_DRIVERCXX2SOCKETPLAINPORT_H_
#define EXAMPLES_DRIVERCXX2SOCKETPLAINPORT_H_ 

#include "examples/Driver.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace examples { 

     class DriverCxx2SocketPlainPort;
}

class examples::DriverCxx2SocketPlainPort: public examples::Driver{
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
    DriverCxx2SocketPlainPort(char* host,int port,int buffer_size);
     DriverCxx2SocketPlainPort(int port,int buffer_size);
    ~DriverCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void go();  
    void goParallel();
   
};

#endif
