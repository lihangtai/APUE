#include <asm-generic/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <errno.h>
#include <time.h>
#include <arpa/inet.h>

#include "proto.h"

#define BACKLOG 200
#define BUFSIZE 1024
#define IPSTRSIZE 16
#define MAX_PROC 4

static void server_loop(int sd);

static void serverjob(int sd, const struct sockaddr_in* paddr)
{
	char buf[BUFSIZE] = {0};
	int len = 0;
	// // len = snprintf(buf, BUFSIZE, FMT_STAMP, (long long)time(NULL));
	// if (len < 0)
	// {
	// 	perror("snprintf()");
	// 	exit(1);
	// }
	strcpy(buf, "the info from server");

	while (send(sd, buf, BUFSIZE, 0) < 0)
	{
		if (errno == EINTR)
			continue;
		perror("send()");
		exit(1);
	}
    printf("send success\n");
    
    char buffer[BUFSIZE];

    int received_size = recv(sd, buffer, BUFSIZE, 0);
	printf("%d\n",received_size);
    if (received_size < 0) {
        perror("recv failed");
    } else if (received_size == 0) {
        printf("Server disconnected.\n");
    } else {
        printf("Received: %s\n", buffer);
    }
    

    
	return;
}

int main(int argc, char** argv)
{
	int sd = 0;
	struct sockaddr_in laddr = {0};
	int val = 0;	
	
	// 1st. get socket fd
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0)
	{
		perror("socket()");
		exit(1);
	}

	val = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0)
	{
		perror("setsockopt()");
		exit(1);
	}
	// 2nd. initialize local sockaddr, and bind it to socket fd
	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(SERVERPORT));
	// laddr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	//	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
	laddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sd, (void*)&laddr, sizeof(laddr)) < 0)
	{
		perror("bind()");
		exit(1);
	}

	// 3rd. switch the socket fd to passive listening mode
	if ( listen(sd, BACKLOG) < 0 )
	{
		perror("listen()");
		exit(1);
	}

	for (int i = 0; i < MAX_PROC; ++i)
	{
		int pid = fork();
		if (pid < 0)
		{
			perror("fork()");
			exit(1);
		}
		else if (pid == 0)
		{
			
			printf("created the service %d pid:%d\n",i, getpid());
			server_loop(sd);
			
			exit(0);
		}
	}

	for (int i = 0; i < MAX_PROC; ++i)
	{
		wait(NULL);
	}
}

static void server_loop(int sd)
{
	// caller must initialize it to contain the size (in bytes) of the raddr
	char ipstr[IPSTRSIZE] = {0};
	struct sockaddr_in raddr;
	socklen_t raddr_len;
	raddr_len = sizeof(raddr);
	while (1)
	{
		int newsd = 0;
		// 4th. Wait for accepting a client connection.
		// accept atomically to receive a connection.
        
		newsd = accept(sd, (void*)&raddr, &raddr_len);
		if (newsd < 0)
		{
			if (errno == EINTR)
				continue;
			perror("accept()");
			exit(1);
		}
        printf("connect successful\n");
		// 5th. Do server. Sending or receiving data.
		serverjob(newsd, &raddr);
		inet_ntop(AF_INET, &raddr.sin_addr, ipstr,  raddr_len);
		printf("[%d]Connection from: %s:%d\n", getpid(), ipstr, ntohs(raddr.sin_port));
		// 6th. Close the newly allocated socket fd.
		close(newsd);
	}
	// never return normally.
	// close(sd);
}