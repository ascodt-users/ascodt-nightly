#include "de/tum/ExampleComponentC2CxxProxy.h"
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
	
#include "de/tum/ExampleComponentImplementation.h"

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
&sockfd
){


#ifdef _WIN32
		 WSADATA wsaData;
		 int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	     assert (iResult == 0);
#endif
          struct addrinfo hints;
	      struct addrinfo *result = NULL;
         

          bzero(&hints, sizeof(hints));
          hints.ai_family = AF_INET;
          hints.ai_socktype = SOCK_STREAM;
		  hints.ai_protocol = IPPROTO_TCP;
		  hints.ai_flags = AI_PASSIVE;
          getaddrinfo(NULL, port, &hints, &result);
		  
		  sockfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
          assert (sockfd>=0);
          bind(sockfd, result->ai_addr, (int)result->ai_addrlen);
		  
          listen(sockfd,5);
         
        
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

void invoker_create_instance(void** ref,int,int,char*,char*){
     *ref = new de::tum::ExampleComponentImplementation();
}

void invoker_destroy_instance(void** ref,int,int,char*,char*){
      delete ((de::tum::ExampleComponentImplementation*)*ref);
  
}
void invoker_reset(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  
  ((de::tum::ExampleComponentImplementation*)*ref)->reset();
  
}
void invoker_bar(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  int data_len=0;
readData((char*)&data_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* data=new double[data_len];
readData((char*)data,sizeof(double)*data_len,rcvBuffer,newsockfd,buffer_size);

  ((de::tum::ExampleComponentImplementation*)*ref)->bar(data,data_len);
  sendData((char*)&data_len,sizeof(int),sendBuffer,newsockfd,buffer_size);
sendData((char*)data,sizeof(double)*data_len,sendBuffer,newsockfd,buffer_size);
delete [] data;

}
void invoker_foo(void** ref,int newsockfd, int buffer_size,char* rcvBuffer, char* sendBuffer){
  int data_len=0;
readData((char*)&data_len,sizeof(int),rcvBuffer,newsockfd,buffer_size);
double* data=new double[data_len];
readData((char*)data,sizeof(double)*data_len,rcvBuffer,newsockfd,buffer_size);

  ((de::tum::ExampleComponentImplementation*)*ref)->foo(data,data_len);
  delete [] data;

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





void socket_worker_loop(void* ref,
#ifdef _WIN32
SOCKET
#else
int
#endif
clientfd,int bufferSize){
     char *sendBuffer=new char[bufferSize];
     char *rcvBuffer=new char[bufferSize];
     void (*invokers[43])(void**,int,int,char*,char*);
     invokers[0]=invoker_create_instance;
     invokers[1]=invoker_destroy_instance;
     int methodId=0;
     invokers[11]=invoker_reset;
invokers[10]=invoker_bar;
invokers[9]=invoker_foo;

     while(methodId!=1){
          readData((char*)&methodId,sizeof(int),rcvBuffer,clientfd,bufferSize);
          invokers[methodId](&ref,clientfd,bufferSize,rcvBuffer,sendBuffer);
     }
     delete [] sendBuffer;
     delete [] rcvBuffer;
#ifdef _WIN32
     closesocket(clientfd);
#else
     close(clientfd);    
#endif    
     
}


#ifdef _WIN32
DWORD WINAPI server_deamon_run(void* daemon_args){
      SOCKET clientfd;
#else  
void* server_deamon_run(void* daemon_args){
      int clientfd=0;
#endif
      
      accept_on_server(((EXAMPLECOMPONENT_arg*)daemon_args)->daemon_serverfd,clientfd);
      std::cout<<"server accepted"<<std::endl;
      socket_worker_loop(((EXAMPLECOMPONENT_arg*)daemon_args)->ref,clientfd,((EXAMPLECOMPONENT_arg*)daemon_args)->buffer_size);
}
extern "C"{

#ifdef _WIN32
void INITIALISE(EXAMPLECOMPONENT_arg& arg){
#else
void initialise_(EXAMPLECOMPONENT_arg& arg){
#endif
   const char* client_port = getenv("EXAMPLECOMPONENT_PORT"); 
   const char* daemon_port = getenv("EXAMPLECOMPONENT_DAEMON_PORT");
   const char* buffer_size = getenv("EXAMPLECOMPONENT_BUFFER_SIZE");
   const char* hostname = getenv("EXAMPLECOMPONENT_HOSTNAME");
   const char* java_client_flag = getenv("EXAMPLECOMPONENT_JAVA");
   arg.buffer_size = (buffer_size!=NULL)?atoi(buffer_size):4096;
   arg.hostname = (hostname!=NULL)?hostname:"localhost";
   arg.client_port = (client_port!=NULL)?client_port:"50000";
   arg.daemon_port = (daemon_port!=NULL)?daemon_port:"50001";
   arg.java_client_flag=(java_client_flag!=NULL&&strcmp(java_client_flag,"off")==0)?false:true;
   
   invoker_create_instance(&arg.ref,0,0,NULL,NULL);
   if(arg.java_client_flag)         
     open_client(arg.hostname,client_port,arg.java_serverfd,arg.java_clientfd);
   bind_server(arg.daemon_port,arg.daemon_serverfd);
   for(int i=0;i<10;i++){
#ifdef _WIN32    
     CreateThread(NULL, 0,server_deamon_run, &arg, 0, NULL);
#else     
     pthread_t task;
     pthread_create(&task,NULL,server_deamon_run,&arg);
#endif
   } 
}

#ifdef _WIN32
void DESTROY(EXAMPLECOMPONENT_arg& arg){
#else
void destroy_(EXAMPLECOMPONENT_arg& arg){
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
void SOCKET_LOOP(EXAMPLECOMPONENT_arg& arg){
#else
void socket_loop_(EXAMPLECOMPONENT_arg& arg){
#endif
  if(arg.java_client_flag)       
     socket_worker_loop(arg.ref,arg.java_clientfd,arg.buffer_size);
}

#ifdef _WIN32
void MAIN_LOOP(){
#else
void main_loop_(){
#endif
  

  EXAMPLECOMPONENT_arg daemon_args;
#ifdef _WIN32
  INITIALISE(daemon_args);
  DESTROY(daemon_args);     
#else  
  initialise_(daemon_args);
  socket_loop_(daemon_args);
  destroy_(daemon_args);  
#endif
  
}




}

