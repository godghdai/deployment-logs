#### 静态ip设置
在终端中运行以下命令来执行此操作：
```sh
vim /etc/network/interfaces
```
```txt
auto eth0
iface eth0 inet static
address 192.168.72.165
netmask 255.255.255.0
gateway 192.168.72.2
```
#### 动态分配Ip地址
```txt
auto eth0
iface eth0 inet dhcp
```
#### DNS服务器
```sh
vim /etc/resolv.conf
```
```txt
nameserver 8.8.8.8
nameserver 192.168.72.2
```
#### 重启动网络服务
```sh
systemctl restart networking
service networking restart
```
#### ssh

客服端ssh_config，服务端 sshd_config
```sh
vi /etc/ssh/sshd_config
```
```txt
#PermitRootLogin prohibit-password
PermitRootLogin yes
PasswordAuthentication yes
```
#### 更改软件源
```sh
vim /etc/apt/sources.list
```
```txt
#deb http://deb.debian.org/debian bookworm main contrib non-free
#deb http://security.debian.org/debian-security bookworm-security main contrib non-free

deb http://mirrors.ustc.edu.cn/debian bookworm main contrib non-free
deb http://mirrors.ustc.edu.cn/debian-security bookworm-security main contrib non-free 

sudo sed -i 's/deb.debian.org/mirrors.ustc.edu.cn/g' /etc/apt/sources.list
sudo sed -i 's|security.debian.org/debian-security|mirrors.ustc.edu.cn/debian-security|g' /etc/apt/sources.list
````

#### 本地化
```sh
apt-get install locales  
dpkg-reconfigure locales 
# 空格 选中 zh_CN.UTF-8
locale
# 重启才生效
```

#### 修改时区
```sh
timedatectl list-timezones | grep Shanghai
Asia/Shanghai

timedatectl set-timezone Asia/Shanghai
timedatectl
```
```sh
ls -l /etc/localtime

lrwxrwxrwx 1 root root 35 Jun 20 13:55 /etc/localtime -> ../usr/share/zoneinfo/Asia/Shanghai
```

在不支持 timedatectl的情况下
```sh
ln -sf /usr/share/zoneinfo/America/Monterrey /etc/localtime
```


#### 文件上传和下载
```sh
apt install lrzsz
rz 
sz
```

#### 无线网卡
##### 查看是否有无线网卡
```sh
apt install wireless-tools 
iwconfig 
```
```txt
wlan0     IEEE 802.11  ESSID:off/any  
          Mode:Managed  Access Point: Not-Associated   
          Retry short limit:7   RTS thr:off   Fragment thr:off
          Encryption key:off
          Power Management:on
```
##### 搜索wifi

```sh
iwlist wlan0 scan | grep ESSID
```
wifi网卡没启动,会提示
```txt
wlan0     Interface doesn't support scanning : Network is down
```
```sh
ifconfig wlan0 up
iwlist wlan0 scan | grep ESSID
```
```txt
ESSID:"\xF0\x9F\x92\xA9"
ESSID:"yzd_main_wifi"
ESSID:"yzd_main_wifi"
ESSID:"ChinaNet-a4ZT"
ESSID:"Tenda_E8EAA0"
ESSID:""
ESSID:""
```
```sh
ifconfig wlan0 up
```
如果启动失败会有如下提示
```txt
SIOCSIFFLAGS: Operation not possible due to RF-kill
```

```sh
apt install rfkill 
rfkill list all
```
```txt
0: phy0: Wireless LAN
	Soft blocked: yes
	Hard blocked: no
1: hci0: Bluetooth
	Soft blocked: no
	Hard blocked: no
```

```sh
rfkill unblock wifi
rfkill list all
```
```txt
0: phy0: Wireless LAN
	Soft blocked: no
	Hard blocked: no
1: hci0: Bluetooth
	Soft blocked: no
	Hard blocked: no
```
#### 查看网卡支持的模式
```sh
iw list
```

```txt
Supported interface modes:
		 * IBSS
		 * managed
		 * AP
		 * P2P-client
		 * P2P-GO
		 * P2P-device

```
