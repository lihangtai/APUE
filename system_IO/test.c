#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024
int main(int argc, char *argv[]){


    int count = 0 ;
    int c = 0;
    char buf[SIZE],;
    char fmtstr[SIZE];
    fmtstr[0] = '\0';
    time_t stamp;
    struct tm *tm;
    FILE *fp;

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

                fopen(argv[optind-1], "w");
                if(fp == NULL){
                    perror("fopen failed");
                    fp = stdout;
                }



            case 'H':

                if(strcmp(optarg, "12") == 0)
                    strncat(fmtstr, "%I(%P)", SIZE);
                else if(strcmp(optarg, "24") == 0)
                    strncat(fmtstr, "%H", SIZE);
                else

                    fprintf(stderr, "Invalid argument\n");

                break;

            case 'M':
                strncat(fmtstr, "%M ", SIZE);
                break;

            case 'S':
                strncat(fmtstr, "%S ", SIZE);
                break;

            case 'y':

                if(strcmp(optarg, "2") == 0)
                    strncat(fmtstr, "%y ", SIZE);

                else if(strcmp(optarg, "4") == 0)
                    strncat(fmtstr, "%Y ", SIZE);

                else
                    fprintf(stderr, "Invalid error\n");

                break;

            case 'm':
                strncat(fmtstr, "%m ", SIZE);
                break;

            case 'd':
                strncat(fmtstr, "%d ", SIZE);
                break;

            default:
                break;

        }
    }

    strncat(fmtstr, "\n", SIZE);
    strftime(buf, SIZE, fmtstr ,tm);
    fputs(buf,fp);

    if(fp !=stdout)
        fclose(fp);


    return 0;

}