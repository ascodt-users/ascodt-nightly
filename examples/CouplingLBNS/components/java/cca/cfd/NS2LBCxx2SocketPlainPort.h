#ifndef CCA_CFD_NS2LBCXX2SOCKETPLAINPORT_H_
#define CCA_CFD_NS2LBCXX2SOCKETPLAINPORT_H_ 

#include "cca/cfd/NS2LB.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace cca { 
namespace cfd { 
  
     class NS2LBCxx2SocketPlainPort;
} 
}

class cca::cfd::NS2LBCxx2SocketPlainPort: public cca::cfd::NS2LB{
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
    NS2LBCxx2SocketPlainPort(char* host,int port,int buffer_size);
     NS2LBCxx2SocketPlainPort(int port,int buffer_size);
    ~NS2LBCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void iterate();  
    void iterateParallel();
   
    void retrieveTimestep(double& timestep);  
    void retrieveTimestepParallel(double& timestep);
   
    void retrieveVelocitiesSize(int& memory);  
    void retrieveVelocitiesSizeParallel(int& memory);
   
    void retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);  
    void retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len);
   
    void retrieveJacobianCopy(double* jacobian, const int jacobian_len);  
    void retrieveJacobianCopyParallel(double* jacobian, const int jacobian_len);
   
    void retrievePressureCopy(double* pressure, const int pressure_len);  
    void retrievePressureCopyParallel(double* pressure, const int pressure_len);
   
};

#endif
