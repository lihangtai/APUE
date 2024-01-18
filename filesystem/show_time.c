#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define FNAME "/tmp/out"
#define SIZE 1024
int main(int argc, char *argv[]){

    FILE *fp;
    int count = 0 ;
    char buf[SIZE];
    time_t stamp;
    struct tm *tm;
    fp = fopen(FNAME,"a+");
    if(fp == NULL){
        perror("fopen failed!");
        exit(-1);
    }

    while(fgets(buf, SIZE, fp)!= NULL){

        count++;
    }
    while(1){
        stamp = time(NULL);
        tm = gmtime(&stamp);
        fprintf(fp,"%-4d%d-%d-%d %d:%d:%d\n",++count,\
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,\
        tm->tm_hour, tm->tm_min, tm->tm_sec);
        sleep(1);
        fflush(fp);
    }
    fclose(fp);
    return 0;

}
