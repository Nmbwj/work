#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main()
{
	//creating a socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);// it is for IPv4 indicated by AF_INET, and also SOCK_STREAM implies TCP.
	
	//specifiying destination information
	struct sockaddr_in dest;
	memset(&dest, 0, sizeof(struct sockaddr_in));
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("192.168.3.182");
	dest.sin_port = htons(9090);


	// connect to the server
	connect(sockfd, (struct sockadd *)&dest, sizeof(struct sockaddr_in));

	// send data to the server
	// if the firewall on ethswitch side reject data to be transfered as raw TCP packet
	// we can ignore this section of code and close the socket directly.
	char *buffer1 = "Hello Server!\n";
	char *buffer2 = "Hello Again\n";
	write(sockfd, buffer1, strlen(buffer1));
	write(sockfd, buffer2, strlen(buffer2));

	// close the connection
	close(sockfd);
	return 0;
}

