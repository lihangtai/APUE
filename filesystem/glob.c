#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <glob.h>
#include <string.h>

#define PAT "/etc/a*.conf"

int errfun_c(const char *errpath, int errnum){

    puts(errpath);
    fprintf(stderr,"error msg:%s\n",strerror(errnum));
    return 0;

}
int main(){

    glob_t globres;
    int err,i;

    err = glob(PAT,0,errfun_c,&globres);
    if(err){
        printf("error code= %d\n", err);
        exit(1);
    }
    for(i = 0;i< globres.gl_pathc; i++){
        puts(globres.gl_pathv[i]);
    }

    exit(0);
}
