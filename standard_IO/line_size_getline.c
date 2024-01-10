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
    ssize_t size;
    char *line = NULL;
    size_t *n = 0;
    while((size = getline(&line,&n,fd)) != -1){
       
        if(size >0 && line[size -1] == '\n'){
            size--;
        }

        fprintf(stdout, "%ld\n", size);
        
    }
    
    free(line);
    fclose(fd);
    return 0;
}
