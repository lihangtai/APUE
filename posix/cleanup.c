#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static void ret(void *p){
    puts(p);
}
static void *func(void *p){
    puts("thread is working\n");

    pthread_cleanup_push(ret, "cleanup 1");
    pthread_cleanup_push(ret, "cleanup 2");
    pthread_cleanup_push(ret, "cleanup 3");

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);

    pthread_exit(NULL);

}
int main(){

    pthread_t tid;
    int err;

    puts("begin\n");

    err = pthread_create(&tid,NULL,func,NULL);
    if(err){
        fprintf(stderr,"create failed %s\n",strerror(err));
        exit(1);
    }

    pthread_join(tid,NULL);

    puts("end\n");

    exit(0);


}
