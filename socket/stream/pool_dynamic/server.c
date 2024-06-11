#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <time.h>
#include <errno.h>
#include <sys/mman.h>
#include <signal.h>
#include <unistd.h>

#include "proto.h"

#define MINSPARESERVER 5
#define MAXSPARESERVER 10
#define MAXCLIENT 20
#define SIG_NOTIFY SIGUSR2
#define LINEBUFSIZE 1024
#define IPSTRSIZE 40

enum{
    SERVER_BUSY = 0,
    SERVER_IDLE = 1
};
struct server_st{

    int pid;
    int state;
};
static int sd;


struct server_st *serverpool;
static int idle_count = 0;
static int busy_count = 0;

void show_status();
void init_serverpool();
void do_server_job(int pos);
void add_1_server();
void del_1_server();
void show_status();
void scan_pool();
static void usr2_hanlder(int s) {
    return ;
}
int main(){

    
    struct sigaction sa, osa;
    sigset_t set, oset;
    struct sockaddr_in laddr;
    pid_t pid;
    int i;
    int val = 1;


//SIGCHLD 和自定义SIG_NOTIFY 的信号定义，并设置当前进程的mask，屏蔽SIG_NOTIFY等待开启 ////
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_DFL;
    sa.sa_flags = SA_NOCLDWAIT;
    sigaction(SIGCHLD,&sa,&osa);

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = usr2_hanlder;
    sa.sa_flags = 0;
    sigaction(SIG_NOTIFY, &sa, &osa);

    sigemptyset(&set);
    sigaddset(&set, SIG_NOTIFY);
    sigprocmask(SIG_BLOCK, &set, &oset);

//网络服务初始化
    if((sd = socket(AF_INET, SOCK_STREAM, 0) )< 0){
        perror("socket()");
        exit(-1);
    }

      // 设置套接字选项
    if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        perror("setsockopt()");
        exit(1);
    }



    laddr.sin_family = AF_INET;
    laddr.sin_port = htons(atoi(SERVERPORT));
    inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr.s_addr);

    if(bind(sd, (struct sockaddr *)&laddr, sizeof(laddr))< 0 ){
        perror("bind");
        exit(1);
    } 

    if(listen(sd, 200) < 0){
        perror("listen");
        exit(-1);
    }

//初始化服务池
    init_serverpool();
 

    while(1){

//信号驱动，动态改变服务池中服务的进程的数量
            sigsuspend(&oset);
            

            scan_pool();


        
            if(idle_count > MAXSPARESERVER){
                
                for(i = 0; i< (idle_count - MAXSPARESERVER); i++){
                    
                    del_1_server();
                }
            }
            else if(idle_count < MINSPARESERVER){
                for(i = 0; i< (MINSPARESERVER - idle_count); i++){
                    add_1_server();
                }


            }
            
            scan_pool();
            //使用符号展示进程的状态 x表示busy  .表示idle  
            show_status();

            
            }
                      


                     
        sigprocmask(SIG_SETMASK, &oset, NULL);
        close(sd);
  
        

        }

        



void show_status(){
    for(int i =0;i < MAXCLIENT;i++){
        if(serverpool[i].pid == -1)
            putchar(' ');
        else if(serverpool[i].state == SERVER_BUSY)
            putchar('x');
        else
            putchar('.');
    }
    putchar('\n');
}
void scan_pool(){

    int i;
    int busy = 0;
    int idle = 0;
    for(i = 0; i < MAXCLIENT; i++) {
        if(serverpool[i].pid == -1) { // 进程不存在
            continue;
        }
        // kill(pid, 0)用于检测pid是否存在，存在返回0，不存在返回-1
        if(kill(serverpool[i].pid, 0) == -1) {
            serverpool[i].pid = -1;
            continue;
        }
        if(serverpool[i].state == SERVER_IDLE) {
            idle++;
        } else if(serverpool[i].state == SERVER_BUSY) {
            busy++;
        } else {
            fprintf(stderr, "Unknown state.\n");
            abort();
        }
    }
    idle_count = idle;
    busy_count = busy;
    
}


void init_serverpool(){

    serverpool = mmap(NULL, sizeof(struct server_st) * MAXCLIENT , PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS , -1, 0);

    if(serverpool == NULL){
        perror("mmap()");
        exit(0);
    }

    for(int i =0 ; i < MAXCLIENT; i++){
        serverpool[i].pid = -1;
        
    }
    for(int i =0 ; i < MINSPARESERVER; i++){

    add_1_server();
    }

}

void do_server_job(int pos){

    struct sockaddr_in server_addr;
    socklen_t len;
    char buf[BUFSIZE];
    char ipstr[IPSTRSIZE];
    time_t stamp;

    pid_t ppid = getppid();

    int client_sd;

    while(1){

        serverpool[pos].state = SERVER_IDLE;
        

        client_sd = accept(sd, (void *)&server_addr, &len);
        if(client_sd < 0){
            perror("accept()");
            exit(1);
        }
        serverpool[pos].state = SERVER_BUSY;
        kill(ppid, SIG_NOTIFY);
        stamp = time(NULL);

        
        int length = snprintf(buf, BUFSIZE, FMT_STAMP, stamp);
        inet_ntop(AF_INET, &server_addr, ipstr, IPSTRSIZE );
        send(client_sd, buf, length, 0);
        sleep(5);
        close(client_sd);
    }

}

void add_1_server(){

    pid_t pid;
    int slot;
    for(slot = 0;slot < MAXCLIENT; slot++){
        if(serverpool[slot].pid == -1){
            break;
        }
    }

    pid = fork();

    if(pid < 0){
        perror("fork()");
        exit(1);
    }
    else if(pid == 0){
        do_server_job(slot);
        
    }
    else{
        serverpool[slot].pid = pid;
        serverpool[slot].state = SERVER_IDLE;
        idle_count++;
    }
    
}

void del_1_server(){

    int i;
    pid_t pid;
    if(idle_count == 0){
        exit(0);
    }
    for(i = 0;i < MAXCLIENT; i++){
        if(serverpool[i].pid != -1 && serverpool[i].state == SERVER_IDLE){
            kill(serverpool[i].pid,SIGKILL);
            serverpool[i].pid = -1;
            idle_count--;
            break;
        }
    }
   

}