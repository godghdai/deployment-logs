#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define IPSTRSIZE 40
#define SERVERPORT "8080"

int main(int argc,char *argv[])
{
    int sd;
    long long stamp;
    FILE * fp;
    struct sockaddr_in raddr;

    sd=socket(AF_INET,SOCK_STREAM,0);
    if(sd<0)
    {
        perror("socket()");
        exit(1);
    }

    raddr.sin_family=AF_INET;
    raddr.sin_port=htons(atoi(SERVERPORT));
    inet_pton(AF_INET,"127.0.0.1",&raddr.sin_addr);

    if(connect(sd,(void *)&raddr,sizeof(raddr))<0)
    {
        perror("connect()");
        exit(1);
    }

    fp=fdopen(sd,"r");
    if(fp==NULL)
    {
        perror("fdopen()");
        exit(1);
    }

    if(fscanf(fp,"%lld\r\n",&stamp)<1)
        fprintf(stderr,"Bad format!\n");
    else
        fprintf(stdout,"stamp=%lld\n",stamp);

    fclose(fp);
    //close(sd);
    exit(0);
}
