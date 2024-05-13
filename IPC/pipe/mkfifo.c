#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE 1024
#define PATHNAME "/tmp/myfifo"

int main(void){

    pid_t pid;
    char buf[BUFSIZE];
    int fd = -1;

    if(mkfifo(PATHNAME,0644) < 0){
        perror("mkfifo()");
        exit(0);
    }

    fflush(NULL);
    pid = fork();
    if(pid < 0){
        perror("fork()");
        exit(0);
    }
    else if(pid > 0){

        pid = fork();
        if(pid < 0){
        perror("fork()");
        exit(0);}

        if(pid >0){
            exit(0);
        }
        else{
            fd = open(PATHNAME,O_RDWR);
            if(fd < 0  ){
                perror("open");
                exit(1);
            }
            ssize_t len = write(fd,   "hello world", 12);
            if(len < 0){
                perror("write");
                exit(1);
            }
            sleep(1);
            read(fd, buf, BUFSIZE);
            puts(buf);
            close(fd);
            exit(0);
        }
    }
    else{
        fd = open(PATHNAME,O_RDWR);
        if(fd < 0  ){
            perror("open");
            exit(1);
        }
        ssize_t len = read(fd,buf,BUFSIZE);
        if(len < 0){
            perror("read");
            exit(1);
        }
        fprintf(stdout, "%s\n", buf);
        ssize_t len1 = write(fd,   "hello world", 12);
            if(len1 < 0){
                perror("write");
                exit(1);
            }
        close(fd);
        exit(0);

    }

}