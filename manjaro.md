## 安装 vmware-tools
```
$ git clone https://github.com/rasa/vmware-tools-patches.git
$ cd vmware-tools-patches
$ ./patched-open-vm-tools.sh
```

## 安装好后第一步是排列源
```
sudo pacman-mirrors -g
```

Manjaro更换国内源并安装搜狗输入法等常用软件笔记
sudo pacman-mirrors -i -c China -m rank
sudo pacman -Syy
sudo pacman -S vim


## 安装搜狗输入法
sudo pacman -S vim 

添加archlinuxcn源，
sudo vim /etc/pacman.conf，


添加中科大源,如下配置：
```
[archlinuxcn]
SigLevel = Optional TrustedOnly
Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch
```
然后更新一下，
```
sudo pacman -Syy && sudo pacman -S archlinuxcn-keyring
```

卸载已有fcitx
sudo pacman -Rs $(pacman -Qsq fcitx)


$ sudo vi ~/.xprofile  # vi可以换成系统现有的文本编辑器
然后在里面添加：
```
export GTK_IM_MODULE=fcitx
export QT_IM_MODULE=fcitx
export XMODIFIERS=”@im=fcitx”
```



Manjaro更换国内源并安装搜狗输入法等常用软件笔记
```
sudo pacman-mirrors -i -c China -m rank
sudo pacman -Syy
sudo pacman -S vim
```
sudo vim /etc/pacman.conf
#复制以下配置到文件末尾
```
[archlinuxcn]
SigLevel = Optional TrustedOnly
Server = https://mirrors.ustc.edu.cn/archlinuxcn/$arch
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch

[antergos]
SigLevel = TrustAll
Server = https://mirrors.tuna.tsinghua.edu.cn/antergos/$repo/$arch

[arch4edu]
SigLevel = TrustAll
Server = https://mirrors.tuna.tsinghua.edu.cn/arch4edu/$arch
```
```
sudo pacman -Syy
sudo pacman -S archlinuxcn-keyring
sudo pacman -S antergos-keyring
sudo pacman -Syu
sudo pacman -S yaourt
```
#安装环境
```
sudo pacman -S base-devel
```
#安装chrome
```
sudo pacman -S google-chrome
```

#安装搜狗输入法
```
yaourt -S fcitx-sogoupinyin fcitx-configtool fcitx-im
sudo pacman -U https://arch-archive.tuna.tsinghua.edu.cn/2019/04-29/community/os/x86_64/fcitx-qt4-4.2.9.6-1-x86_64.pkg.tar.xz
```
sudo vim /etc/environment
#在文件末尾加上以下配置
```
GTK_IM_MODULE=fcitx
QT_IM_MODULE=fcitx
XMODIFIERS="@im=fcitx"
```
#重启系统

#解决wps英文问题
```
sudo pacman -S archlinuxcn/wps-office-mui-zh-cn
```
#解决：
#/usr/bin/hardcode-fixer: 第 140 行：[: ：需要整数表达式
#sed：无法读取 /tmp/tofix.csv：没有那个文件或目录
#chown: 无法访问 '/tmp/tofix.csv': 没有那个文件或目录
#/usr/bin/hardcode-fixer:行297: /tmp/tofix.csv: 没有那个文件或目录
#错误：命令未能被正确执行

#执行命令
```
sudo pacman -R hardcode-fixer
```

