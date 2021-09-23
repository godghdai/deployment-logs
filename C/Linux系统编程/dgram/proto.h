#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED

#define PORT "8080"
#define NAMESIZE 11

/*
netstat -anu       //udp
netstat -ant       //tcp
*/

struct msg_st
{
    uint8_t name[NAMESIZE];
    uint32_t math;
    uint32_t chinese;
} __attribute__((packed));


#endif // PROTO_H_INCLUDED
