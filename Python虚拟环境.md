## Python 虚拟环境

Python应用程序通常会使用不在标准库内的软件包和模块，且有时会需要包或者模块的特定版本，如应用程序A需要特定模块的1.0版本但应用程序B需要2.0版本。这意味着只安装其中一个版本可能无法满足每个应用程序的要求，此时我们可以使用虚拟环境来解决这一问题。
在学习虚拟环境的时候遇到了**virtualenv**、**venv**、**pipenv**等名词，这些都与Python的虚拟环境有关，那么这些到底是什么及相互之间又有什么联系呢？

### virtualenv
virtualenv 是目前最流行的 Python 虚拟环境配置工具。它不仅同时支持 Python2 和 Python3，而且可以
为每个虚拟环境指定 Python 解释器，并选择不继承基础版本的包。

### virtualenv 的优点

> 1. 使得不同Python应用的开发环境相互独立
>
> 2. 开发环境升级不影响其他应用的开发环境，也不会影响全局的环境（默认开发环境是全局开发环境）,因为虚拟环境是将全局环境进行私有的复制，当我在虚拟环境进行 pip install 时，只会安装到选择的虚拟环境中。
>
> 3. 它可以防止系统中出现包管理混乱和版本的冲突
>

### virtualenv 的简单使用

1. pip 安装 virtualenv

```shell
pip3 install virtualenv 
```

2. 创建虚拟环境目录

```shell
mkdir myproject
cd myproject
```

3. 创建一个独立的Python运行环境: myenv

```shell
virtualenv --no-site-packages myenv  
```

 1）参数：--no-site-packages （可省略） 其意义在于不复制已经安装到系统Python环境中的所有第三方包从而得到一个“纯净”的运行环境。
 2） 此时当前目录下会生成一个名为：“myenv” 的目录，该目录中存放刚生成的虚拟环境文件

4. 激活虚拟运行环境

```shell
#windows:
myenv\Scripts\activate.bat
#Linux:
source myenv/bin/activate
```
注： 以上命令执行完后会发现命令提示符变了，有个(myenv)前缀，表示当前环境是一个名为“myenv”的Python环境，此时可以在该环境中按照我们熟悉的方式安装库、运行程序等。

5. 安装各种第三方包，并运行Python命令
```shell
pip install jieba
python myapp.py
```

注： 因为此时虚拟环境已经激活，所以可以直接使用命令pip、python而不是pip3和python3。

6. 使用deactivate命令退出当前的myenv环境

```shell
deactivate
```
其他详细介绍，请参考 virtutalenv 官网：https://virtualenv.pypa.io/en/latest/reference/

### venv:
Python 从3.3 版本开始，自带了一个虚拟环境 venv，在[PEP-405](https://legacy.python.org/dev/peps/pep-0405/) 中可以看到它的详细介绍。它的很多操作都和 virtualenv 类似，但是两者运行机制不同。
因为是从 3.3 版本开始自带的，这个工具也仅仅支持 python 3.3 和以后版本。所以，要在 python2 上使用虚拟环境，依然要利用 virtualenv 。
有关venv与virtualenv的区别，virtualenv官网: https://virtualenv.pypa.io/en/latest/reference/#compatibility-with-the-stdlib-venv-module 有详细介绍。

venv 安装
```shell
# Windows 中venv已经以标准库的形式存在，不用再单独安装
# Linux
sudo apt-get install python3-venv  # 如有不同版本的Python3,可指定具体版本venv：python3.5-venv
```

在当前目录创建一个独立的Python运行环境: myenv
```shell
# Windows
py -3 -m venv myenv  
# Linux 
python3 -m venv myenv
```
激活虚拟运行环境、安装第三方包、运行程序及退出虚拟环境等操作均与 virtualenv 相同，在此不再赘述。
其他详细介绍，请参考 venv 官网：https://docs.python.org/zh-cn/3/tutorial/venv.html

### pipenv:
pipenv 是 Pipfile 主要倡导者、requests 作者 Kenneth Reitz 写的一个命令行工具，主要包含了Pipfile、pip、click、requests和virtualenv，能够有效管理Python多个环境，各种第三方包及模块。

pipenv 的主要特性：

> pipenv集成了pip，virtualenv两者的功能，且完善了两者的一些缺陷。
> 过去用virtualenv管理requirements.txt文件可能会有问题，Pipenv使用Pipfile和Pipfile.lock，后者存放将包的依赖关系，查看依赖关系是十分方便。
> 各个地方使用了哈希校验，无论安装还是卸载包都十分安全，且会自动公开安全漏洞。
> 通过加载.env文件简化开发工作流程。
> 支持Python2 和 Python3，在各个平台的命令都是一样的。
