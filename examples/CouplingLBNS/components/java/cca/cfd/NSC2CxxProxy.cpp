#include "cca/cfd/NSC2CxxProxy.h"
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
	
#include "cca/cfd/NSImplementation.h"
CCA_CFD_NS_arg daemon_args;
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
     *ref = new cca::cfd::NSImplementation();
}

void invoker_destroy_instance(void** ref,int,int,char*,char*
#ifdef Parallel
	 ,MPI_Comm communicator,int methodID
#endif  
){
      delete ((cca::cfd::NSImplementation*)*ref);
  
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
  ((cca::cfd::NSImplementation*)*ref)->connectlb((cca::cfd::LBSolverNativeSocketDispatcher*)portref);   
  delete[]host;
  sendData((char*)&portref,sizeof(long long),sendBuffer,newsockfd,buffer_size);
}

void invoker_connect_client_dispatcher_lb(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
  if(*dispatcherRef==NULL){
     *dispatcherRef=new cca::cfd::LBSolverNativeDispatcher();
     ((cca::cfd::NSImplementation*)(*ref))->connectlb((cca::cfd::LBSolverNativeDispatcher*) *dispatcherRef);   
  }
  ((cca::cfd::LBSolverNativeDispatcher*) (*dispatcherRef))->connect((cca::cfd::LBSolver*)(*portRef));
}




void invoker_disconnect_client_dispatcher_lb(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 ((cca::cfd::NSImplementation*)*ref)->disconnectlb();
}

void invoker_disconnect_client_dispatcher_lb(void** ref,void** dispatcherRef, void** portRef, char* host,int port,int buffer_size){
 ((cca::cfd::LBSolverNativeDispatcher*)*dispatcherRef)->disconnect((cca::cfd::LBSolver*)(*portRef));
}

void invoker_retrievePressureCopy(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int pressure_len=0;
readData((char*)&pressure_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* pressure=new double[pressure_len];
readData((char*)pressure,sizeof(double)*pressure_len,rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->retrievePressureCopy(pressure,pressure_len);
  sendData((char*)&pressure_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)pressure,sizeof(double)*pressure_len,sendBuffer,newsockfd,buffer_size);
delete [] pressure;

}


void parallel_master_invoker_retrievePressureCopy(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int pressure_len=0;
readData((char*)&pressure_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* pressure=new double[pressure_len];
readData((char*)pressure,sizeof(double)*pressure_len,rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&pressure_len,sizeof(int),communicator);
broadcastParallelData((char*)pressure,sizeof(double)*pressure_len,communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->retrievePressureCopy(pressure,pressure_len);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_retrievePressureCopy(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int pressure_len=0;
broadcastParallelData((char*)&pressure_len,sizeof(int),newsockfd);
double* pressure=new double[pressure_len];
broadcastParallelData((char*)pressure,sizeof(double)*pressure_len,newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->retrievePressureCopy(pressure,pressure_len);
  #endif		  
} 
void invoker_retrieveJacobianCopy(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int jacobian_len=0;
readData((char*)&jacobian_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* jacobian=new double[jacobian_len];
readData((char*)jacobian,sizeof(double)*jacobian_len,rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->retrieveJacobianCopy(jacobian,jacobian_len);
  sendData((char*)&jacobian_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)jacobian,sizeof(double)*jacobian_len,sendBuffer,newsockfd,buffer_size);
delete [] jacobian;

}


void parallel_master_invoker_retrieveJacobianCopy(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int jacobian_len=0;
readData((char*)&jacobian_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* jacobian=new double[jacobian_len];
readData((char*)jacobian,sizeof(double)*jacobian_len,rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&jacobian_len,sizeof(int),communicator);
broadcastParallelData((char*)jacobian,sizeof(double)*jacobian_len,communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->retrieveJacobianCopy(jacobian,jacobian_len);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_retrieveJacobianCopy(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int jacobian_len=0;
broadcastParallelData((char*)&jacobian_len,sizeof(int),newsockfd);
double* jacobian=new double[jacobian_len];
broadcastParallelData((char*)jacobian,sizeof(double)*jacobian_len,newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->retrieveJacobianCopy(jacobian,jacobian_len);
  #endif		  
} 
void invoker_retrieveVelocitiesCopy(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int velocityX_len=0;
readData((char*)&velocityX_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocityX=new double[velocityX_len];
readData((char*)velocityX,sizeof(double)*velocityX_len,rcvBuffer,newsockfd,buffer_size);
int velocityY_len=0;
readData((char*)&velocityY_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocityY=new double[velocityY_len];
readData((char*)velocityY,sizeof(double)*velocityY_len,rcvBuffer,newsockfd,buffer_size);
int velocityZ_len=0;
readData((char*)&velocityZ_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocityZ=new double[velocityZ_len];
readData((char*)velocityZ,sizeof(double)*velocityZ_len,rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->retrieveVelocitiesCopy(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
  sendData((char*)&velocityX_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)velocityX,sizeof(double)*velocityX_len,sendBuffer,newsockfd,buffer_size);
delete [] velocityX;
sendData((char*)&velocityY_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)velocityY,sizeof(double)*velocityY_len,sendBuffer,newsockfd,buffer_size);
delete [] velocityY;
sendData((char*)&velocityZ_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)velocityZ,sizeof(double)*velocityZ_len,sendBuffer,newsockfd,buffer_size);
delete [] velocityZ;

}


void parallel_master_invoker_retrieveVelocitiesCopy(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int velocityX_len=0;
readData((char*)&velocityX_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocityX=new double[velocityX_len];
readData((char*)velocityX,sizeof(double)*velocityX_len,rcvBuffer,newsockfd,buffer_size);
int velocityY_len=0;
readData((char*)&velocityY_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocityY=new double[velocityY_len];
readData((char*)velocityY,sizeof(double)*velocityY_len,rcvBuffer,newsockfd,buffer_size);
int velocityZ_len=0;
readData((char*)&velocityZ_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocityZ=new double[velocityZ_len];
readData((char*)velocityZ,sizeof(double)*velocityZ_len,rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&velocityX_len,sizeof(int),communicator);
broadcastParallelData((char*)velocityX,sizeof(double)*velocityX_len,communicator);
broadcastParallelData((char*)&velocityY_len,sizeof(int),communicator);
broadcastParallelData((char*)velocityY,sizeof(double)*velocityY_len,communicator);
broadcastParallelData((char*)&velocityZ_len,sizeof(int),communicator);
broadcastParallelData((char*)velocityZ,sizeof(double)*velocityZ_len,communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->retrieveVelocitiesCopy(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_retrieveVelocitiesCopy(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int velocityX_len=0;
broadcastParallelData((char*)&velocityX_len,sizeof(int),newsockfd);
double* velocityX=new double[velocityX_len];
broadcastParallelData((char*)velocityX,sizeof(double)*velocityX_len,newsockfd);
int velocityY_len=0;
broadcastParallelData((char*)&velocityY_len,sizeof(int),newsockfd);
double* velocityY=new double[velocityY_len];
broadcastParallelData((char*)velocityY,sizeof(double)*velocityY_len,newsockfd);
int velocityZ_len=0;
broadcastParallelData((char*)&velocityZ_len,sizeof(int),newsockfd);
double* velocityZ=new double[velocityZ_len];
broadcastParallelData((char*)velocityZ,sizeof(double)*velocityZ_len,newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->retrieveVelocitiesCopy(velocityX,velocityX_len,velocityY,velocityY_len,velocityZ,velocityZ_len);
  #endif		  
} 
void invoker_retrieveVelocitiesSize(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int memory;
readData((char*)&memory,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->retrieveVelocitiesSize(memory);
  sendData((char*)&memory,sizeof(int),sendBuffer,newsockfd,buffer_size);

}


void parallel_master_invoker_retrieveVelocitiesSize(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int memory;
readData((char*)&memory,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&memory,sizeof(int),communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->retrieveVelocitiesSize(memory);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_retrieveVelocitiesSize(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int memory;
broadcastParallelData((char*)&memory,sizeof(int),newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->retrieveVelocitiesSize(memory);
  #endif		  
} 
void invoker_retrieveTimestep(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  double timestep;
readData((char*)&timestep,sizeof(double),rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->retrieveTimestep(timestep);
  sendData((char*)&timestep,sizeof(double),sendBuffer,newsockfd,buffer_size);

}


void parallel_master_invoker_retrieveTimestep(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  double timestep;
readData((char*)&timestep,sizeof(double),rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&timestep,sizeof(double),communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->retrieveTimestep(timestep);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_retrieveTimestep(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  double timestep;
broadcastParallelData((char*)&timestep,sizeof(double),newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->retrieveTimestep(timestep);
  #endif		  
} 
void invoker_iterate(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->iterate();
  
}


void parallel_master_invoker_iterate(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->iterate();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_iterate(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->iterate();
  #endif		  
} 
void invoker_syncr(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int value;
readData((char*)&value,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->syncr(value);
  sendData((char*)&value,sizeof(int),sendBuffer,newsockfd,buffer_size);

}


void parallel_master_invoker_syncr(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int value;
readData((char*)&value,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&value,sizeof(int),communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->syncr(value);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_syncr(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int value;
broadcastParallelData((char*)&value,sizeof(int),newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->syncr(value);
  #endif		  
} 
void invoker_plot(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->plot();
  
}


void parallel_master_invoker_plot(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->plot();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_plot(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->plot();
  #endif		  
} 
void invoker_forwardVelocities(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int keys_len=0;
readData((char*)&keys_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* keys=new int[keys_len];
readData((char*)keys,sizeof(int)*keys_len,rcvBuffer,newsockfd,buffer_size);
int offsets_len=0;
readData((char*)&offsets_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* offsets=new int[offsets_len];
readData((char*)offsets,sizeof(int)*offsets_len,rcvBuffer,newsockfd,buffer_size);
int flips_len=0;
readData((char*)&flips_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* flips=new int[flips_len];
readData((char*)flips,sizeof(int)*flips_len,rcvBuffer,newsockfd,buffer_size);
int values_len=0;
readData((char*)&values_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* values=new double[values_len];
readData((char*)values,sizeof(double)*values_len,rcvBuffer,newsockfd,buffer_size);
int ackn;
readData((char*)&ackn,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->forwardVelocities(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
  delete [] keys;
delete [] offsets;
delete [] flips;
delete [] values;
sendData((char*)&ackn,sizeof(int),sendBuffer,newsockfd,buffer_size);

}


void parallel_master_invoker_forwardVelocities(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int keys_len=0;
readData((char*)&keys_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* keys=new int[keys_len];
readData((char*)keys,sizeof(int)*keys_len,rcvBuffer,newsockfd,buffer_size);
int offsets_len=0;
readData((char*)&offsets_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* offsets=new int[offsets_len];
readData((char*)offsets,sizeof(int)*offsets_len,rcvBuffer,newsockfd,buffer_size);
int flips_len=0;
readData((char*)&flips_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* flips=new int[flips_len];
readData((char*)flips,sizeof(int)*flips_len,rcvBuffer,newsockfd,buffer_size);
int values_len=0;
readData((char*)&values_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* values=new double[values_len];
readData((char*)values,sizeof(double)*values_len,rcvBuffer,newsockfd,buffer_size);
int ackn;
readData((char*)&ackn,sizeof(int),rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&keys_len,sizeof(int),communicator);
broadcastParallelData((char*)keys,sizeof(int)*keys_len,communicator);
broadcastParallelData((char*)&offsets_len,sizeof(int),communicator);
broadcastParallelData((char*)offsets,sizeof(int)*offsets_len,communicator);
broadcastParallelData((char*)&flips_len,sizeof(int),communicator);
broadcastParallelData((char*)flips,sizeof(int)*flips_len,communicator);
broadcastParallelData((char*)&values_len,sizeof(int),communicator);
broadcastParallelData((char*)values,sizeof(double)*values_len,communicator);
broadcastParallelData((char*)&ackn,sizeof(int),communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->forwardVelocities(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_forwardVelocities(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int keys_len=0;
broadcastParallelData((char*)&keys_len,sizeof(int),newsockfd);
int* keys=new int[keys_len];
broadcastParallelData((char*)keys,sizeof(int)*keys_len,newsockfd);
int offsets_len=0;
broadcastParallelData((char*)&offsets_len,sizeof(int),newsockfd);
int* offsets=new int[offsets_len];
broadcastParallelData((char*)offsets,sizeof(int)*offsets_len,newsockfd);
int flips_len=0;
broadcastParallelData((char*)&flips_len,sizeof(int),newsockfd);
int* flips=new int[flips_len];
broadcastParallelData((char*)flips,sizeof(int)*flips_len,newsockfd);
int values_len=0;
broadcastParallelData((char*)&values_len,sizeof(int),newsockfd);
double* values=new double[values_len];
broadcastParallelData((char*)values,sizeof(double)*values_len,newsockfd);
int ackn;
broadcastParallelData((char*)&ackn,sizeof(int),newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->forwardVelocities(keys,keys_len,offsets,offsets_len,flips,flips_len,values,values_len,ackn);
  #endif		  
} 
void invoker_iterateInner(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->iterateInner();
  
}


void parallel_master_invoker_iterateInner(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->iterateInner();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_iterateInner(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->iterateInner();
  #endif		  
} 
void invoker_iterateBoundary(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->iterateBoundary();
  
}


void parallel_master_invoker_iterateBoundary(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->iterateBoundary();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_iterateBoundary(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->iterateBoundary();
  #endif		  
} 
void invoker_closeNSProfiles(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->closeNSProfiles();
  
}


void parallel_master_invoker_closeNSProfiles(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->closeNSProfiles();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_closeNSProfiles(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->closeNSProfiles();
  #endif		  
} 
void invoker_printNSProfiles(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->printNSProfiles();
  
}


void parallel_master_invoker_printNSProfiles(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->printNSProfiles();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_printNSProfiles(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->printNSProfiles();
  #endif		  
} 
void invoker_printNSPressure(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->printNSPressure();
  
}


void parallel_master_invoker_printNSPressure(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->printNSPressure();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_printNSPressure(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->printNSPressure();
  #endif		  
} 
void invoker_setVelocities(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int velocitiesX_len=0;
readData((char*)&velocitiesX_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocitiesX=new double[velocitiesX_len];
readData((char*)velocitiesX,sizeof(double)*velocitiesX_len,rcvBuffer,newsockfd,buffer_size);
int velocitiesY_len=0;
readData((char*)&velocitiesY_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocitiesY=new double[velocitiesY_len];
readData((char*)velocitiesY,sizeof(double)*velocitiesY_len,rcvBuffer,newsockfd,buffer_size);
int velocitiesZ_len=0;
readData((char*)&velocitiesZ_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocitiesZ=new double[velocitiesZ_len];
readData((char*)velocitiesZ,sizeof(double)*velocitiesZ_len,rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->setVelocities(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
  delete [] velocitiesX;
delete [] velocitiesY;
delete [] velocitiesZ;

}


void parallel_master_invoker_setVelocities(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int velocitiesX_len=0;
readData((char*)&velocitiesX_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocitiesX=new double[velocitiesX_len];
readData((char*)velocitiesX,sizeof(double)*velocitiesX_len,rcvBuffer,newsockfd,buffer_size);
int velocitiesY_len=0;
readData((char*)&velocitiesY_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocitiesY=new double[velocitiesY_len];
readData((char*)velocitiesY,sizeof(double)*velocitiesY_len,rcvBuffer,newsockfd,buffer_size);
int velocitiesZ_len=0;
readData((char*)&velocitiesZ_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* velocitiesZ=new double[velocitiesZ_len];
readData((char*)velocitiesZ,sizeof(double)*velocitiesZ_len,rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&velocitiesX_len,sizeof(int),communicator);
broadcastParallelData((char*)velocitiesX,sizeof(double)*velocitiesX_len,communicator);
broadcastParallelData((char*)&velocitiesY_len,sizeof(int),communicator);
broadcastParallelData((char*)velocitiesY,sizeof(double)*velocitiesY_len,communicator);
broadcastParallelData((char*)&velocitiesZ_len,sizeof(int),communicator);
broadcastParallelData((char*)velocitiesZ,sizeof(double)*velocitiesZ_len,communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->setVelocities(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_setVelocities(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int velocitiesX_len=0;
broadcastParallelData((char*)&velocitiesX_len,sizeof(int),newsockfd);
double* velocitiesX=new double[velocitiesX_len];
broadcastParallelData((char*)velocitiesX,sizeof(double)*velocitiesX_len,newsockfd);
int velocitiesY_len=0;
broadcastParallelData((char*)&velocitiesY_len,sizeof(int),newsockfd);
double* velocitiesY=new double[velocitiesY_len];
broadcastParallelData((char*)velocitiesY,sizeof(double)*velocitiesY_len,newsockfd);
int velocitiesZ_len=0;
broadcastParallelData((char*)&velocitiesZ_len,sizeof(int),newsockfd);
double* velocitiesZ=new double[velocitiesZ_len];
broadcastParallelData((char*)velocitiesZ,sizeof(double)*velocitiesZ_len,newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->setVelocities(velocitiesX,velocitiesX_len,velocitiesY,velocitiesY_len,velocitiesZ,velocitiesZ_len);
  #endif		  
} 
void invoker_solveOneTimestepPhaseTwo(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->solveOneTimestepPhaseTwo();
  
}


void parallel_master_invoker_solveOneTimestepPhaseTwo(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->solveOneTimestepPhaseTwo();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_solveOneTimestepPhaseTwo(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->solveOneTimestepPhaseTwo();
  #endif		  
} 
void invoker_solveOneTimestepPhaseOne(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->solveOneTimestepPhaseOne();
  
}


void parallel_master_invoker_solveOneTimestepPhaseOne(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->solveOneTimestepPhaseOne();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_solveOneTimestepPhaseOne(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->solveOneTimestepPhaseOne();
  #endif		  
} 
void invoker_solve(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  
  ((cca::cfd::NSImplementation*)*ref)->solve();
  
}


void parallel_master_invoker_solve(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  
  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  
  #endif
  ((cca::cfd::NSImplementation*)*ref)->solve();
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_solve(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  
  ((cca::cfd::NSImplementation*)*ref)->solve();
  #endif		  
} 
void invoker_setupCommForLBRegion(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int startOfRegion_len=0;
readData((char*)&startOfRegion_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* startOfRegion=new int[startOfRegion_len];
readData((char*)startOfRegion,sizeof(int)*startOfRegion_len,rcvBuffer,newsockfd,buffer_size);
int endOfRegion_len=0;
readData((char*)&endOfRegion_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* endOfRegion=new int[endOfRegion_len];
readData((char*)endOfRegion,sizeof(int)*endOfRegion_len,rcvBuffer,newsockfd,buffer_size);
int commids_len=0;
readData((char*)&commids_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
char (* commids)[255]=new char[commids_len][255];
std::string* commids_data=new std::string[commids_len];
for(int i=0;i<commids_len;i++){
	int commids_data_len=0;
	readData((char*)&commids_data_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
	readData((char*)commids[i],commids_data_len<255?commids_data_len:255,rcvBuffer,newsockfd,buffer_size);
	commids[i][commids_data_len]='\0';
	commids_data[i]=commids[i];
}

  ((cca::cfd::NSImplementation*)*ref)->setupCommForLBRegion(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids_data,commids_len);
  delete [] startOfRegion;
delete [] endOfRegion;
delete [] commids;

}


void parallel_master_invoker_setupCommForLBRegion(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int startOfRegion_len=0;
readData((char*)&startOfRegion_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* startOfRegion=new int[startOfRegion_len];
readData((char*)startOfRegion,sizeof(int)*startOfRegion_len,rcvBuffer,newsockfd,buffer_size);
int endOfRegion_len=0;
readData((char*)&endOfRegion_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
int* endOfRegion=new int[endOfRegion_len];
readData((char*)endOfRegion,sizeof(int)*endOfRegion_len,rcvBuffer,newsockfd,buffer_size);
int commids_len=0;
readData((char*)&commids_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
char (* commids)[255]=new char[commids_len][255];
std::string* commids_data=new std::string[commids_len];
for(int i=0;i<commids_len;i++){
	int commids_data_len=0;
	readData((char*)&commids_data_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
	readData((char*)commids[i],commids_data_len<255?commids_data_len:255,rcvBuffer,newsockfd,buffer_size);
	commids[i][commids_data_len]='\0';
	commids_data[i]=commids[i];
}

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&startOfRegion_len,sizeof(int),communicator);
broadcastParallelData((char*)startOfRegion,sizeof(int)*startOfRegion_len,communicator);
broadcastParallelData((char*)&endOfRegion_len,sizeof(int),communicator);
broadcastParallelData((char*)endOfRegion,sizeof(int)*endOfRegion_len,communicator);
broadcastParallelData((char*)&commids_len,sizeof(int),communicator);
for(int i=0;i<commids_len;i++){
	int commids_data_len=commids_data[i].size();
	broadcastParallelData((char*)&commids_data_len,sizeof(int),communicator);
	broadcastParallelData((char*)commids[i],commids_data_len<255?commids_data_len:255,communicator);
}

  #endif
  ((cca::cfd::NSImplementation*)*ref)->setupCommForLBRegion(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids_data,commids_len);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_setupCommForLBRegion(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int startOfRegion_len=0;
broadcastParallelData((char*)&startOfRegion_len,sizeof(int),newsockfd);
int* startOfRegion=new int[startOfRegion_len];
broadcastParallelData((char*)startOfRegion,sizeof(int)*startOfRegion_len,newsockfd);
int endOfRegion_len=0;
broadcastParallelData((char*)&endOfRegion_len,sizeof(int),newsockfd);
int* endOfRegion=new int[endOfRegion_len];
broadcastParallelData((char*)endOfRegion,sizeof(int)*endOfRegion_len,newsockfd);
int commids_len=0;
broadcastParallelData((char*)&commids_len,sizeof(int),newsockfd);
char (* commids)[255]=new char[commids_len][255];
std::string * commids_data = new std::string[commids_len];
for(int i=0;i<commids_len;i++){
	int commids_data_len=0;
	broadcastParallelData((char*)&commids_data_len,sizeof(int),newsockfd);
	broadcastParallelData((char*)commids[i],commids_data_len<255?commids_data_len:255,newsockfd);
	commids[i][commids_data_len]='\0';
	commids_data[i]=commids[i];
}

  ((cca::cfd::NSImplementation*)*ref)->setupCommForLBRegion(startOfRegion,startOfRegion_len,endOfRegion,endOfRegion_len,commids_data,commids_len);
  #endif		  
} 
void invoker_setup(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
  int inputScenario_str_len=0;
readData((char*)&inputScenario_str_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
char* inputScenario=new char[inputScenario_str_len];
readData((char*)inputScenario,inputScenario_str_len,rcvBuffer,newsockfd,buffer_size);

  ((cca::cfd::NSImplementation*)*ref)->setup(inputScenario);
  
}


void parallel_master_invoker_setup(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer
#ifdef Parallel
,MPI_Comm communicator, int methodId
#endif
){
 	
  int inputScenario_str_len=0;
readData((char*)&inputScenario_str_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
char* inputScenario=new char[inputScenario_str_len];
readData((char*)inputScenario,inputScenario_str_len,rcvBuffer,newsockfd,buffer_size);

  #ifdef Parallel
  broadcastParallelData((char*)&methodId,sizeof(int),communicator);
  broadcastParallelData((char*)&inputScenario_str_len,sizeof(int),communicator);
broadcastParallelData((char*)inputScenario,inputScenario_str_len,communicator);

  #endif
  ((cca::cfd::NSImplementation*)*ref)->setup(inputScenario);
  //int ack=1;
  //sendData((char*)&ack,sizeof(int),sendBuffer,newsockfd,buffer_size);
}
void parallel_worker_invoker_setup(void** ref
#ifdef Parallel
,MPI_Comm newsockfd
#endif
){
  #ifdef Parallel
  int inputScenario_str_len=0;
broadcastParallelData((char*)&inputScenario_str_len,sizeof(int),newsockfd);
char* inputScenario=new char[inputScenario_str_len];
broadcastParallelData((char*)inputScenario,inputScenario_str_len,newsockfd);

  ((cca::cfd::NSImplementation*)*ref)->setup(inputScenario);
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
	const char* network_interface = getenv("CCA_CFD_NS_NET_INTERFACE");
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
					res<<std::string(inet_ntoa(((struct sockaddr_in*) &req.ifr_addr)->sin_addr))<<":"<<daemon_args.daemon_port;
					
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
     invokers[22]=invoker_disconnect_client_dispatcher_lb;
invokers[21]=invoker_connect_client_dispatcher_lb;
invokers[20]=invoker_create_client_port_for_lb;
invokers[65]=parallel_master_invoker_retrievePressureCopy;
invokers[64]=invoker_retrievePressureCopy;
invokers[63]=parallel_master_invoker_retrieveJacobianCopy;
invokers[62]=invoker_retrieveJacobianCopy;
invokers[61]=parallel_master_invoker_retrieveVelocitiesCopy;
invokers[60]=invoker_retrieveVelocitiesCopy;
invokers[59]=parallel_master_invoker_retrieveVelocitiesSize;
invokers[58]=invoker_retrieveVelocitiesSize;
invokers[57]=parallel_master_invoker_retrieveTimestep;
invokers[56]=invoker_retrieveTimestep;
invokers[55]=parallel_master_invoker_iterate;
invokers[54]=invoker_iterate;
invokers[96]=parallel_master_invoker_syncr;
invokers[95]=invoker_syncr;
invokers[94]=parallel_master_invoker_plot;
invokers[93]=invoker_plot;
invokers[92]=parallel_master_invoker_forwardVelocities;
invokers[91]=invoker_forwardVelocities;
invokers[90]=parallel_master_invoker_iterateInner;
invokers[89]=invoker_iterateInner;
invokers[88]=parallel_master_invoker_iterateBoundary;
invokers[87]=invoker_iterateBoundary;
invokers[86]=parallel_master_invoker_closeNSProfiles;
invokers[85]=invoker_closeNSProfiles;
invokers[84]=parallel_master_invoker_printNSProfiles;
invokers[83]=invoker_printNSProfiles;
invokers[82]=parallel_master_invoker_printNSPressure;
invokers[81]=invoker_printNSPressure;
invokers[80]=parallel_master_invoker_setVelocities;
invokers[79]=invoker_setVelocities;
invokers[78]=parallel_master_invoker_solveOneTimestepPhaseTwo;
invokers[77]=invoker_solveOneTimestepPhaseTwo;
invokers[76]=parallel_master_invoker_solveOneTimestepPhaseOne;
invokers[75]=invoker_solveOneTimestepPhaseOne;
invokers[74]=parallel_master_invoker_solve;
invokers[73]=invoker_solve;
invokers[72]=parallel_master_invoker_setupCommForLBRegion;
invokers[71]=invoker_setupCommForLBRegion;
invokers[70]=parallel_master_invoker_setup;
invokers[69]=invoker_setup;

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
     parallel_worker_invokers[64]=parallel_worker_invoker_retrievePressureCopy;
parallel_worker_invokers[62]=parallel_worker_invoker_retrieveJacobianCopy;
parallel_worker_invokers[60]=parallel_worker_invoker_retrieveVelocitiesCopy;
parallel_worker_invokers[58]=parallel_worker_invoker_retrieveVelocitiesSize;
parallel_worker_invokers[56]=parallel_worker_invoker_retrieveTimestep;
parallel_worker_invokers[54]=parallel_worker_invoker_iterate;
parallel_worker_invokers[95]=parallel_worker_invoker_syncr;
parallel_worker_invokers[93]=parallel_worker_invoker_plot;
parallel_worker_invokers[91]=parallel_worker_invoker_forwardVelocities;
parallel_worker_invokers[89]=parallel_worker_invoker_iterateInner;
parallel_worker_invokers[87]=parallel_worker_invoker_iterateBoundary;
parallel_worker_invokers[85]=parallel_worker_invoker_closeNSProfiles;
parallel_worker_invokers[83]=parallel_worker_invoker_printNSProfiles;
parallel_worker_invokers[81]=parallel_worker_invoker_printNSPressure;
parallel_worker_invokers[79]=parallel_worker_invoker_setVelocities;
parallel_worker_invokers[77]=parallel_worker_invoker_solveOneTimestepPhaseTwo;
parallel_worker_invokers[75]=parallel_worker_invoker_solveOneTimestepPhaseOne;
parallel_worker_invokers[73]=parallel_worker_invoker_solve;
parallel_worker_invokers[71]=parallel_worker_invoker_setupCommForLBRegion;
parallel_worker_invokers[69]=parallel_worker_invoker_setup;

     while(methodId!=1){
          broadcastParallelData((char*)&methodId,sizeof(int),clientfd);
          parallel_worker_invokers[methodId-1](&ref,clientfd);
     }
    
     
}

#endif

#ifdef Parallel
void* parallel_deamon_run(void* daemon_args){
	parallel_worker_loop(((CCA_CFD_NS_arg*)daemon_args)->ref,((CCA_CFD_NS_arg*)daemon_args)->communicator);
}
#endif
 
#ifdef _WIN32
DWORD WINAPI server_deamon_run(void* daemon_args){
      SOCKET clientfd;
#else  
void* server_deamon_run(void* daemon_args){
      int clientfd=0;
#endif
      accept_on_server(((CCA_CFD_NS_arg*)daemon_args)->daemon_serverfd,clientfd);
      std::cout<<"server accepted"<<std::endl;
      socket_worker_loop(
      	((CCA_CFD_NS_arg*)daemon_args)->ref,
      	clientfd,
      	((CCA_CFD_NS_arg*)daemon_args)->buffer_size
#ifdef Parallel
		,((CCA_CFD_NS_arg*)daemon_args)->communicator
#endif      	
      	);
}
void startMPIDaemon(CCA_CFD_NS_arg& arg){
#ifdef Parallel	 
int rank = -1;
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
if(rank>0){
	 parallel_deamon_run(&arg);
}
#endif     
}

void startSocketDaemons(CCA_CFD_NS_arg& arg){
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

void initialiseENV(CCA_CFD_NS_arg& arg){
          const char* client_port = getenv("CCA_CFD_NS_PORT");
          const char* daemon_port = getenv("CCA_CFD_NS_DAEMON_PORT");
          const char* buffer_size = getenv("CCA_CFD_NS_BUFFER_SIZE");
          const char* hostname = getenv("CCA_CFD_NS_HOSTNAME");
          const char* java_client_flag = getenv("CCA_CFD_NS_JAVA");
          const char* number_of_workers = getenv("CCA_CFD_NS_WORKERS");
          const char* xmlFile = getenv("CCA_CFD_NS_XML");
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

void initialiseXMLDaemons(CCA_CFD_NS_arg& arg){
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
          
           invokers[22]=invoker_disconnect_client_dispatcher_lb;
invokers[21]=invoker_connect_client_dispatcher_lb;
invokers[20]=invoker_create_client_port_for_lb;

          for(tinyxml2::XMLElement* e = root->FirstChildElement("component"); e != NULL; e = e->NextSiblingElement("component"))
          {
            if(strcmp(e->Attribute("name"),"cca.cfd.NS")==0){
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
void initialiseXMLConnections(CCA_CFD_NS_arg& arg){
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
          
           invokers[22]=invoker_disconnect_client_dispatcher_lb;
invokers[21]=invoker_connect_client_dispatcher_lb;
invokers[20]=invoker_create_client_port_for_lb;

          for(tinyxml2::XMLElement* e = root->FirstChildElement("component"); e != NULL; e = e->NextSiblingElement("component"))
          {
            if(strcmp(e->Attribute("name"),"cca.cfd.NS")==0){
                 int port;
                 std::stringstream str;
                 e->QueryIntAttribute("port",&port);
                 str<<(port+1);
                // arg.daemon_port=str.str();
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

void initialiseParallel(CCA_CFD_NS_arg& arg){
#ifdef Parallel
     int rank = -1 ;
     int comm_size;
     std::stringstream st;

     MPI_Comm_rank(MPI_COMM_WORLD,&rank);
     MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
     int port=atoi(arg.daemon_port.c_str())+rank;
     st<<port;
     arg.communicator = MPI_COMM_WORLD;
     arg.daemon_port=st.str();
     if(rank>0){
          arg.java_client_flag=false;
          arg.joinable=false;
     }
      
#endif
}
extern "C"{

#ifdef _WIN32
void INITIALISE(CCA_CFD_NS_arg& arg){
#else
void initialise_(CCA_CFD_NS_arg& arg,bool joinable){
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
     
     initialiseXMLDaemons(arg);
     initialiseParallel(arg);
     

   invoker_create_instance(&arg.ref,0,0,NULL,NULL
#ifdef Parallel
   ,MPI_COMM_WORLD,0 	
#endif   
   );
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
void DESTROY(CCA_CFD_NS_arg& arg){
#else
void destroy_(CCA_CFD_NS_arg& arg){
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
void SOCKET_LOOP(CCA_CFD_NS_arg& arg){
#else
void socket_loop_(CCA_CFD_NS_arg& arg,bool joinable){
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





