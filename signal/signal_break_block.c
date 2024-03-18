#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

 static void int_handler(int s){
    write(1,"!", 1 );
 }

 int main(){
    int i;
    signal(SIGINT, int_handler);

    for(i=0;i<100;i++){
        write(1,"*", 1);
        sleep(1);
    }
    exit(0);
 }
