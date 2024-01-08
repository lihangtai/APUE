#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]){

    if(argc <3){
        fprintf(stdout, "please follow the pattern ./my_cp [obj] [des]\n");
        exit(-1);
    }

    FILE *fdi, *fdo;
    char buf[1024];
    size_t indi;
    fdi = fopen(argv[1],"r");
    if(fdi == NULL){
        perror("open failed\n");
        exit(-1);
    }
    
    fdo = fopen(argv[2], "w");
    if(fdo == NULL){
        perror("open failed\n");
        exit(-1);
    }

    while((indi = fread(buf, 1, 100, fdi)) >0){

        fwrite(buf, 1,indi, fdo);
    }

    fclose(fdi);
    fclose(fdo);

    fprintf(stdout, "cp successfully\n");
    exit(0);
    return 0;
}
        

