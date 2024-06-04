#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "proto.h"

#define IPSTRSIZE 64

int main(void){

    int sd;
    struct sockaddr_in laddr, raddr;

    socklen_t raddr_len;
    struct msg_st rbuf;
    char ipstr[IPSTRSIZE];
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sd <0){
        perror("socket()");
        exit(1);
    }

    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(RCVPROT));
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr.s_addr);
    //// 对"0.0.0.0"的定义是any address.就是说在当前绑定阶段,本机的ip地址是多少,这四个0就会自动换成当前的ip地址

    if(bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) < 0){
        perror("bind()");
        exit(1);
    }
    raddr_len = sizeof(raddr);
    while(1){
        if(recvfrom(sd, &rbuf, sizeof(rbuf), 0, (void *)&raddr, &raddr_len) < 0){
            perror("recvfrom()");
            exit(1);
        }
    
    inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
    printf("__MESSAGE FROM  %s:%d ---\n",ipstr,IPSTRSIZE);
    printf("NAME = %s\n", rbuf.name);
    printf("MATH = %d\n", ntohl(rbuf.math));
    printf("CHINEses = %d\n", ntohl(rbuf.chinese));

    }
    close(sd);
    exit(0);



}