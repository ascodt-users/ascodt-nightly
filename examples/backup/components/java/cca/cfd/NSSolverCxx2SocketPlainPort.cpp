#include "cca/cfd/NSSolverCxx2SocketPlainPort.h"
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

cca::cfd::NSSolverCxx2SocketPlainPort::NSSolverCxx2SocketPlainPort(char* host,int port,int buffer_size):
     _buffer_size(buffer_size){
     _rcvBuffer=new char[_buffer_size];
     _sendBuffer=new char[_buffer_size];
     cca::cfd::NSSolverCxx2SocketPlainPort::open_client(host,port,_sockfd,_newsockfd);
     
}

cca::cfd::NSSolverCxx2SocketPlainPort::NSSolverCxx2SocketPlainPort(int port,int buffer_size):
    _buffer_size(buffer_size){
    _rcvBuffer=new char[_buffer_size];
    _sendBuffer=new char[_buffer_size];
    //cca::cfd::NSSolverCxx2SocketPlainPort::open_server(port,_sockfd,_newsockfd);
}

cca::cfd::NSSolverCxx2SocketPlainPort::~NSSolverCxx2SocketPlainPort(){
     int method=-1;
     sendData((char*)&method,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     delete [] _rcvBuffer;
     delete [] _sendBuffer;
     
     cca::cfd::NSSolverCxx2SocketPlainPort::close(_sockfd,_newsockfd);
     
}


//int cca::cfd::NSSolverCxx2SocketPlainPort::getSockfd(){
//     return _sockfd;
//}
//int cca::cfd::NSSolverCxx2SocketPlainPort::getNewsockfd(){
//     return _newsockfd;
//}

void cca::cfd::NSSolverCxx2SocketPlainPort::open_client(char* hostname,int port,
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
void cca::cfd::NSSolverCxx2SocketPlainPort::open_server(int port,int &sockfd,int &newsockfd){
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

void cca::cfd::NSSolverCxx2SocketPlainPort::sendData(char* data, size_t numberOfBytes, char* sendBuffer,
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


void cca::cfd::NSSolverCxx2SocketPlainPort::readData(char* data,size_t size_of_data,char* readBuffer,
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


void cca::cfd::NSSolverCxx2SocketPlainPort::close(
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

void cca::cfd::NSSolverCxx2SocketPlainPort::setup(const std::string inputScenario){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=69;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     int inputScenario_data_size=inputScenario.size()+1;
sendData((char*)&inputScenario_data_size,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)inputScenario.c_str(),inputScenario.size()+1,_sendBuffer,_newsockfd,_buffer_size);

     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::setupParallel(const std::string inputScenario){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=70;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     int inputScenario_data_size=inputScenario.size()+1;
sendData((char*)&inputScenario_data_size,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)inputScenario.c_str(),inputScenario.size()+1,_sendBuffer,_newsockfd,_buffer_size);

     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::setupCommForLBRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=71;
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

void cca::cfd::NSSolverCxx2SocketPlainPort::setupCommForLBRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=72;
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
void cca::cfd::NSSolverCxx2SocketPlainPort::solve(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=73;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::solveParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=74;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::solveOneTimestepPhaseOne(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=75;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::solveOneTimestepPhaseOneParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=76;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::solveOneTimestepPhaseTwo(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=77;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::solveOneTimestepPhaseTwoParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=78;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=79;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&velocitiesX_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesX,sizeof(double)*velocitiesX_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&velocitiesY_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesY,sizeof(double)*velocitiesY_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&velocitiesZ_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)velocitiesZ,sizeof(double)*velocitiesZ_len,_sendBuffer,_newsockfd,_buffer_size);

     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=80;
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
void cca::cfd::NSSolverCxx2SocketPlainPort::printNSPressure(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=81;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::printNSPressureParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=82;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::printNSProfiles(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=83;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::printNSProfilesParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=84;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::closeNSProfiles(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=85;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::closeNSProfilesParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=86;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::iterateBoundary(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=87;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::iterateBoundaryParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=88;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::iterateInner(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=89;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::iterateInnerParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=90;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags ^= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=91;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&keys_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)keys,sizeof(int)*keys_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&offsets_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)offsets,sizeof(int)*offsets_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&flips_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)flips,sizeof(int)*flips_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&values_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)values,sizeof(double)*values_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&componentSize_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)componentSize,sizeof(int)*componentSize_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&ackn,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&ackn,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

}

void cca::cfd::NSSolverCxx2SocketPlainPort::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,const int* componentSize, const int componentSize_len,int& ackn){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=92;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&keys_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)keys,sizeof(int)*keys_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&offsets_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)offsets,sizeof(int)*offsets_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&flips_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)flips,sizeof(int)*flips_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&values_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)values,sizeof(double)*values_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&componentSize_len,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)componentSize,sizeof(int)*componentSize_len,_sendBuffer,_newsockfd,_buffer_size);
sendData((char*)&ackn,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&ackn,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::plot(){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags |= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=93;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
}

void cca::cfd::NSSolverCxx2SocketPlainPort::plotParallel(){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=94;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     
     
     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
void cca::cfd::NSSolverCxx2SocketPlainPort::syncr(int& value){
     //assert(_destination!=NULL);
     #ifdef _WIN32
#else
int flags;
flags = fcntl(_newsockfd, F_GETFL, 0);
flags ^= O_NONBLOCK;
fcntl(_newsockfd, F_SETFL, flags);
#endif

     int methodId=95;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&value,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&value,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

}

void cca::cfd::NSSolverCxx2SocketPlainPort::syncrParallel(int& value){
     //assert(_destination!=NULL);
     int flags;
     flags = fcntl(_newsockfd, F_GETFL, 0);
     flags ^= O_NONBLOCK;
     fcntl(_newsockfd, F_SETFL, flags);
     int methodId=96;
     sendData((char*) &methodId, sizeof(int),_sendBuffer,_newsockfd,_buffer_size);
     sendData((char*)&value,sizeof(int),_sendBuffer,_newsockfd,_buffer_size);

     readData((char*)&value,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);

     //int ack=0;
     //readData((char*)&ack,sizeof(int),_rcvBuffer,_newsockfd,_buffer_size);
         
}
