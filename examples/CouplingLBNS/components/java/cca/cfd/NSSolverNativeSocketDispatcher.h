#ifndef CCA_CFD_NSSOLVERNATIVESOCKETDISPATCHER_H_
#define CCA_CFD_NSSOLVERNATIVESOCKETDISPATCHER_H_ 

#include "cca/cfd/NSSolverNativeDispatcher.h"
#include <iostream>
#include <vector>
#ifdef _WIN32
#include <winsock2.h>
#endif
namespace cca { 
namespace cfd { 
  
     class NSSolverNativeSocketDispatcher;
} 
}



#ifdef __cplusplus
  extern "C" {
#endif


          


#ifdef __cplusplus
  }
#endif


class cca::cfd::NSSolverNativeSocketDispatcher: public cca::cfd::NSSolverNativeDispatcher{
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
    
    void open(char* hostname,int port,
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
    //void open(int port,int &sockfd,int &newsockfd);
    void sendData(char* data, size_t numberOfBytes, char* sendBuffer,
    #ifdef _WIN32
    SOCKET
	#else
    int
	#endif 
    newsockfd,
    int bufferSize);
    void readData(char* data,size_t size_of_data,char* readBuffer,
    #ifdef _WIN32
    SOCKET
	#else
    int
	#endif 
    newsockfd,
    int bufferSize);
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
    NSSolverNativeSocketDispatcher(char* host,int port,int bufferSize);
    NSSolverNativeSocketDispatcher(int port,int bufferSize);
    ~NSSolverNativeSocketDispatcher();
    void dispatch();
  
    
   
    
};

#endif
