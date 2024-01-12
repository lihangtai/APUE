#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

off_t flen(const char *filename){
    struct stat buf;
    if(stat(filename, &buf) <0){
        perror("fail");
        exit(-1);
    }
    return buf.st_size;

}

int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stdout, "follow the pattern\n");
        exit(-1);

    }
    
    fprintf(stdout, "%ld\n", (long)flen(argv[1]));

}

