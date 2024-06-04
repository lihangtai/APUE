#ifndef __PROTO_H__
#define __PROTO_H__

#include <stdint.h>

#define RCVPROT "1989"
#define NAMESIZE 13

struct msg_st{
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
};

#endif
