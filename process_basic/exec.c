#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){

   pid_t pid;
   puts("begin the program\n");
   fflush(NULL);

   pid = fork();
   if(pid < 0){
       perror("fork()");
       exit(-1);
   }
   if(pid == 0){
       execl("/bin/ls", "ls","-alh", NULL);
       perror("execl()");
       exit(-1);
   }

       wait(NULL);
       puts("end\n");
       exit(0);

}
