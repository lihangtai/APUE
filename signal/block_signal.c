#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

 static void int_handler(int s){
    write(1,"!", 1 );
 }

 int main(){
    int i;
    sigset_t set;
     
    signal(SIGINT, int_handler);
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    for(i= 0;i<100;i++){
    sigprocmask(SIG_BLOCK,&set, NULL );
    for(int j=0;j<5;j++){
        write(1,"*", 1);
        sleep(1);
        }
        fprintf(stdout,"\n");
        sigprocmask(SIG_UNBLOCK, &set, NULL);
    }
    exit(0);

 }
