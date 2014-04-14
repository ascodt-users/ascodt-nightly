#ifndef EXAMPLES_FOOCXX2SOCKETPLAINPORT_H_
#define EXAMPLES_FOOCXX2SOCKETPLAINPORT_H_ 

#include "examples/Foo.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace examples { 

     class FooCxx2SocketPlainPort;
}

class examples::FooCxx2SocketPlainPort: public examples::Foo{
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
    FooCxx2SocketPlainPort(char* host,int port,int buffer_size);
     FooCxx2SocketPlainPort(int port,int buffer_size);
    ~FooCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void bar(const int a,const int b);  
    void barParallel(const int a,const int b);
   
};

#endif
