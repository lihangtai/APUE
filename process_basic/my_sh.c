#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <glob.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define DELIMS " \t\n"

struct cmd{
    glob_t globres;

};
static void parse(char *line, struct cmd *res){


    char *tok;
    int i = 0;
    while(1) {
        tok = strsep(&line, DELIMS);
        if(tok == NULL)
            break;
        if(tok[0] == '\0'){
            continue;
        }

        glob(tok, GLOB_NOCHECK | GLOB_APPEND*i, NULL, &(res->globres));
        i = 1;

    }
}
static void prompt(){

    printf("jerry's sh: ");
}

int main(){

    pid_t  pid;
    char *linebuf = NULL;
    size_t size = 0;
    struct cmd info;
    while(1){

        prompt();
        if(getline(&linebuf, &size,stdin ) < 0){
            perror("getline()");
            break;
        }
        parse(linebuf, &info);

        if(0){}
        else{

            pid = fork();
            if(pid <0){
                perror("fork()");
                exit(-1);
            }
            if(pid == 0){
                execvp(info.globres.gl_pathv[0], info.globres.gl_pathv);
            }

             wait(NULL);
        }


    }

    return 0;

}

