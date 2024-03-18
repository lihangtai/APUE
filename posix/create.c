#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
static void *func(void *s){
    puts("thread created\n");
    return NULL;
}
int main(){

    pthread_t tid;
    int err;
    puts("begin\n");
    err = pthread_create(&tid,NULL, func,NULL);
    if(err){
        fprintf(stderr,"pthread_create() %s\n", strerror(err));
    }
    puts("end\n");
    pthread_join(tid,NULL);
    exit(0);
}
