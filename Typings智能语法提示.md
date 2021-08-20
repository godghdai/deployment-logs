一些js库扩展了JavaScript的特性和语法，但是TypeScript编译器并不识别，通过typings.json配置可以辅助IDE，给出有智能的提示信息，以及重构的依据。
因此需要在typings.json文件中配置TypeScript类型定义文件（文件名后缀为.d.ts）
[https://github.com/typings/typings](https://github.com/typings/typings)
### 全局安装typings
```shell
npm install typings --global
```

### 搜索
```shell
typings search module
npm install typings --global
```

### 查找
```shell
typings search --name module
npm install typings --global
```
#安装(默认使用npm)
```shell
typings install module --save
npm install typings --global
```

### 使用数据源为dt安装
```shell
typings install dt~module --global --save
npm install typings --global
```

### 其他数据源安装
```shell
typings install env~module --global --save
typings install npm~module --save
```

可以直接用github,后面为github的项目路径https://github.com/DefinitelyTyped/DefinitelyTyped #后面为提交的版本号，可以不写
```shell
typings install github:DefinitelyTyped/DefinitelyTyped/jasmine/jasmine.d.ts#38fb591c6eba840e0b53d1110302b8e4fb04652c --global --save
```

#显示所有引用
```shell
cat typings/index.d.ts
```

### 数据源
- npm - dependencies from NPM 
- github - dependencies directly from GitHub (E.g. Duo, JSPM)
- bower - dependencies from Bower
- common - "standard" libraries without a known "source"
- shared - shared library functionality
- lib - shared environment functionality (mirror of shared) (--global)
- env - environments (E.g. atom, electron) (--global)
- global - global (window.<var>) libraries (--global)
- dt - typings from DefinitelyTyped (usually --global)
