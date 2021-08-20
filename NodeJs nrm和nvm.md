# NodeJs nrm和nvm

#### nrm 和 nvm

- 🚀 `nrm (npm registry manager)`是`npm`的镜像源管理工具 🚀
- 🚀 `nvm (node version manager)`是`nodejs`的版本管理工具 🚀

#### nrm

```bash
# nrm 安装
  npm install -g nrm

# nrm ls
  npm -------- https://registry.npmjs.org/
  yarn ------- https://registry.yarnpkg.com/
  cnpm ------- http://r.cnpmjs.org/
* taobao ----- https://registry.npm.taobao.org/
  nj --------- https://registry.nodejitsu.com/
  npmMirror -- https://skimdb.npmjs.com/registry/
  edunpm ----- http://registry.enpmjs.org/

# nrm use: 切换镜像源
  nrm use npm

# nrm use: 添加镜像源
  nrm add registry `http://registry.npm.frp.trmap.cn/`

# nrm del: 删除镜像源
  nrm del <registry>

# nrm test: 镜像源测速
  nrm test<registry>
```

#### nvm

```bash
# 查看已经安装的nodejs版本
  nvm ls

# 安装指定版本的nodejs
  nvm install <version>

# 切换到指定版本
  nvm use <version>

# 卸载指定版本
  nvm uninstall <version>

# 查看版本
  nvm -v

# 查看运行机器 bit mode
  nvm arch

# 查看帮助
  nvm -h
```
