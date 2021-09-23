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
注意关闭防火墙，接收端和发送端，必须设置 SO_BROADCAST
```c
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
