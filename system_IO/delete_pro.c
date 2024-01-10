#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[])
{
    
    if(argc <3){
        fprintf(stderr, "follow the standard pattern\n");
        return -1;
    }
    FILE *file_read, *file_write;
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    int line_to_delete = atoi(argv[2]);
    long write_pos = 0;

    file_read = fopen(argv[1], "r");
    
    if(file_read == NULL){
        perror("open ");
        return -1;
    }

    file_write = fopen(argv[1], "r+");
    if(file_write == NULL){
    perror("open: ");
    exit(-1);
    }

    while(fgets(line, MAX_LINE_LENGTH, file_read) != NULL){
        
        line_number++;

        if(line_number == line_to_delete-1){

            write_pos = ftell(file_read);
            continue;
        }

        if(line_number > line_to_delete){

            fseek(file_write, write_pos, SEEK_SET);
            fputs(line,file_write);
            fflush(file_write);
            write_pos = ftell(file_write);

        }

//        line_number++;
//        if (line_number != line_to_delete) {
//            fseek(file_write, write_pos, SEEK_SET);
//            fputs(line, file_write);
//            fflush(file_write);
//            write_pos = ftell(file_write);
//        } else {
//            write_pos = ftell(file_write);
//        }
//
    }

   // fseek(file_write, write_pos, SEEK_SET);
    //truncate(argv[1], ftell(file_write));
    ftruncate(fileno(file_write), write_pos);

    fclose(file_read);
    fclose(file_write);
    return 0;
    }
