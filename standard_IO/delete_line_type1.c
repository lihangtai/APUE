#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]){

    if(argc <4){
        fprintf(stderr, "please follow the pattern:./delete [obj] [des] [line number] \n");
        exit(-1);
    }

    FILE *fileptr, *tempfileptr;
    char *line = NULL;
    size_t size = 0;
    int line_number = 0;
    int line_to_delete = atoi(argv[3]);

    fileptr = fopen(argv[1], "r");
    if(fileptr == NULL){
        perror("fopen");
        return -1;
    }

    tempfileptr = fopen(argv[2], "w");
    if(tempfileptr == NULL){
        perror("fopen");
        return -1;
    }

    while(getline(&line, &size, fileptr) != -1){
        
        line_number++;

        if(line_number != line_to_delete){
            fputs(line, tempfileptr);
        }
    }


    fclose(fileptr);
    fclose(tempfileptr);

    return 0;
}


