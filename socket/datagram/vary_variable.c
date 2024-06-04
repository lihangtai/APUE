#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct packet_st{
    uint32_t packHead;
    uint8_t packetData[0];
}__attribute__((packed));


int main(){
    int size;
    struct packet_st *bufp;
    printf("sizeof(uint32_t)%d\n", sizeof(bufp->packetData));
    printf("sizeof(packet_st)= %d\n",sizeof(bufp));

    char data[] = "12345";
    size = sizeof(struct packet_st) + strlen(data);
    bufp = (struct packet_st *)malloc(size);
    bufp->packHead = strlen(data);
    strcpy(bufp->packetData,data);
       printf("packetHead: %d\n", bufp->packHead);
    printf("packetData: %s\n", bufp->packetData);
    free(bufp);
    return 0;



}