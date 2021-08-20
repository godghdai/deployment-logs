## 国内镜像源

- 阿里云 https://mirrors.aliyun.com/pypi/simple/
- 中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/
- 豆瓣 https://pypi.douban.com/simple/
- 清华大学 https://pypi.tuna.tsinghua.edu.cn/simple/
- 中国科学技术大学 https://pypi.mirrors.ustc.edu.cn/simple/
- 华中理工大学 http://pypi.hustunique.com/
- 山东理工大学 http://pypi.sdutlinux.org/

## 设为全局

```shell
# 如果你只想为当前用户设置，你也可以去掉下面的"--global"选项
pip config --global set  global.index-url https://mirrors.aliyun.com/pypi/simple/
```

## 临时使用

```shel
pip install scrapy -i https://pypi.tuna.tsinghua.edu.cn/simple 
pip install scrapy -i http://pypi.douban.com/simple/  --trusted-host pypi.douban.com
pip install scrapy -i http://mirrors.aliyun.com/pypi/simple/ --trusted-host mirrors.aliyun.com
```

## 永久修改

Linux下，修改 ~/.pip/pip.conf (没有就创建一个文件夹及文件。文件夹要加“.”，表示是隐藏文件夹)

```ini
[global]
index-url = https://pypi.tuna.tsinghua.edu.cn/simple
[install]
trusted-host=mirrors.aliyun.com
```

在**Windows 7**及以上版本的系统中，该文件默认是被隐藏的，实际位置是：**C:\ProgramData\pip\pip.ini**

## 生成requirements.txt

1. 第一种 适用于 **单虚拟环境的情况：** 

```shell
pip freeze > requirements.txt
```

2. 当我们使用的是全局环境时， 推荐 使用 `pipreqs` github地址为： https://github.com/bndr/pipreqs

```she
pip install pipreqs
pipreqs . --encoding=utf8 --force
```

## 使用requirements.txt安装依赖的方式：

```shel
pip install -r requirements.txt
```
