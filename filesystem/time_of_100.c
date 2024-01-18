#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 1024
int main(int argc, char *argv[]){


    int count = 0 ;
    char buf[SIZE];
    time_t stamp;
    struct tm *tm;
    stamp = time(NULL);
    tm = gmtime(&stamp);
    strftime(buf, SIZE, "Now: %Y-%m-%d",tm);
    puts(buf);

    tm->tm_mday+=100;
   (void)mktime(tm);
    strftime(buf, SIZE, "after 100 day: %Y-%m-%d",tm);
    puts(buf);



return 0;

}
