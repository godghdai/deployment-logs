http://dia-installer.de/download/index.html
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

## 线程
#### 互斥量
```
pthread_mutex_t
pthread_mutex_init();
pthread_mutex_destroy();
pthread_mutex_lock();
pthread_mutex_trylock();
pthread_mutex_unlock();
pthread_once();
```
#### 条件变量

```
pthread_cond_t
pthread_cond_init();
pthread_cond_destroy();
pthread_cond_broadcast();
pthread_cond_signal();
```

#### 安装openssl

```
sudo apt-get install openssl
sudo apt-get install libssl-dev
```
