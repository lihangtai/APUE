#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024
#define B_SIZE 2048
int main(int argc, char *argv[]){


    int c = 0;
    char buf[B_SIZE] = "";
    char fmtstr[SIZE];
    fmtstr[0] = '\0';
    time_t stamp;
    struct tm *tm;  
    FILE *fp =stdout;

    stamp = time(NULL);
    tm = gmtime(&stamp);

    while(1)
    {
        c = getopt(argc, argv, "-H:MSy:md");
        if(c < 0)
            break;

        switch(c)
        {

            case 1:

                fp = fopen(argv[optind-1], "w");
                if(fp == NULL){
                    perror("fopen failed");
                    fp = stdout;
                }

                break;



            case 'H':

                if(strcmp(optarg, "12") == 0)
                    strncat(fmtstr, "%I(%P)", SIZE-100);
                else if(strcmp(optarg, "24") == 0)
                    strncat(fmtstr, "%H", SIZE-100);
                else

                    fprintf(stderr, "Invalid argument\n");

                break;

            case 'M':
                strncat(fmtstr, "%M ", SIZE-100);
                break;

            case 'S':
                strncat(fmtstr, "%S ", SIZE-100);
                break;

            case 'y':

                if(strcmp(optarg, "2") == 0)
                    strncat(fmtstr, "%y ", SIZE-100);

                else if(strcmp(optarg, "4") == 0)
                    strncat(fmtstr, "%Y ", SIZE-100);

                else
                    fprintf(stderr, "Invalid error\n");

                break;

            case 'm':
                strncat(fmtstr, "%m ", SIZE-100);
                break;

            case 'd':
                strncat(fmtstr, "%d ", SIZE-100);
                break;

            default:
                break;

        }
    }

    strncat(fmtstr, "\n", SIZE-100);
    strftime(buf, SIZE, fmtstr ,tm);
    fputs(buf,fp);

    if(fp !=stdout)
        fclose(fp);


    return 0;

}
