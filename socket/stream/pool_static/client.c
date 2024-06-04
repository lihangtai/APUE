#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "proto.h"
#define SERVER_IP "127.0.0.1"
int main(int argc, char** argv)
{
	int sd = 0;
	long long stamp;
	// FILE* fp = NULL;
	struct sockaddr_in raddr = {0};


	// 1st. create a stream (TCP) socket.
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	// 2nd. bind can omit
	
	// 3rd. connect to server
	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(atoi(SERVERPORT));
	raddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	if ( connect(sd, (void*)&raddr, sizeof(raddr)) < 0 )
	{
		perror("connect()");
		exit(1);
	}

	char buf[BUFSIZE];
	ssize_t result;
	ssize_t result1;

	while((result = recv(sd, (void *) buf, sizeof(buf), 0 ) <=0)){
		
	if(result == -1){
		perror("recv()");
		close(sd);
		exit(-1);
	}
	if(result == 0){
		printf("server disconnected\n");
	}
			
	
	}

	printf("received: ");
	printf("%s\n", buf);
	
	

	

	char message[BUFSIZE];
	strcpy(message, "this is from client info");

	// while((result1 = send(sd, message, sizeof(message), 0 ))<0){
	// 	perror("send()");
	// 	exit(-1);
	// }
	while (send(sd, message, BUFSIZE, 0) < 0)
	{
		if (errno == EINTR)
			continue;
		perror("send()");
		exit(1);
	}
    printf("send success\n");

	
	printf("send successful\n");

	printf("the communication is over\n");
	close(sd);
	return 0;
	}



