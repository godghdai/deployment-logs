# 开启 TCP BBR 拥塞控制算法

BBR 目的是要尽量跑满带宽，并且尽量不要有排队的情况，效果并不比速锐差。

Linux kernel 4.9+ 已支持 tcp_bbr。下面简单讲述基于 KVM 架构 VPS 如何开启。

## Debian 8+ / Ubuntu 14.04
下载最新内核，最新内核查看这里
http://kernel.ubuntu.com/~kernel-ppa/mainline/v4.16/linux-image-4.16.0-041600-generic_4.16.0-041600.201804012230_amd64.deb
安装内核
```
dpkg -i linux-image-4.*.deb
```
删除旧内核（可选）
```
dpkg -l | grep linux-image 
apt-get purge <旧内核>
```
更新 grub 系统引导文件并重启
```
update-grub
reboot
```
## Ubuntu 16.04
安装 Hardware Enablement Stack (HWE)，自动更新内核
```
apt install --install-recommends linux-generic-hwe-16.04
```
删除旧内核（可选）
```
sudo apt autoremove
```

## CentOS 6
下载更换内核，最新内核查看这里
```
rpm --import https://www.elrepo.org/RPM-GPG-KEY-elrepo.org
rpm -Uvh http://www.elrepo.org/elrepo-release-6-8.el6.elrepo.noarch.rpm
yum --enablerepo=elrepo-kernel install kernel-ml -y
```
查看内核是否安装成功
```
rpm -qa | grep kernel
```
删除旧内核（可选）
```
rpm -ev <旧内核>
```
更新 grub 系统引导文件并重启
```
sed -i 's:default=.*:default=0:g' /etc/grub.conf
reboot
```
开不了机的打开 VPS 后台控制面板的 VNC，开机卡在 grub 引导, 只需要手动选择内核就可以了。

安装完成后不要忘记修改 /boot/grub/menu.lst 和 /etc/grub.conf，将这两个文件中旧内核的启动项删除即可避免无法重启的问题。

更新到最新版内核
```
yum --enablerepo=elrepo-kernel update -y 
reboot
```
## CentOS 7
下载更换内核，最新内核查看这里
```
rpm --import https://www.elrepo.org/RPM-GPG-KEY-elrepo.org
rpm -Uvh http://www.elrepo.org/elrepo-release-7.0-3.el7.elrepo.noarch.rpm
yum --enablerepo=elrepo-kernel install kernel-ml -y
```
查看内核是否安装成功
```
rpm -qa | grep kernel
```
删除旧内核（可选）
```
rpm -ev 旧内核
```
更新 grub 系统引导文件并重启
```
egrep ^menuentry /etc/grub2.cfg | cut -f 2 -d \'
grub2-set-default 0  # default 0 表示第一个内核设置为默认运行, 选择最新内核就对了
reboot
```
注意，某些服务商（如 Digital Ocean）可能需要首先将 VPS 配置为可自定义内核，然后 grub2 的配置才会生效
重新启动后，如果出现「read-only file system」的错误，root 账户下执行 mount -o remount rw / 即可。

更新到最新版内核
方法同 CentOS 6。

## 开启 BBR
开机后 uname -r 看看是不是内核 >= 4.9。

执行 lsmod | grep bbr，如果结果中没有 tcp_bbr 的话就先执行：
```
sudo modprobe tcp_bbr
echo "tcp_bbr" | sudo tee --append /etc/modules-load.d/modules.conf
```
执行
```
echo "net.core.default_qdisc=fq" | sudo tee --append /etc/sysctl.conf
echo "net.ipv4.tcp_congestion_control=bbr" | sudo tee --append /etc/sysctl.conf
```
保存生效
```
sudo sysctl -p
```
执行
```
sysctl net.ipv4.tcp_available_congestion_control
sysctl net.ipv4.tcp_congestion_control
```
如果结果都有 bbr，则证明你的内核已开启 BBR。

执行 lsmod | grep bbr，看到有 tcp_bbr 模块即说明 BBR 已启动。
