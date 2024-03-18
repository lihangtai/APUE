#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define FNAME "/tmp/out"

static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

static void *thread_add(void *p){
    FILE *fp;
    char linebuf[1024];
    fp = fopen(FNAME, "r+");
    if(fp == NULL){
        perror("fopen  failed\n");
        exit(0);
    }
    pthread_mutex_lock(&mut); 
    fgets(linebuf, 1024,fp);
    fprintf(fp,"%d\n", (atoi(linebuf)+1));
    fclose(fp); 
    pthread_mutex_unlock(&mut);
    pthread_exit(NULL);

}
int main(){

    pthread_t tid[20];
    int err, i;

    for( i = 0; i<=20;i++){

        err = pthread_create(tid+i, NULL,thread_add,NULL );
        if(err){
            fprintf(stderr,"pthread_create error\n");
            exit(1);
        } 

    }
    for(i = 0; i<20;i++){
        pthread_join(tid[i], NULL);
    }

    pthread_mutex_destroy(&mut);

    exit(0); 
}


