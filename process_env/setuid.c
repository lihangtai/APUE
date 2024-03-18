#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    if(argc < 3){
        fprintf(stderr, "wrong");
        exit(-1);
    }
    pid_t pid;

    pid = fork();
    if(pid <0){
        perror("fork");
        exit(1);
    }
    if(pid == 0) {
        int res;
        res = setuid(atoi(argv[1]));
        if(res == -1){
                printf("!!!!!!!!!!!!!!!!\n");
                exit(-1);
        }
        execvp(argv[2], argv + 2);
        perror("execvp");
        exit(1);
    }

    wait(NULL);
    exit(0);

    }

