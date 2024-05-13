#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFSIZE 1024


void main(void){
    int pd[2];
    char buf[BUFSIZE];
    pid_t pid;
    int len;


    if(pipe(pd) < 0 ){
        perror("pipe()");
        exit(1);
    }

    pid = fork();

    if(pid < 0 ){
        perror("fork()");
        exit(1);
    }
    if(pid == 0){
        close(pd[1]);

        len = read(pd[0],buf,BUFSIZE);
        puts(buf);
        close(pd[0]);
        exit(0);

    }
    else{
        close(pd[0]);
        write(pd[1], "hello!",6);

        close(pd[1]);
        wait(NULL);
        exit(0);


    }

}
