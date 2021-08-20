# NodeJS使用Babel

## 安装依赖

```shell
npm install --save-dev @babel/core @babel/cli @babel/preset-env
npm install -g nodemon
#装饰器
npm install --save-dev @babel/plugin-proposal-class-properties
npm install --save-dev @babel/plugin-proposal-decorators
```

## 配置文件

###  babel.config.json

```js
{
  "presets": [
    [
      "@babel/env",
      {
        "targets": {
          "node": "current"
        },
        "useBuiltIns": "usage",
        "corejs": "3.6.5"
      }
    ]
  ],
  "plugins": [
    ["@babel/plugin-proposal-decorators", { "legacy": true }],
    ["@babel/plugin-proposal-class-properties", { "loose" : true }]
  ]
}
```

###  nodemon.json
```js
{
    "restartable": "rs",
    "ignore": [
        ".git",
        ".svn",
        "node_modules/**/node_modules"
    ],
    "verbose": true,
    "execMap": {
        "js": "node --harmony"
    },
    "watch": [
        "src/*"
    ],
    "env": {
        "NODE_ENV": "development"
    },
    "ext": "ejs js json"
}
```

### package.json

```js
{
  "name": "es66",
  "version": "1.0.0",
  "main": "index.js",
  "dependencies": {},
  "devDependencies": {
    "@babel/cli": "^7.14.8",
    "@babel/core": "^7.15.0",
    "@babel/plugin-proposal-class-properties": "^7.14.5",
    "@babel/plugin-proposal-decorators": "^7.14.5",
    "@babel/preset-env": "^7.15.0"
  },
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "start": "nodemon -w src --exec node ./node_modules/@babel/cli/bin/babel ./src/main.js",
    "build": "node ./node_modules/@babel/cli/bin/babel src --out-dir dist"
  },
  "author": "",
  "license": "ISC",
  "description": ""
}
```

### 测试代码

```js
[1,3,4].forEach((num,index)=>{
    console.log(num);
})

const set = new Set([1, 2, 3]);
[1, 2, 3].includes(2);

async function a () {
    await new Promise(function(resolve, reject) {
      resolve(1)
    })
  } 


  function isTestable(value) {
    return function decorator(target) {
      target.isTestable = value;
    };
  }

  @isTestable(true)
  class MyClass {
      constructor(){
          this.name="dsf";
      }
      @isTestable(false)
      update(camera) {
        console.log(camera);
      }
  }
```
