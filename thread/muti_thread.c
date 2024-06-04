#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LEFT 30000000
#define RIGHT 30000200
#define THRNUM (RIGHT-LEFT+1)

typedef struct{
    int n;
}thr_arg_st;

static void *thr_prime(void *p){

    int i,j,mark;
    i = ((thr_arg_st *)p)->n;
    mark = 1;
    for(j=2;j<i/2;j++){
        if(i%j==0){
            mark=0;
            break;
        }
    }
    if(mark){
        printf("%d is a primer.\n",i);
    
    }
        pthread_exit(p);
}

int main(){

    pthread_t tid[THRNUM];
    thr_arg_st *p;
    void *ret;
    for(int i=LEFT;i<=RIGHT;i++){
        
        p = malloc(sizeof(thr_arg_st));
        if(p ==NULL){
            perror("malloc()");
            exit(0);
        }
        p->n = i;
        int err = pthread_create(&tid[i-LEFT], NULL, thr_prime, p);
        if(err){
            perror("pthread_create()");
            exit(1);
        }

        
    }
    
    for(int i = LEFT;i<=RIGHT;i++){
        pthread_join(tid[i-LEFT], &(ret));
        free(ret);
    }

    exit(0);
}