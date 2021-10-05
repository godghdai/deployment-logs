# Pop!_OS

#### 常用包管理命令

```
apt install 包名     apt-get install 包名
apt remove 包名      apt-get remove 包名
apt search 包名      apt-cache search 包名
apt show 包名        apt-cache show 包名
apt update          apt-get update
apt upgrade         apt-get upgrade
```

#### 修改root密码

```
sudo passwd root
```

#### 安装openssh

```
sudo apt install openssh-server
systemctl status ssh
```
vim /etc/ssh/sshd_config 
```
# Authentication:
LoginGraceTime 120
#PermitRootLogin prohibit-password 
PermitRootLogin yes  //允许root登录，设为yes。
StrictModes yes
```
#### 重启ssh服务
系统服务目录 /etc/systemd/system
```
sudo service ssh restart
sudo systemctl restart ssh 
```
#### 备份原镜像源
```
cp /etc/apt/sources.list /etc/apt/sources.list.bak
```
#### 修改为国内镜像源
```
vim /etc/apt/sources.list
```
```
deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse

deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
```
#### 更新系统
```
 apt update
 apt list --upgradable
 apt upgrade
```

#### 创建桌面快捷方式

win+t 打开终端

```
apt install vlc
ls  /usr/share/applications |grep -i vlc
cp /usr/share/applications/vlc.desktop /home/yzd/桌面/vlc.desktop
chmod a+x /home/yzd/桌面/vlc.desktop
```

右键单击桌面vlc图标 允许运行

####  安装微软雅黑和 Consolas 字体

```shell
wget http://www.mycode.net.cn/wp-content/uploads/2015/07/YaHeiConsolas.tar.gz --no-check-certificate 
//在系统目录下创建自定义字体目录
sudo mkdir -p /usr/share/fonts/vista 
tar -zxvf YaHeiConsolas.tar.gz -C /usr/share/fonts/vista/
//修改字体权限
sudo chmod 644 /usr/share/fonts/vista/*.ttf
//进入字体目录
cd /usr/share/fonts/vista/
//刷新并安装字体
sudo mkfontscale && sudo mkfontdir && sudo fc-cache -fv
reboot
```

在Tweaks中设置字体

#### 安装网易云音乐

https://music.163.com/#/download

#### 安装Chrome

```
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
dpkg -i google-chrome-stable_current_amd64.deb 
```

#### 安装 GNOME Shell 扩展

用firefox 打开 https://extensions.gnome.org/ ，安装浏览器扩展

```text
gnome-shell --version
apt install chrome-gnome-shell //虽然名字中有chrome firefox也可以用，只是浏览器扩展的服务端程序
```

#### 显示窗口最大化和最小化

如果程序列表中没有tweak(优化)，安装

```
apt install gnome-tweak-tool
```

tweak->windows->Titlebar Buttons

#### 设置输入法切换快捷键 

默认 Win+Space
Settings->keyboard->Typing

设置ibus框架

```
sudo ibus-setup
```

增加极点五笔

Settings->keyboard->Input Sources->Chinese(China)->极点五笔
