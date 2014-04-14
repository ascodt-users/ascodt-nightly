#ifndef CCA_CFD_LBSOLVERCXX2SOCKETPLAINPORT_H_
#define CCA_CFD_LBSOLVERCXX2SOCKETPLAINPORT_H_ 

#include "cca/cfd/LBSolver.h"
#include <iostream>
#include <string>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace cca { 
namespace cfd { 
  
     class LBSolverCxx2SocketPlainPort;
} 
}

class cca::cfd::LBSolverCxx2SocketPlainPort: public cca::cfd::LBSolver{
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
    LBSolverCxx2SocketPlainPort(char* host,int port,int buffer_size);
     LBSolverCxx2SocketPlainPort(int port,int buffer_size);
    ~LBSolverCxx2SocketPlainPort();
    //int getSockfd();
    //int getNewsockfd();
    
    void setup(const std::string inputScenario);
	void setupParallel(const std::string inputScenario);
    void setupCommForNSRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len);
	void setupCommForNSRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len);
    void solve();
	void solveParallel();
    void solveOneTimestep();
	void solveOneTimestepParallel();
    void setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);
	void setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len);
    void setPressure(const double* pressure, const int pressure_len);
	void setPressureParallel(const double* pressure, const int pressure_len);
    void setGradients(const double* gradients, const int gradients_len);
	void setGradientsParallel(const double* gradients, const int gradients_len);
    void closeLBProfiles();
	void closeLBProfilesParallel();
    void printLBDensity();
	void printLBDensityParallel();
    void printLBProfiles();
	void printLBProfilesParallel();
    void forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn);
	void forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn);
    void forwardPressure(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);
	void forwardPressureParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn);
    void syncr(int& value);
	void syncrParallel(int& value);
    void plot();
	void plotParallel();
};

#endif
