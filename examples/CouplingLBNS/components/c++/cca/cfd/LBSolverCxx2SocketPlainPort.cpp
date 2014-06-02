#include "cca/cfd/LBSolverCxx2SocketPlainPort.h"
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <sstream>

cca::cfd::LBSolverCxx2SocketPlainPort::LBSolverCxx2SocketPlainPort(char* host,int port,int buffer_size):
     _buffer_size(buffer_size){
     _rcvBuffer=new char[_buffer_size];
     _sendBuffer=new char[_buffer_size];
     cca::cfd::LBSolverCxx2SocketPlainPort::open_client(host,port,_sockfd,_newsockfd);
     
}

cca::cfd::LBSolverCxx2SocketPlainPort::LBSolverCxx2SocketPlainPort(int port,int buffer_size):
    _buffer_size(buffer_size){
    _rcvBuffer=new char[_buffer_size];
    _sendBuffer=new char[_buffer_size];
    //cca::cfd::LBSolverCxx2SocketPlainPort::open_server(port,_sockfd,_newsockfd);
}

cca::cfd::LBSolverCxx2SocketPlainPort::~LBSolverCxx2SocketPlainPort(){
     int method=-1;
     sendData((char*)&method,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     delete [] _rcvBuffer;
     delete [] _sendBuffer;
     
     cca::cfd::LBSolverCxx2SocketPlainPort::close(_sockfd,_newsockfd);
     
}


//int cca::cfd::LBSolverCxx2SocketPlainPort::getSockfd(){
//     return _sockfd;
//}
//int cca::cfd::LBSolverCxx2SocketPlainPort::getNewsockfd(){
//     return _newsockfd;
//}

void cca::cfd::LBSolverCxx2SocketPlainPort::open_client(char* hostname,int port,
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
&newsockfd){
		  std::stringstream port_str;
		  port_str<<port;
          struct addrinfo *result = NULL,
     	                   hints;
          bzero( &hints, sizeof(hints) );
          hints.ai_family = AF_UNSPEC;
          hints.ai_socktype = SOCK_STREAM;
          hints.ai_protocol = IPPROTO_TCP;
          getaddrinfo(hostname, port_str.str().c_str(), &hints, &result);
          sockfd = socket(result->ai_family, result->ai_socktype, 
            result->ai_protocol);
          assert(sockfd >= 0);
          
          int tries=60;
                while(tries>0){
                 if (::connect(sockfd, result->ai_addr, (int)result->ai_addrlen)==0)
                    break;
                         tries--;
#ifdef _WIN32
						 Sleep(1000);
#else
						 sleep(1);
#endif	
                }   
         newsockfd=sockfd;
        
}

/*
void cca::cfd::LBSolverCxx2SocketPlainPort::open_server(int port,int &sockfd,int &newsockfd){
          socklen_t clilen;

          struct sockaddr_in serv_addr, cli_addr;

          sockfd = socket(AF_INET, SOCK_STREAM, 0);
          assert (sockfd>=0);

          bzero((char *) &serv_addr, sizeof(serv_addr));
          serv_addr.sin_family = AF_INET;
          serv_addr.sin_addr.s_addr = INADDR_ANY;
          serv_addr.sin_port = htons(port);
          assert (bind(sockfd, (struct sockaddr *) &serv_addr,
                    sizeof(serv_addr)) >= 0);
          listen(sockfd,5);
          clilen = sizeof(cli_addr);
          newsockfd = accept(sockfd,
                    (struct sockaddr *) &cli_addr,
                    &clilen);
          assert (newsockfd >= 0);
}
*/

void cca::cfd::LBSolverCxx2SocketPlainPort::sendData(char* data, size_t numberOfBytes, char* sendBuffer,
#ifdef _WIN32
SOCKET
#else
int
#endif 
newsockfd,int bufferSize){
     char* data_ptr=(char*)data;
     int remaining_bytes_to_send=0,total_send_bytes=0,send_bytes=0,n=0;

     //clear buffer
     bzero(sendBuffer,bufferSize);
     while(total_send_bytes<numberOfBytes){
          remaining_bytes_to_send=(numberOfBytes-total_send_bytes<=bufferSize)?numberOfBytes-total_send_bytes:bufferSize;
          memcpy(sendBuffer,data_ptr,remaining_bytes_to_send);
          send_bytes=0;
          char* send_buffer_ptr=sendBuffer;
          while(send_bytes<bufferSize){
               n = 
#ifdef _WIN32
				   send(
#else

				   write(
#endif
				   newsockfd,send_buffer_ptr,bufferSize-send_bytes
#ifdef _WIN32
				   ,0
#else

#endif
				   );
               if(n>0){
                    send_bytes+=n;
                    send_buffer_ptr+=n;
               }
          }
          total_send_bytes+=send_bytes;
          data_ptr+=send_bytes;
     }

}


void cca::cfd::LBSolverCxx2SocketPlainPort::readData(char* data,size_t size_of_data,char* readBuffer,
#ifdef _WIN32
SOCKET
#else
int
#endif 
newsockfd, int bufferSize){
          bzero(readBuffer,bufferSize);
          int bytes_received=0;
          int total_bytes_received=0;
          int local_bytes_received=0;
          int bytes_to_copy=0;
          char* data_ptr=data;
          char* buffer_ptr;

          while(total_bytes_received<size_of_data){
               bytes_received=0;
               buffer_ptr=readBuffer;
               while(bytes_received<bufferSize){
                    local_bytes_received = 
#ifdef _WIN32
						recv(
#else
						read(
#endif
							newsockfd,buffer_ptr,bufferSize-bytes_received
#ifdef _WIN32
							,0
#else
#endif
							);
                    if(local_bytes_received>0){
                         bytes_received+=local_bytes_received;
                         buffer_ptr+=local_bytes_received;
                    }
               }
               bytes_to_copy=(total_bytes_received+bytes_received>size_of_data)?size_of_data-total_bytes_received:bytes_received;
               memcpy(data_ptr,readBuffer,bytes_to_copy);
               data_ptr+=bytes_to_copy;
               total_bytes_received+=bytes_to_copy;
          }

}


void cca::cfd::LBSolverCxx2SocketPlainPort::close(
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
&newsockfd){
#ifdef _WIN32
	 if(newsockfd>=0)
         closesocket(newsockfd);
     if(sockfd>=0)
         closesocket(sockfd);
#else

     if(newsockfd>=0)
         ::close(newsockfd);
     if(sockfd>=0)
         ::close(sockfd);
#endif
}

void cca::cfd::LBSolverCxx2SocketPlainPort::setup(const std::string inputScenario){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=23;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     int inputScenario_data_size=inputScenario.size()+1;
sendData((char*)&inputScenario_data_size,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)inputScenario.c_str(),inputScenario.size()+1,_sendBuffer,_newsockfd,_buffer_size);

     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::setupParallel(const std::string inputScenario){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=24;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     int inputScenario_data_size=inputScenario.size()+1;
sendData((char*)&inputScenario_data_size,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)inputScenario.c_str(),inputScenario.size()+1,_sendBuffer,_newsockfd,_buffer_size);

     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::setupCommForNSRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=25;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&startOfRegion_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)startOfRegion,sizeof(int)*startOfRegion_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&endOfRegion_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)endOfRegion,sizeof(int)*endOfRegion_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&commids_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
for(int i=0;i<commids_len;i++){
	int data_size=commids[i].size();
	sendData((char*)&data_size,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
	sendData((char*)commids[i].c_str(),commids[i].size()<255?commids[i].size():255,_sendBuffer,_newsockfd,_buffer_size);
}

     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::setupCommForNSRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=26;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&startOfRegion_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)startOfRegion,sizeof(int)*startOfRegion_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&endOfRegion_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)endOfRegion,sizeof(int)*endOfRegion_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&commids_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
for(int i=0;i<commids_len;i++){
	int data_size=commids[i].size();
	sendData((char*)&data_size,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
	sendData((char*)commids[i].c_str(),commids[i].size()<255?commids[i].size():255,_sendBuffer,_newsockfd,_buffer_size);
}

     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::solve(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=27;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::solveParallel(){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=28;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::solveOneTimestep(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=29;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::solveOneTimestepParallel(){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=30;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=31;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&velocitiesX_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesX,sizeof(double)*velocitiesX_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&velocitiesY_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesY,sizeof(double)*velocitiesY_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&velocitiesZ_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesZ,sizeof(double)*velocitiesZ_len,_sendBuffer,_newsockfd,_buffer_size);

     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=32;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&velocitiesX_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesX,sizeof(double)*velocitiesX_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&velocitiesY_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesY,sizeof(double)*velocitiesY_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&velocitiesZ_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesZ,sizeof(double)*velocitiesZ_len,_sendBuffer,_newsockfd,_buffer_size);

     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::setPressure(const double* pressure, const int pressure_len){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=33;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&pressure_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)pressure,sizeof(double)*pressure_len,_sendBuffer,_newsockfd,_buffer_size);

     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::setPressureParallel(const double* pressure, const int pressure_len){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=34;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&pressure_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)pressure,sizeof(double)*pressure_len,_sendBuffer,_newsockfd,_buffer_size);

     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::setGradients(const double* gradients, const int gradients_len){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=35;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&gradients_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)gradients,sizeof(double)*gradients_len,_sendBuffer,_newsockfd,_buffer_size);

     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::setGradientsParallel(const double* gradients, const int gradients_len){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=36;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&gradients_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)gradients,sizeof(double)*gradients_len,_sendBuffer,_newsockfd,_buffer_size);

     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::closeLBProfiles(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=37;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::closeLBProfilesParallel(){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=38;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::printLBDensity(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=39;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::printLBDensityParallel(){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=40;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::printLBProfiles(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=41;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::printLBProfilesParallel(){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=42;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags ^= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=43;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&keys_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)keys,sizeof(int)*keys_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&offsets_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)offsets,sizeof(int)*offsets_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&flips_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)flips,sizeof(int)*flips_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&values_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)values,sizeof(double)*values_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&ackn,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&ackn,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

}

void cca::cfd::LBSolverCxx2SocketPlainPort::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=44;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&keys_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)keys,sizeof(int)*keys_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&offsets_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)offsets,sizeof(int)*offsets_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&flips_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)flips,sizeof(int)*flips_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&values_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)values,sizeof(double)*values_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&ackn,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&ackn,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::forwardPressure(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags ^= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=45;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&keys_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)keys,sizeof(int)*keys_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&offsets_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)offsets,sizeof(int)*offsets_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&flips_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)flips,sizeof(int)*flips_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&values_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)values,sizeof(double)*values_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&ackn,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&ackn,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

}

void cca::cfd::LBSolverCxx2SocketPlainPort::forwardPressureParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=46;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&keys_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)keys,sizeof(int)*keys_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&offsets_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)offsets,sizeof(int)*offsets_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&flips_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)flips,sizeof(int)*flips_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&values_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)values,sizeof(double)*values_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&ackn,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&ackn,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::syncr(int& value){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags ^= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=47;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&value,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&value,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

}

void cca::cfd::LBSolverCxx2SocketPlainPort::syncrParallel(int& value){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=48;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&value,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&value,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::LBSolverCxx2SocketPlainPort::plot(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=49;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::LBSolverCxx2SocketPlainPort::plotParallel(){
     //assert(_destination!=NULL);
#ifdef _WIN32
#else
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
#endif
     int methodId=50;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
