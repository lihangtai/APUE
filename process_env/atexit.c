#include <stdio.h>
#include <stdlib.h>

static void f1(void){

    puts("f1 runing!");
}

static int f2(void){
    puts("f2 runing!");
    return 1;

}
int main(){

    puts("begining");

    atexit(f1);
    atexit(f2);

    puts("end");

    exit(0);

}

