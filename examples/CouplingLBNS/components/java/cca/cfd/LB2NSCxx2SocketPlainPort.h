#ifndef CCA_CFD_LB2NSCXX2SOCKETPLAINPORT_H_
#define CCA_CFD_LB2NSCXX2SOCKETPLAINPORT_H_ 

#include "cca/cfd/LB2NS.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace cca { 
namespace cfd { 
  
     class LB2NSCxx2SocketPlainPort;
} 
}

class cca::cfd::LB2NSCxx2SocketPlainPort: public cca::cfd::LB2NS{
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
    LB2NSCxx2SocketPlainPort(char* host,int port,int buffer_size);
     LB2NSCxx2SocketPlainPort(int port,int buffer_size);
    ~LB2NSCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void iterateBoundary();  
    void iterateBoundaryParallel();
   
    void iterateInner();  
    void iterateInnerParallel();
   
    void retrieveTimestep(double& dt);  
    void retrieveTimestepParallel(double& dt);
   
    void retrieveVelocitiesSize(int& memoryX,int& memoryY,int& memoryZ);  
    void retrieveVelocitiesSizeParallel(int& memoryX,int& memoryY,int& memoryZ);
   
    void retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);  
    void retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);
   
};

#endif
