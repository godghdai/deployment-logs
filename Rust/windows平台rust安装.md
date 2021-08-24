### windows平台rust安装

#### 从[rustup.rs](https://rustup.rs/)官网下载 rustup-init.exe

默认安装于**用户目录**下。

> 该软件默认检查环境变量`CARGO_HOME`、`RUSTUP_HOME`，分别为`.cargo`、`.rustup`设置目录，按需修改
> 需要注意的是后期包的累积可能会占用巨量的存储空间。
```
CARGO_HOME　  D:\Rust\cargo
RUSTUP_HOME　 D:\Rust\rustup
```
安装过程中请选择第二项 “Customize installation” ！注意到default host triple中设置的是x86_64-pc-windows-msvc，而由于本文所使用的调试器是GDB，故需要修改为x86_64-pc-windows-gnu。default toolchain请选择stable，即稳定版。nightly为前瞻版（更新频率快），'beta’为测试版，实际使用时我们仍需使用到nightly版，后文会提到。

等待下载完成后可在path中检查添加~/.cargo/bin以使用各种命令。

输入rustup --version以检查是否安装成功。

#### 安装下载加速环境变量

```
RUSTUP_DIST_SERVER : https://mirrors.ustc.edu.cn/rust-static
RUSTUP_UPDATE_ROOT : https://mirrors.ustc.edu.cn/rust-static/rustup
```

#### setting.toml

TOML(Tom’s Obvious Minimal Language) 是一个想要打败yuml的标注语言，caogo项目也有使用。

该文件位于.rustup/下。

default_host_triple: 第一次安装时设置，只能对该文件进行修改以改变默认值。
default_toolchain : 默认使用的toolchain，可由rustup default <toolchain name>进行修改。
rustup命令

以下列出rustup的部分命令：

> rsutup show : 列出现在使用的和已安装的rust版本。
> rustup update : 更新所有已安装版本，由于nightly偶尔会爆肝日更，所以谨慎更新。
> rustup default: 设置将要使用的版本。
> rustup component <sub> : 列出(list)、安装(add)、移除(remove)组建。

####  Cargo

cargo既是一个类似于npm、pip的包管理软件，又是一个像maven一样的项目框架。一个> cargo help可以让你懂得它有多nb。

```
build       编译当前包
check       检查当前包并寻出错误，但不进行编译
clean       删除编译结果（即target文件夹）
doc         构建当前包以及依赖项得文档
new         新建一个crate
init        以当前文件夹初始化一个crate
run         编译并执行src/main.rs
test        执行测试项
bench       执行基准测试项
update      更新所需的依赖项并预编译
search      搜索crates
publish     打包发布
install     安装cargo相关可执行文件，默认路径为 $HOME/.cargo/bin
uninstall   卸载相关可执行文件
```

#### 配置Crates.io国内镜像
新建C:\Users\[用户名]\.cargo\config(config文件不带扩展)，将以下内容写入config文件　　

```
[registry]
index = "https://mirrors.ustc.edu.cn/crates.io-index/"
[source.crates-io]
replace-with = 'ustc'
[source.ustc]
registry = "https://mirrors.ustc.edu.cn/crates.io-index/"
```

#### vscode 开发环境 插件安装
rust  

### [Rust的CLion调试方法](https://rustcc.cn/article?id=85282d12-6b84-4504-9a47-c1c3b3baa3fc)

####  通用步骤

1. 安装`rust`
2. 安装`CLion`以及`intellij-rust`插件
3. `CLion`开起`Rust`项目
4. 打上一个断点，然后点击`main`函数旁边的“播放”按钮，选中“虫子”
5. 程序将在你的断点处暂停

#### macOS下，我的环境为10.13

1. 安装`Command Line Tools`或者`xcode`
2. 剩下步骤与通用步骤下相同

#### Ubuntu下，我的环境为16.04

1. 安装`build-essential`和`git`
2. 剩下步骤与通用步骤下相同

#### Windows下，我的环境为Win10

1. 安装`msys2`, 我安装在 `C:\msys64\`

2. 运行`mingw64.exe`

3. 运行`pacman -S --noconfirm base-devel mingw-w64-x86_64-toolchain git`

4. 添加**配置**到`C:\Users\YourName\.cargo\config`

5. 添加`C:\msys64\usr\bin`（如果报冲突，这个就不添加）和`C:\msys64\mingw64\bin`到`Path`环境变量

6. 安装`rust`，选择`stable-gnu`或者`nightly-gnu`为默认工具链

7. 安装   CLion
   1. 并添加`MinGW`工具链到`CLion`，路径为`C:\msys64\mingw64`
   2. 安装`intellij-rust`插件

8. 剩下步骤与通用步骤相同

**配置**

```
[target.x86_64-pc-windows-gnu]
linker = "C:\\msys64\\mingw64\\bin\\gcc.exe"
ar = "C:\\msys2\\mingw64\\bin\\ar.exe"
```

如果你的`GDB`版本为`v8.2`及以上，那至少需要`CLion 2018.3`及以上版本
