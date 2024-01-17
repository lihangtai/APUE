#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <glob.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>
#define PATHSIZE 1024

static int path_noloop(const char *path){
    char *pos;
    pos = strrchr(path, '/');
    if(pos == NULL){
        exit(1);
    }
    if(strcmp(pos+1, ".") == 0 || strcmp(pos+1, "..") == 0) {
        return 0;
    }

    return 1;


    }


static int64_t my_du(const char *path) {

    struct stat statres;
    char nextpath[PATHSIZE];
    glob_t globres;
    int sum = 0;

    if (lstat(path, &statres) < 0) {
        perror("lstat() fail");
        exit(1);
    }
    //step 1: make sure the type of argc[1] (file? dir? link?)

    if (!S_ISDIR(statres.st_mode))
        return statres.st_blocks;

    else {
// file under dir has two types: /*, .xx



        strncpy(nextpath, path, PATHSIZE);
        strcat(nextpath, "/*");
        glob(nextpath, 0, NULL, &globres);

        strncpy(nextpath, path, PATHSIZE);
        strcat(nextpath, "/.*");
        glob(nextpath, GLOB_APPEND, NULL, &globres);

        for (int i = 0; i < globres.gl_pathc; i++) {
            if (path_noloop(globres.gl_pathv[i]))
                sum += my_du(globres.gl_pathv[i]);
            // f+f + d

        }

        sum += statres.st_blocks;

        return sum;

    }
}



int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr, "follow the pattern please\n");
        exit(-1);
    }

    printf("%ld\n", my_du(argv[1])/2);

    return 0;


}
