```
netstat -anu       //udp
netstat -ant       //tcp
```

报式套接字：

```
socket();
bind();
sendto();
rcvfrom();
inet_pton();
inet_ntop();
```

多点通讯：广播（全网广播，子网广播），多播/组播
#### 全网广播
```c
//注意关闭防火墙，接收端和发送端，必须设置 SO_BROADCAST
raddr.sin_family=AF_INET;
raddr.sin_port=htons(atoi(PORT));
inet_pton(AF_INET,"255.255.255.255",&raddr.sin_addr);

int val=1;
if(setsockopt(sd,SOL_SOCKET,SO_BROADCAST,&val,sizeof(val))<0)
{
   perror("setsockopt()");
   exit(1);
}
```

#### 多播组 
特殊组 224.0.0.1
```
#define MGROUP "224.2.2.2"
```
```
//接收端
struct ip_mreqn mreq;
inet_pton(AF_INET,MGROUP,&mreq.imr_multiaddr);
inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);
mreq.imr_ifindex=if_nametoindex("eth0");
if(setsockopt(sd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))<0)
{
    perror("setsockopt()");
    exit(1);
}
```

```
//发送端
struct ip_mreqn mreq;
inet_pton(AF_INET,MGROUP,&mreq.imr_multiaddr);
inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);
/*
* 查看网络索引号
* ip ad sh
* ifconfig
*/
mreq.imr_ifindex=if_nametoindex("eth0");
if(setsockopt(sd,IPPROTO_IP,IP_MULTICAST_IF,&mreq,sizeof(mreq))<0)
{
    perror("setsockopt()");
    exit(1);
}

```
