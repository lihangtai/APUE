#ifndef __PROTO_H__
#define __PROTO_H__
#define NAMESIZE 32
#define KEYPATH "/tmp/myfifo"
#define KEYPROJ 'a'
#define MSGTYPE 10

struct msg_st{
    long mtype;
    char name[NAMESIZE];
    int math;
    int chinese;
};

#endif




