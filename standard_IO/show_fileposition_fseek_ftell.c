#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    
    if(argc < 2){
        fprintf(stdout , "error\n");
        exit(-1);
    }

    FILE *fd;
    fd = fopen(argv[1], "r");
    if( fd == NULL){
        perror("open failed\n");
        fclose(fd);
        exit(-1);
    }

    fseek(fd,0,SEEK_END);
    fprintf(stdout,"%ld", ftell(fd));
    fclose(fd);
    return 0;
}
