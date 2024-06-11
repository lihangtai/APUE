/* client.c */
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include "proto.h"

int main(int argc, char*argv[]) {
    int sd;
    // 对端地址
    struct sockaddr_in raddr;
    FILE *fp;
    long long stamp;
    
	// Usage: ./client IP

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if(sd < 0) {
        perror("socket()");
        exit(1);
    }

    // 对端地址的配置
    raddr.sin_family = AF_INET; // 对端协议
    raddr.sin_port = htons(atoi(SERVERPORT)); // 对端端口
    inet_pton(AF_INET, "127.0.0.1", &raddr.sin_addr); // 对端ip地址

    // 与对端建立连接
    if(connect(sd, (void *)&raddr, sizeof(raddr)) < 0) {
        perror("connect()");
        exit(1);
    }
	// 系统io转换为标准io
    // r+表示打开可读写的文件，且该文件必须存在
    fp = fdopen(sd, "r+");

    if(fp == NULL) {
        perror("dfopen()");
        exit(1);
    }
	
    // 根据数据格式FMT_STAMP从fp中读取数据到stamp中
    if(fscanf(fp, FMT_STAMP, &stamp) < 1) {
        fprintf(stderr, "Bad format!\n");
    } else {
        fprintf(stdout, "stamp = %lld\n", stamp);
    }
	// 按照标准io的方式关闭fp
    fclose(fp);
    exit(0);
}

