## NodeJS配置国内源

此方法不需要安装cnpm也可以使用淘宝镜像，提高国内访问速度

由于 Node 的官方模块仓库网速太慢，模块仓库需要切换到阿里的源。

### 临时

```shell
npm --registry https://registry.npm.taobao.org install xxx
```

### 全局

```shell
npm config set registry https://registry.npm.taobao.org 
```

执行下面的命令，确认是否切换成功。

```shell
npm config get registry
```

如果输出：https://registry.npm.taobao.org/，则表示切换成功

## npm源换回默认

```shell
npm config set registry https://registry.npmjs.org/
npm config get registry
```

## cnpm

cnpm是淘宝团队做的国内镜像，因为npm的服务器位于国外可能会影响安装速度。淘宝镜像与官方同步频率目前为 10分钟 一次以保证尽量与官方服务同步。

PS.网上有一些贴子说cnpm会丢包，如果遇到丢包，删除node_modules目录，再重新使用npm，总体来说网络上不太建议使用cnpm。

官网：https://developer.aliyun.com/mirror/NPM?from=tnpm

安装：命令提示符执行
`npm install cnpm -g --registry=https://registry.npm.taobao.org`

`cnpm -v` 来测试是否成功安装

安装完成后可以cnpm通过来代替默认的npm

```shell
cnpm install [name]
```

## nrm

- `nrm`包安装命令： `npm i nrm -g`
- `nrm`能够管理所用可用的镜像源地址以及当前所使用的镜像源地址，但是只是单纯的提供了几个url并能够让我们在这几个地址之间方便切换
- `nrm ls`即nrm list，查看所有可用的镜像，并可以切换。*号表示当前npm使用的地址，可以使用命令`nrm use taobao`或 `nrm use npm`来进行两者之间的切换。

```powershell
C:\Users\yzd>nrm ls
  npm -------- https://registry.npmjs.org/
  yarn ------- https://registry.yarnpkg.com/
  cnpm ------- http://r.cnpmjs.org/
* taobao ----- https://registry.npm.taobao.org/
  nj --------- https://registry.nodejitsu.com/
  npmMirror -- https://skimdb.npmjs.com/registry/
  edunpm ----- http://registry.enpmjs.org/
```

## npm参数 -g -S -D

- `-g`：全局安装。 将会安装在 `C:\Users\Administrator\AppData\Roaming\npm`，**并且写入系统环境变量**；非全局安装：将会安装在当前定位目录;全局安装可以通过命令行任何地方调用它，本地安装将安装在定位目录的node_modules文件夹下，通过要求调用;
- `-S`：即`npm install module_name --save`,写入`package.json`的`dependencies` ,`dependencies` 是需要发布到生产环境的，比如jq，vue全家桶，ele-ui等ui框架这些项目运行时必须使用到的插件就需要放到`dependencies`
- `-D`：即`npm install module_name --save-dev`,写入`package.json`的`devDependencies` ,`devDependencies` 里面的插件只用于开发环境，不用于生产环境。比如一些babel编译功能的插件、webpack打包插件就是开发时候的需要，真正程序打包跑起来并不需要的一些插件。
