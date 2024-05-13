#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "proto.h"


int main(){
    key_t key;
    int msgid;
    struct msg_st sbuf;
    srand(time(NULL));
    key = ftok(KEYPATH, KEYPROJ);
    printf("key = %d\n", key);
    if(key <0){
        perror("ftok()");
        exit(1);
    }
    msgid = msgget(key, 0);
    printf("msgid = %d\n", msgid);
    if(msgid <0){
        perror("msgget()");
        exit(0);
    }
    sbuf.mtype = MSGTYPE;
    sbuf.chinese = rand()%100;
    sbuf.math = rand()%100;
    strcpy(sbuf.name, "zhangsan");

    if(msgsnd(msgid, &sbuf, sizeof(sbuf)-sizeof(long), 0)< 0){

        perror("msgsnd()");
        exit(0);

    }

    puts("ok!");

    exit(0);

}