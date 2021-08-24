# windows平台rust安装

#### 1、安装目录环境变量

　　RUSTUP_HOME　　D:\WorkSoftware\Rust\cargo

　　CARGO_HOME　　D:\WorkSoftware\Rust\rustup

#### 2、安装下载加速环境变量

　　RUSTUP_DIST_SERVER　　https://mirrors.ustc.edu.cn/rust-static

　　RUSTUP_UPDATE_ROOT　　https://mirrors.ustc.edu.cn/rust-static/rustup*

#### 3、下载安装
　　https://static.rust-lang.org/rustup/dist/x86_64-pc-windows-msvc/rustup-init.exe
  
```
安装过程中请选择第二项 “Customize installation” ！注意到default host triple中设置的是x86_64-pc-windows-msvc，而由于本文所使用的调试器是GDB，故需要修改为x86_64-pc-windows-gnu。default 　　　　　　toolchain请选择stable，即稳定版。nightly为前瞻版（更新频率快），'beta’为测试版，实际使用时我们仍需使用到nightly版，后文会提到。
```

#### 4、配置Crates.io国内镜像
　　新建C:\Users\[用户名]\.cargo\config(config文件不带扩展)，将以下内容写入config文件　　

```
[registry]
index = "https://mirrors.ustc.edu.cn/crates.io-index/"
[source.crates-io]
replace-with = 'ustc'
[source.ustc]
registry = "https://mirrors.ustc.edu.cn/crates.io-index/"
```

#### 5、vscode 开发环境 插件安装
　　rust  

####  6、新建项目

　　cargo new test
  
　　cd test
  
　　cargo run 报错 linker `link.exe` not found

安装c++build工具 默认安装即可
https://download.microsoft.com/download/5/f/7/5f7acaeb-8363-451f-9425-68a90f98b238/visualcppbuildtools_full.exe
