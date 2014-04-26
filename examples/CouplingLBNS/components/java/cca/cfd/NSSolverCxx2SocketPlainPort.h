#ifndef CCA_CFD_NSSOLVERCXX2SOCKETPLAINPORT_H_
#define CCA_CFD_NSSOLVERCXX2SOCKETPLAINPORT_H_ 

#include "cca/cfd/NSSolver.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace cca { 
namespace cfd { 
  
     class NSSolverCxx2SocketPlainPort;
} 
}

class cca::cfd::NSSolverCxx2SocketPlainPort: public cca::cfd::NSSolver{
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
    NSSolverCxx2SocketPlainPort(char* host,int port,int buffer_size);
     NSSolverCxx2SocketPlainPort(int port,int buffer_size);
    ~NSSolverCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void setup(const std::string inputScenario);  
    void setupParallel(const std::string inputScenario);
   
    void setupCommForLBRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len);  
    void setupCommForLBRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len);
   
    void solve();  
    void solveParallel();
   
    void solveOneTimestepPhaseOne();  
    void solveOneTimestepPhaseOneParallel();
   
    void solveOneTimestepPhaseTwo();  
    void solveOneTimestepPhaseTwoParallel();
   
    void setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);  
    void setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);
   
    void printNSPressure();  
    void printNSPressureParallel();
   
    void printNSProfiles();  
    void printNSProfilesParallel();
   
    void closeNSProfiles();  
    void closeNSProfilesParallel();
   
    void iterateBoundary();  
    void iterateBoundaryParallel();
   
    void iterateInner();  
    void iterateInnerParallel();
   
    void forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn);  
    void forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn);
   
    void plot();  
    void plotParallel();
   
    void syncr(int& value);  
    void syncrParallel(int& value);
   
};

#endif
