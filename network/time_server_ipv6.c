#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#endif
#if defined(_WIN32)
#define ISVALIDSOCKET(s) ((s) != INVALID_SOCKET)
#define CLOSESOCKET(s) closesocket(s)
#define GETSOCKETERRNO() (WSAGetLastError())
#else
#define ISVALIDSOCKET(s) ((s) >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO() (errno)
#endif
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	int line,option=0;
	if (argc != 2)
	{
		printf("Usage: time_server port\n");
		return -1;
	}
	#if defined(_WIN32)
		WSADATA d;
		if (WSAStartup(MAKEWORD(2,2),&d)){
			fprintf(stderr,"Failed to initialize.\n");
			exit(1);
		}
	#endif
	printf("Configuring the Server...\n");
	struct addrinfo hints;
	memset(&hints,0,sizeof hints);
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo *bind_address;

	getaddrinfo(0,*++argv,&hints,&bind_address);

	printf("Creating Socket ...\n");
	SOCKET socket_listen = socket(bind_address->ai_family,bind_address->ai_socktype,bind_address->ai_protocol);

	if(!ISVALIDSOCKET(socket_listen))
	{
		line = __LINE__ ;
		line -= 4;
		fprintf(stderr,"\nError: in file: %s, at line: %d.\nDescription: %s \n",__FILE__,line,strerror(GETSOCKETERRNO()));
		exit(1);
	}

	if(setsockopt(socket_listen,IPPROTO_IPV6,IPV6_V6ONLY,(void *) &option,sizeof option)){
		line = __LINE__ ;
		line -= 1;
		fprintf(stderr,"\nError: in file: %s, at line: %d.\nDescription: %s \n",__FILE__,line,strerror(GETSOCKETERRNO()));
		exit(1);
	}



	
	printf("Binding the server ... \n");
	if(bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen))
	{
		line = __LINE__;
		line -=3;		
		fprintf(stderr,"\nError: in file: %s, at line: %d.\nDescription: %s \n",__FILE__,line,strerror(GETSOCKETERRNO()));
		exit(1);
	}
	freeaddrinfo(bind_address);
	
	printf("Listening for connection ...\n");
	if(listen(socket_listen,10)<0)
	{
		line = __LINE__;
		line -=3;
		fprintf(stderr,"\nError: in file: %s, at line: %d.\nDescription: %s \n",__FILE__,line,strerror(GETSOCKETERRNO()));
		exit(1);
	}

	printf("Waiting for connection ...\n");
	struct sockaddr_storage client_address;
	socklen_t client_len = sizeof client_address;

	SOCKET socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
	if (!ISVALIDSOCKET(socket_client)) {
		line = __LINE__;
		line -=2;		
		fprintf(stderr,"\nError: in file: %s, at line: %d.\nDescription: %s \n",__FILE__,line,strerror(GETSOCKETERRNO()));
		exit(1);
	}
	printf("Client is connected ...\n");
	char address_buffer[100];
	getnameinfo((struct sockaddr*)&client_address, client_len, address_buffer, sizeof address_buffer, 0, 0, NI_NUMERICHOST);
	printf("Client Address: %s\n", address_buffer);
	
	printf("Reading Request ... \n");
	char request[1024];
	int bytes_recieved = recv(socket_client,request,1024,0);
	printf("Recieved %d bytes \n",bytes_recieved);

	printf("________________________________________________\n Content Recived\n%.*s \n_________________________________________________\n",bytes_recieved,request);

	printf("Sending Response ...\n");
	const char * response =
		"HTTP/1.1 200 OK \r\n"
		"Connection: close \r\n"
		"Content-Type: text/plain\r\n\r\n"
		"Local time in EAT : ";
	int bytes_sent = send(socket_client, response, strlen(response),0);
	printf("Sent %d of %d bytes. \n",bytes_sent,(int) strlen(response));
	time_t timer;
	time(&timer);
	char *time_msg = ctime(&timer);
	bytes_sent = send(socket_client, time_msg, strlen(time_msg), 0);
	printf("Sent %d of %d bytes. \n",bytes_sent,(int)strlen(time_msg));

	printf("Closing client socket ... \n");
	CLOSESOCKET(socket_client);

	printf("Closing listener socket ...\n");
	CLOSESOCKET(socket_listen);

	#if defined(_WIN32)
		WSACleanup();
	#endif
	printf("Finished.\n");
	return 0;
}

			
