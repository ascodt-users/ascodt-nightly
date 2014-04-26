#include "cca/cfd/UekermannDriverC2CxxProxy.h"
#ifdef _WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	
	#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  
	#define bcopy(b1,b2,len) (memmove((b2), (b1), (len)), (void) 0)
	#pragma comment(lib, "Ws2_32.lib")
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <unistd.h>
	#include <arpa/inet.h>
#endif

#include <stdio.h>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sstream>
#include "tinyxml2.h"
#include <hash_map>
#include <vector>
#ifdef Parallel
#include <mpi.h>
#endif
	
#include "cca/cfd/UekermannDriverImplementation.h"
CCA_CFD_UEKERMANNDRIVER_arg daemon_args;
void open_client(const char* hostname,const char* port,
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
		 WSADATA wsaData;
		 int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	     assert (iResult == 0);
#endif
          struct addrinfo *result = NULL,
     	                   hints;
          bzero( &hints, sizeof(hints) );
          hints.ai_family = AF_UNSPEC;
          hints.ai_socktype = SOCK_STREAM;
          hints.ai_protocol = IPPROTO_TCP;
          getaddrinfo(hostname, port, &hints, &result);
          sockfd = socket(result->ai_family, result->ai_socktype, 
            result->ai_protocol);
          assert(sockfd >= 0);
          
          int tries=60;
                while(tries>0){
                 if (connect(sockfd, result->ai_addr, (int)result->ai_addrlen)==0)
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

void bind_server(const char* port,
#ifdef _WIN32
SOCKET
#else
int
#endif 
&sockfd,
const int numberOfWorkers
){


#ifdef _WIN32
		 WSADATA wsaData;
		 int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	     assert (iResult == 0);
#endif
        
     int sockd, sockd2;
       int addrlen;
       struct sockaddr_in my_name, peer_name;
       int status;

       /* create a socket */
       sockd = socket(AF_INET, SOCK_STREAM, 0);
       if (sockd == -1)
       {
         perror("Socket creation error");
         exit(1);
       }


       /* server address  */
       my_name.sin_family = AF_INET;
       my_name.sin_addr.s_addr = INADDR_ANY;
       my_name.sin_port = htons(atoi(port));
       int yes=1;
       setsockopt(sockd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
       status = bind(sockd, (struct sockaddr*)&my_name, sizeof(my_name));
       if (status == -1)
       {
         perror("Binding error");
         exit(1);
       }

       status = listen(sockd, numberOfWorkers);
       sockfd=sockd;
         
        
}

void accept_on_server(
#ifdef _WIN32
SOCKET&
#else
int&
#endif
sockfd,
#ifdef _WIN32
SOCKET&
#else
int&
#endif
clientfd
){
           clientfd = accept(sockfd,
                    NULL,
                    NULL);
          assert (clientfd >= 0);
}

void sendData(char* data, size_t numberOfBytes, char* sendBuffer,
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

#ifdef Parallel
void broadcastParallelData(char* data,size_t size_of_data,MPI_Comm newsockfd){
          MPI_Status status;
           MPI_Bcast(data, size_of_data, MPI_BYTE, 0, newsockfd);
          
}
#endif

void readData(char* data,size_t size_of_data,char* readBuffer,
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

void invoker_create_instance(void** ref,int,int,char*,char*
#ifdef Parallel
	 ,MPI_Comm communicator,int methodID
#endif  
){
     *ref = new cca::cfd::UekermannDriverImplementation();
}

void invoker_destroy_instance(void** ref,int,int,char*,char*
#ifdef Parallel
	 ,MPI_Comm communicator,int methodID
#endif  
){
      delete ((cca::cfd::UekermannDriverImplementation*)*ref);
  
}
#include "cca/cfd/NSSolverNativeSocketDispatcher.h"
#include "cca/cfd/NSSolverCxx2SocketPlainPort.h"
void invoker_create_client_port_for_ns(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];
  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new cca::cfd::NSSolverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  delete [] host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
 
}
  
void invoker_create_client_port_for_ns(void** ref, void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  
  *portRef=new cca::cfd::NSSolverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  
}
void invoker_connect_client_dispatcher_ns(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];

  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new cca::cfd::NSSolverNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
  ((cca::cfd::UekermannDriverImplementation*)*ref)->connectns((cca::cfd::NSSolverNativeSocketDispatcher*)portref);   
  delete[]host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
}

void invoker_connect_client_dispatcher_ns(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  if(*dispatcherRef==NULL){
     *dispatcherRef=new cca::cfd::NSSolverNativeDispatcher();
     ((cca::cfd::UekermannDriverImplementation*)(*ref))->connectns((cca::cfd::NSSolverNativeDispatcher*) *dispatcherRef);   
  }
  ((cca::cfd::NSSolverNativeDispatcher*) (*dispatcherRef))->connect((cca::cfd::NSSolver*)(*portRef));
}




void invoker_disconnect_client_dispatcher_ns(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 ((cca::cfd::UekermannDriverImplementation*)*ref)->disconnectns();
}

void invoker_disconnect_client_dispatcher_ns(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
 ((cca::cfd::NSSolverNativeDispatcher*)*dispatcherRef)->disconnect((cca::cfd::NSSolver*)(*portRef));
}

#include "cca/cfd/NS2LBNativeSocketDispatcher.h"
#include "cca/cfd/NS2LBCxx2SocketPlainPort.h"
void invoker_create_client_port_for_ns2lb(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];
  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new cca::cfd::NS2LBCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  delete [] host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
 
}
  
void invoker_create_client_port_for_ns2lb(void** ref, void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  
  *portRef=new cca::cfd::NS2LBCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  
}
void invoker_connect_client_dispatcher_ns2lb(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];

  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new cca::cfd::NS2LBNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
  ((cca::cfd::UekermannDriverImplementation*)*ref)->connectns2lb((cca::cfd::NS2LBNativeSocketDispatcher*)portref);   
  delete[]host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
}

void invoker_connect_client_dispatcher_ns2lb(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  if(*dispatcherRef==NULL){
     *dispatcherRef=new cca::cfd::NS2LBNativeDispatcher();
     ((cca::cfd::UekermannDriverImplementation*)(*ref))->connectns2lb((cca::cfd::NS2LBNativeDispatcher*) *dispatcherRef);   
  }
  ((cca::cfd::NS2LBNativeDispatcher*) (*dispatcherRef))->connect((cca::cfd::NS2LB*)(*portRef));
}




void invoker_disconnect_client_dispatcher_ns2lb(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 ((cca::cfd::UekermannDriverImplementation*)*ref)->disconnectns2lb();
}

void invoker_disconnect_client_dispatcher_ns2lb(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
 ((cca::cfd::NS2LBNativeDispatcher*)*dispatcherRef)->disconnect((cca::cfd::NS2LB*)(*portRef));
}

#include "cca/cfd/LB2NSNativeSocketDispatcher.h"
#include "cca/cfd/LB2NSCxx2SocketPlainPort.h"
void invoker_create_client_port_for_lb2ns(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];
  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new cca::cfd::LB2NSCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  delete [] host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
 
}
  
void invoker_create_client_port_for_lb2ns(void** ref, void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  
  *portRef=new cca::cfd::LB2NSCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  
}
void invoker_connect_client_dispatcher_lb2ns(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];

  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new cca::cfd::LB2NSNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
  ((cca::cfd::UekermannDriverImplementation*)*ref)->connectlb2ns((cca::cfd::LB2NSNativeSocketDispatcher*)portref);   
  delete[]host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
}

void invoker_connect_client_dispatcher_lb2ns(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  if(*dispatcherRef==NULL){
     *dispatcherRef=new cca::cfd::LB2NSNativeDispatcher();
     ((cca::cfd::UekermannDriverImplementation*)(*ref))->connectlb2ns((cca::cfd::LB2NSNativeDispatcher*) *dispatcherRef);   
  }
  ((cca::cfd::LB2NSNativeDispatcher*) (*dispatcherRef))->connect((cca::cfd::LB2NS*)(*portRef));
}




void invoker_disconnect_client_dispatcher_lb2ns(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 ((cca::cfd::UekermannDriverImplementation*)*ref)->disconnectlb2ns();
}

void invoker_disconnect_client_dispatcher_lb2ns(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
 ((cca::cfd::LB2NSNativeDispatcher*)*dispatcherRef)->disconnect((cca::cfd::LB2NS*)(*portRef));
}

#include "cca/cfd/LBSolverNativeSocketDispatcher.h"
#include "cca/cfd/LBSolverCxx2SocketPlainPort.h"
void invoker_create_client_port_for_lb(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];
  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new cca::cfd::LBSolverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  delete [] host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
 
}
  
void invoker_create_client_port_for_lb(void** ref, void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  
  *portRef=new cca::cfd::LBSolverCxx2SocketPlainPort(
        host,
        port,
        buffer_size
   );
  
}
void invoker_connect_client_dispatcher_lb(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  long long portref=0;
  int port;
  int hostname_len=0;
  char* host;
  readData((char*)&hostname_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  host = new char[hostname_len];

  readData((char*)host,hostname_len,rcvBuffer,newsockfd,buffer_size);
  readData((char*)&port,sizeof(int),rcvBuffer,newsockfd,buffer_size);
  portref=(long long)new cca::cfd::LBSolverNativeSocketDispatcher(
           host,
           port,
           buffer_size
     );
  ((cca::cfd::UekermannDriverImplementation*)*ref)->connectlb((cca::cfd::LBSolverNativeSocketDispatcher*)portref);   
  delete[]host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
}

void invoker_connect_client_dispatcher_lb(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  if(*dispatcherRef==NULL){
     *dispatcherRef=new cca::cfd::LBSolverNativeDispatcher();
     ((cca::cfd::UekermannDriverImplementation*)(*ref))->connectlb((cca::cfd::LBSolverNativeDispatcher*) *dispatcherRef);   
  }
  ((cca::cfd::LBSolverNativeDispatcher*) (*dispatcherRef))->connect((cca::cfd::LBSolver*)(*portRef));
}




void invoker_disconnect_client_dispatcher_lb(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 ((cca::cfd::UekermannDriverImplementation*)*ref)->disconnectlb();
}

void invoker_disconnect_client_dispatcher_lb(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
 ((cca::cfd::LBSolverNativeDispatcher*)*dispatcherRef)->disconnect((cca::cfd::LBSolver*)(*portRef));
}

void invoker_go(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int configFile_str_len=0;
readData((char*)&configFile_str_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
char* configFile=new char[configFile_str_len];
readData((char*)configFile,configFile_str_len,rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::UekermannDriverImplementation*)*ref)->go(configFile);
  
}


void parallel_master_invoker_go(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int configFile_str_len=0;
readData((char*)&configFile_str_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
char* configFile=new char[configFile_str_len];
readData((char*)configFile,configFile_str_len,rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&configFile_str_len,sizeof(int),communicator);
broadcastParallelData((char*)configFile,configFile_str_len,communicator);

  #endif
  ((cca::cfd::UekermannDriverImplementation*)*ref)->go(configFile);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_go(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int configFile_str_len=0;
broadcastParallelData((char*)&configFile_str_len,sizeof(int),newsockfd);
char* configFile=new char[configFile_str_len];
broadcastParallelData((char*)configFile,configFile_str_len,newsockfd);

  ((cca::cfd::UekermannDriverImplementation*)*ref)->go(configFile);
  #endif		  
} 

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
&newsockfd){
#ifdef _WIN32
	 if(newsockfd>=0)
         closesocket(newsockfd);
     if(sockfd>=0)
         closesocket(sockfd);
#else

     if(newsockfd>=0)
         close(newsockfd);
     if(sockfd>=0)
         close(sockfd);
#endif
}


std::string retrieveSocketAddress(){
	std::stringstream res;
	  int rank = 0 ;
#ifdef Parallel
  
     MPI_Comm_rank(MPI_COMM_WORLD,&rank);
#endif
	int _sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(_sockfd>=0);
	const char* network_interface = getenv("CCA_CFD_UEKERMANNDRIVER_NET_INTERFACE");
	if(network_interface==NULL)
		network_interface="lo";	
	struct if_nameindex *curif, *ifs;
	struct ifreq req;
	ifs = if_nameindex();
	if(ifs) {
		for(curif = ifs; curif && curif->if_name; curif++) {
			strncpy(req.ifr_name, curif->if_name, IFNAMSIZ);
			req.ifr_name[IFNAMSIZ] = 0;
			if (ioctl(_sockfd, SIOCGIFADDR, &req) < 0)
				perror("ioctl");
			else{
				printf("%s: [%s]\n", curif->if_name,
                                                        inet_ntoa(((struct sockaddr_in*) &req.ifr_addr)->sin_addr));
				if(strcmp(curif->if_name,network_interface)==0)
				{
					res<<std::string(inet_ntoa(((struct sockaddr_in*) &req.ifr_addr)->sin_addr))<<":"<<(atoi(daemon_args.daemon_port.c_str())+rank);
					
				}
			}
		}
		if_freenameindex(ifs);
	}
	close(_sockfd);
	return res.str();
}


void socket_worker_loop(void* ref,
#ifdef _WIN32
SOCKET
#else
int
#endif
clientfd,int bufferSize
#ifdef Parallel
,MPI_Comm communicator
#endif
){
     char *sendBuffer=new char[bufferSize];
     char *rcvBuffer=new char[bufferSize];
     void (*invokers[97])(void**,int,int,char*,char*
#ifdef Parallel
	 ,MPI_Comm,int
#endif     
     );
     invokers[0]=invoker_create_instance;
     invokers[1]=invoker_destroy_instance;
     int methodId=0;
     invokers[68]=invoker_disconnect_client_dispatcher_ns;
invokers[67]=invoker_connect_client_dispatcher_ns;
invokers[66]=invoker_create_client_port_for_ns;
invokers[53]=invoker_disconnect_client_dispatcher_ns2lb;
invokers[52]=invoker_connect_client_dispatcher_ns2lb;
invokers[51]=invoker_create_client_port_for_ns2lb;
invokers[9]=invoker_disconnect_client_dispatcher_lb2ns;
invokers[8]=invoker_connect_client_dispatcher_lb2ns;
invokers[7]=invoker_create_client_port_for_lb2ns;
invokers[22]=invoker_disconnect_client_dispatcher_lb;
invokers[21]=invoker_connect_client_dispatcher_lb;
invokers[20]=invoker_create_client_port_for_lb;
invokers[6]=parallel_master_invoker_go;
invokers[5]=invoker_go;

     while(methodId!=1){
          readData((char*)&methodId,sizeof(int),rcvBuffer,clientfd,bufferSize);
          invokers[methodId](&ref,clientfd,bufferSize,rcvBuffer,sendBuffer
#ifdef Parallel
	 		,communicator,methodId
#endif            
          );
     }
     delete [] sendBuffer;
     delete [] rcvBuffer;
#ifdef _WIN32
     closesocket(clientfd);
#else
     close(clientfd);    
#endif    
     
}

#ifdef Parallel
void parallel_worker_loop(void* ref,
MPI_Comm clientfd){
     void (*parallel_worker_invokers[97])(void**,MPI_Comm);
     int methodId=0;
     parallel_worker_invokers[5]=parallel_worker_invoker_go;

     while(methodId!=1){
          broadcastParallelData((char*)&methodId,sizeof(int),clientfd);
          parallel_worker_invokers[methodId-1](&ref,clientfd);
     }
    
     
}

#endif

#ifdef Parallel
void* parallel_deamon_run(void* daemon_args){
	parallel_worker_loop(((CCA_CFD_UEKERMANNDRIVER_arg*)daemon_args)->ref,((CCA_CFD_UEKERMANNDRIVER_arg*)daemon_args)->communicator);
}
#endif
 
#ifdef _WIN32
DWORD WINAPI server_deamon_run(void* daemon_args){
      SOCKET clientfd;
#else  
void* server_deamon_run(void* daemon_args){
      int clientfd=0;
#endif
      accept_on_server(((CCA_CFD_UEKERMANNDRIVER_arg*)daemon_args)->daemon_serverfd,clientfd);
      std::cout<<"server accepted"<<std::endl;
      socket_worker_loop(
      	((CCA_CFD_UEKERMANNDRIVER_arg*)daemon_args)->ref,
      	clientfd,
      	((CCA_CFD_UEKERMANNDRIVER_arg*)daemon_args)->buffer_size
#ifdef Parallel
		,((CCA_CFD_UEKERMANNDRIVER_arg*)daemon_args)->communicator
#endif      	
      	);
}
void startMPIDaemon(CCA_CFD_UEKERMANNDRIVER_arg& arg){
#ifdef Parallel	 
int rank = -1;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
if(rank>0){
	 parallel_deamon_run(&arg);
}
#endif     
}

void startSocketDaemons(CCA_CFD_UEKERMANNDRIVER_arg& arg){
     std::vector<pthread_t> tasks;
  
     for(int i=0;i<arg.number_of_workers;i++){
     #ifdef _WIN32    
          CreateThread(NULL, 0,server_deamon_run, &arg, 0, NULL);
     #else     
          pthread_t task;
          tasks.push_back(task);
          pthread_create(&task,NULL,server_deamon_run,&arg);
     #endif
     }
   
}

void initialiseENV(CCA_CFD_UEKERMANNDRIVER_arg& arg){
          const char* client_port = getenv("CCA_CFD_UEKERMANNDRIVER_PORT");
          const char* daemon_port = getenv("CCA_CFD_UEKERMANNDRIVER_DAEMON_PORT");
          const char* buffer_size = getenv("CCA_CFD_UEKERMANNDRIVER_BUFFER_SIZE");
          const char* hostname = getenv("CCA_CFD_UEKERMANNDRIVER_HOSTNAME");
          const char* java_client_flag = getenv("CCA_CFD_UEKERMANNDRIVER_JAVA");
          const char* number_of_workers = getenv("CCA_CFD_UEKERMANNDRIVER_WORKERS");
          const char* xmlFile = getenv("CCA_CFD_UEKERMANNDRIVER_XML");
          if(buffer_size!=NULL)
               arg.buffer_size = atoi(buffer_size);
          if(hostname!=NULL)
               arg.hostname = hostname;
          if(client_port!=NULL)
               arg.client_port = client_port;
          if(daemon_port!=NULL)
               arg.daemon_port = daemon_port;
          if(java_client_flag!=NULL)
               arg.java_client_flag = (strcmp(java_client_flag,"off")==0)?false:true;
          if(number_of_workers!=NULL)
               arg.number_of_workers = atoi(number_of_workers);
          if(xmlFile!=NULL)
               arg.xml=xmlFile;
               
}

void initialiseXMLDaemons(CCA_CFD_UEKERMANNDRIVER_arg& arg){
    int rank=0;
   
    if(arg.xml!=NULL){
          tinyxml2::XMLDocument confFile;
          confFile.LoadFile(arg.xml);
          tinyxml2::XMLElement* root = confFile.FirstChildElement("diagram");
          __gnu_cxx::hash_map<int,std::vector<int> > connections;
          __gnu_cxx::hash_map<int,int> componentPorts;
          __gnu_cxx::hash_map<int,std::string> componentHosts;
          __gnu_cxx::hash_map<int,void*> dispatchers;
          void (*invokers[97])(void**,void**,void**,char* host,int port,int buffer_size);
          
           invokers[68]=invoker_disconnect_client_dispatcher_ns;
invokers[67]=invoker_connect_client_dispatcher_ns;
invokers[66]=invoker_create_client_port_for_ns;
invokers[53]=invoker_disconnect_client_dispatcher_ns2lb;
invokers[52]=invoker_connect_client_dispatcher_ns2lb;
invokers[51]=invoker_create_client_port_for_ns2lb;
invokers[9]=invoker_disconnect_client_dispatcher_lb2ns;
invokers[8]=invoker_connect_client_dispatcher_lb2ns;
invokers[7]=invoker_create_client_port_for_lb2ns;
invokers[22]=invoker_disconnect_client_dispatcher_lb;
invokers[21]=invoker_connect_client_dispatcher_lb;
invokers[20]=invoker_create_client_port_for_lb;

          for(tinyxml2::XMLElement* e = root->FirstChildElement("component"); e != NULL; e = e->NextSiblingElement("component"))
          {
            if(strcmp(e->Attribute("name"),"cca.cfd.UekermannDriver")==0){
                 int port;
                 std::stringstream str;
                 e->QueryIntAttribute("port",&port);
                 str<<(port+1);
                 arg.daemon_port=str.str();
                 for(
                           tinyxml2::XMLElement* conElement = e->FirstChildElement("outputPort");
                           conElement != NULL;
                           conElement = conElement->NextSiblingElement("outputPort"))
                 {
                      int key=0;
                      int createId=0,connectId=0,disconnectId=0;

                      conElement->QueryIntAttribute("index",&key);
                      conElement->QueryIntAttribute("createId",&createId);
                      conElement->QueryIntAttribute("connectId",&connectId);
                      conElement->QueryIntAttribute("disconnectId",&disconnectId);
                      connections[key].resize(3);
                      connections[key][0]=createId;
                      connections[key][1]=connectId;
                      connections[key][2]=disconnectId;

                 }
            }else{
                 int port=0;
                 e->QueryIntAttribute("port",&port);
                 const char* hostname=e->Attribute("host");
                 for(
                           tinyxml2::XMLElement* conElement = e->FirstChildElement("inputPort");
                           conElement != NULL;
                           conElement = conElement->NextSiblingElement("inputPort"))
                 {
                     int key=0;
                     conElement->QueryIntAttribute("index",&key);
                     componentPorts[key]=port+1;
                     componentHosts[key]=hostname;
                 }
            }
          }
      
     }
}
void initialiseXMLConnections(CCA_CFD_UEKERMANNDRIVER_arg& arg){
    int rank=0;
   
    if(arg.xml!=NULL){
          tinyxml2::XMLDocument confFile;
          confFile.LoadFile(arg.xml);
          tinyxml2::XMLElement* root = confFile.FirstChildElement("diagram");
          __gnu_cxx::hash_map<int,std::vector<int> > connections;
          __gnu_cxx::hash_map<int,int> componentPorts;
          __gnu_cxx::hash_map<int,std::string> componentHosts;
          __gnu_cxx::hash_map<int,void*> dispatchers;
          void (*invokers[97])(void**,void**,void**,char* host,int port,int buffer_size);
          
           invokers[68]=invoker_disconnect_client_dispatcher_ns;
invokers[67]=invoker_connect_client_dispatcher_ns;
invokers[66]=invoker_create_client_port_for_ns;
invokers[53]=invoker_disconnect_client_dispatcher_ns2lb;
invokers[52]=invoker_connect_client_dispatcher_ns2lb;
invokers[51]=invoker_create_client_port_for_ns2lb;
invokers[9]=invoker_disconnect_client_dispatcher_lb2ns;
invokers[8]=invoker_connect_client_dispatcher_lb2ns;
invokers[7]=invoker_create_client_port_for_lb2ns;
invokers[22]=invoker_disconnect_client_dispatcher_lb;
invokers[21]=invoker_connect_client_dispatcher_lb;
invokers[20]=invoker_create_client_port_for_lb;

          for(tinyxml2::XMLElement* e = root->FirstChildElement("component"); e != NULL; e = e->NextSiblingElement("component"))
          {
            if(strcmp(e->Attribute("name"),"cca.cfd.UekermannDriver")==0){
                 int port;
                 std::stringstream str;
                 e->QueryIntAttribute("port",&port);
                 str<<(port+1);
                 arg.daemon_port=str.str();
                 for(
                           tinyxml2::XMLElement* conElement = e->FirstChildElement("outputPort");
                           conElement != NULL;
                           conElement = conElement->NextSiblingElement("outputPort"))
                 {
                      int key=0;
                      int createId=0,connectId=0,disconnectId=0;

                      conElement->QueryIntAttribute("index",&key);
                      conElement->QueryIntAttribute("createId",&createId);
                      conElement->QueryIntAttribute("connectId",&connectId);
                      conElement->QueryIntAttribute("disconnectId",&disconnectId);
                      connections[key].resize(3);
                      connections[key][0]=createId;
                      connections[key][1]=connectId;
                      connections[key][2]=disconnectId;

                 }
            }else{
                 int port=0;
                 e->QueryIntAttribute("port",&port);
                 const char* hostname=e->Attribute("host");
                 for(
                           tinyxml2::XMLElement* conElement = e->FirstChildElement("inputPort");
                           conElement != NULL;
                           conElement = conElement->NextSiblingElement("inputPort"))
                 {
                     int key=0;
                     conElement->QueryIntAttribute("index",&key);
                     componentPorts[key]=port+1;
                     componentHosts[key]=hostname;
                 }
            }
          }
       #ifdef Parallel
    
       MPI_Comm_rank(MPI_COMM_WORLD,&rank);
       if(rank==0){
          #endif
          for(tinyxml2::XMLElement* e = root->FirstChildElement("connection"); e != NULL; e = e->NextSiblingElement("connection"))
          {
            int source=-1;
            int destination=-1;
            e->QueryIntAttribute("source",&source);
            e->QueryIntAttribute("destination",&destination);
            __gnu_cxx::hash_map<int,std::vector<int> >::iterator itSource = connections.find(source);
            __gnu_cxx::hash_map<int,std::string >::iterator itDestination = componentHosts.find(destination);
            if(itSource!=connections.end()&&itDestination!=componentHosts.end()){
                 std::cout<<"establish connection from xml id:"<< source<<" host:"<<
                    componentHosts[destination]<<" port:"<<componentPorts[destination]<<std::endl;
                 if(dispatchers.find(source)==dispatchers.end())
                     dispatchers[source]=NULL;
                 void* port =NULL;
                 invokers[(*itSource).second[0]](
                          &arg.ref,
                          NULL,
                          &port,
                          (char*)componentHosts[destination].c_str(),
                          componentPorts[destination],
                          arg.buffer_size);
                 invokers[(*itSource).second[1]](
                               &arg.ref,
                               &dispatchers[source],
                               &port,
                              (char*)componentHosts[destination].c_str(),
                               componentPorts[destination],
                               arg.buffer_size);
            }
          }
       #ifdef Parallel
       }
       #endif
     }
}

void initialiseParallel(CCA_CFD_UEKERMANNDRIVER_arg& arg){
#ifdef Parallel
     int rank = -1 ;
     int comm_size;
     std::stringstream st;

     MPI_Comm_rank(MPI_COMM_WORLD,&rank);
     MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
     int port=atoi(arg.daemon_port.c_str())+rank;
     st<<port<<'\0';
     std::vector<char> daemon_str(st.str().size()+1);
     strncpy(&daemon_str[0],st.str().c_str(),st.str().size());
     daemon_str[st.str().size()]='\0';
     arg.communicator = MPI_COMM_WORLD;
     arg.daemon_port=std::string(&daemon_str[0]);
     if(rank>0){
          arg.java_client_flag=false;
          arg.joinable=false;
     }
      
#endif
}
extern "C"{

#ifdef _WIN32
void INITIALISE(CCA_CFD_UEKERMANNDRIVER_arg& arg){
#else
void initialise_(CCA_CFD_UEKERMANNDRIVER_arg& arg,bool joinable){
#endif
     arg.buffer_size = 4096;
     arg.hostname = "localhost";
     arg.client_port = "50000";
     arg.daemon_port = "50001";
     arg.java_client_flag = true;
     arg.number_of_workers = 10;
     arg.xml=NULL;
     arg.joinable=joinable;
     initialiseENV(arg);
     

   invoker_create_instance(&arg.ref,0,0,NULL,NULL
#ifdef Parallel
   ,MPI_COMM_WORLD,0 	
#endif   
   );
   initialiseXMLDaemons(arg);
   initialiseParallel(arg);
   if(arg.java_client_flag)         
     open_client(arg.hostname.c_str(),arg.client_port.c_str(),arg.java_serverfd,arg.java_clientfd);
   
   bind_server(arg.daemon_port.c_str(),arg.daemon_serverfd,arg.number_of_workers);
   startSocketDaemons(arg);
   initialiseXMLConnections(arg);
   if(arg.joinable)
     server_deamon_run(&arg);
   startMPIDaemon(arg);
}





#ifdef _WIN32
void DESTROY(CCA_CFD_UEKERMANNDRIVER_arg& arg){
#else
void destroy_(CCA_CFD_UEKERMANNDRIVER_arg& arg){
#endif
#ifdef _WIN32
  closesocket(arg.daemon_serverfd);
  if(arg.java_client_flag)
     closesocket(arg.java_serverfd);    
#else
  close(arg.daemon_serverfd);
  if(arg.java_client_flag)
     close(arg.java_serverfd);
#endif
  
  
   
#ifdef _WIN32
  WSACleanup();
#endif   

}

#ifdef _WIN32
void SOCKET_LOOP(CCA_CFD_UEKERMANNDRIVER_arg& arg){
#else
void socket_loop_(CCA_CFD_UEKERMANNDRIVER_arg& arg,bool joinable){
#endif
  if(arg.java_client_flag)       
     socket_worker_loop(arg.ref,arg.java_clientfd,arg.buffer_size
#ifdef Parallel
     ,arg.communicator
#endif     
     );
}

#ifdef _WIN32
void MAIN_LOOP(){
#else
void main_loop_(bool joinable){
#endif
  

  
#ifdef _WIN32
  INITIALISE(daemon_args);
  DESTROY(daemon_args);     
#else  
  initialise_(daemon_args,joinable);
  socket_loop_(daemon_args,joinable);
  destroy_(daemon_args);  
#endif
  
}

}





