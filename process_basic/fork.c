#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){

    pid_t pid;
    printf("[%d]begin!\n", getpid());
    pid = fork();

    if(pid == 0){
        printf("[%d]I'm son process!\n", getpid());
    }
    else if(pid == -1 ){
        perror("fork failed");
        exit(0);
    }
    else{
        printf("[%d]I'm father process\n", getpid());
    }
    printf("[%d]end!\n", getpid());
    exit(0);
    wait(null);
}
