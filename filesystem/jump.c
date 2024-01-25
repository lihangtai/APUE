#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;
static void c(){
    printf("%s:c() Begin. \n", __FUNCTION__ );

    printf("%s:c() End. \n", __FUNCTION__ );
    printf("%s:c() jump now. \n", __FUNCTION__ );
    longjmp(env,6);

}
static void b(){
    printf("%s:Begin. \n", __FUNCTION__ );
    printf("%s:call c(). \n", __FUNCTION__ );
    c();
    printf("%s:c() returned. \n", __FUNCTION__ );
    printf("%s:End. \n", __FUNCTION__ );

}
static void a(){
    printf("%s:Begin. \n", __FUNCTION__ );
    printf("%s:call b(). \n", __FUNCTION__ );
    b();
    printf("%s:b() returned. \n", __FUNCTION__ );
    printf("%s:End. \n", __FUNCTION__ );

}
int main(){
    int ret;

    printf("%s:Begin. \n", __FUNCTION__ );
    printf("%s:call a(). \n", __FUNCTION__ );
    ret = setjmp(env);
    if(ret == 0){
        a();
        printf("%s:a() returned. \n", __FUNCTION__ );

    }
    else{
        printf("%s: jump back here with code %d\n", __FUNCTION__, ret );
    }

    printf("%s:End. \n", __FUNCTION__ );

}

