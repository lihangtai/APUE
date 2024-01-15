#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){

    if(argc <2){
        fprintf(stdout,"follow the standard pattern\n");
        exit(-1);
    }

    FILE *fp;
    fp = fopen(argv[1], "r+");

    fseek(fp,5ll*1024ll*1024ll*1024ll-1,SEEK_SET);

    //fputc('1',fp);
    
    fclose(fp);
    return 0;
    

}
