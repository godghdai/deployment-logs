## 环境搭建

1、安装gcc、g++、gdb
```
sudo apt-get install gcc 
sudo apt-get install g++ 
sudo apt-get install gdb
```

2、安装编译环境
```
sudo apt-get install build-essential
sudo apt-get install codeblocks-contrib
```
```
Geany ： sudo apt-get install geany
CodeBlocks : sudo apt-get install codeblocks
```

## 使用codeblocks编程运行时终端不能复制粘贴（Ubuntu)
```
settings–>environment–>generalsettings–>Terminal to launch console programs:
把方框里默认的终端改成 gnome-terminal -t $TITLE -x
```

## 安装pthread相关 man手册
```
sudo apt-get install manpages-posix-dev
```
