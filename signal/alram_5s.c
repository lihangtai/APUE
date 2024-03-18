#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int loop = 1;

static void handler(int s){
    loop = 0;
}
int main(){

    int64_t count = 0;

    signal(SIGALRM, handler);
    alarm(5);

    while(loop){
        count++;
    }

    printf("%lld\n", count);

    exit(0);
}
