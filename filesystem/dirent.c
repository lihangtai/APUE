#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#define PAT "/etc"
int main(){

    DIR *dp;
    struct dirent *cur;
    dp = opendir(PAT);
    if(dp == NULL){
       perror("open failed");
       exit(-1);
    }

    while((cur = readdir(dp)) != NULL){
        if(strncmp(cur->d_name, "a",1) == 0 && strstr(cur->d_name, ".conf")!=NULL) {
            puts(cur->d_name);
        }
    }

    closedir(dp);
    exit(0);

}
