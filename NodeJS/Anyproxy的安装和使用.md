## Anyproxy的安装和使用
[帮助文档](https://github.com/alibaba/anyproxy/blob/master/docs/cn/src_doc.md)

#### 安装

```bash
npm install anyproxy -g
npm install pm2 -g
```
#### 下载证书

抓取https请求，电脑上必须安装证书

```shell
anyproxy 
```
```
C:\Users\yzd>anyproxy
[AnyProxy Log][2021-08-26 10:44:13]: Http proxy started on port 8001
[AnyProxy Log][2021-08-26 10:44:13]: web interface started on port 8002
```

浏览器中输入 http://127.0.0.1:8002/  Anyproxy管理界面-->RootCA-->Download-->rootCA.crt 下载的rootCA.crt

#### chrome浏览器安装证书

1. 地址栏输入 chrome://settings/security

2. 管理证书，选择受信任的根证书颁发机构，导入**rootCA.crt**

执行以下命令来启动anyproxy，-i参数开启https的支持

```shell
anyproxy -i
```

####  rule接口文档

规则模块应该符合cmd规范，一个典型的规则模块代码结构如下。模块中所有方法都是可选的，只需实现业务感兴趣的部分即可。

```js
module.exports = {
  // 模块介绍
  summary: 'my customized rule for AnyProxy',
  // 发送请求前拦截处理
  *beforeSendRequest(requestDetail) { /* ... */ },
  // 发送响应前处理
  *beforeSendResponse(requestDetail, responseDetail) { /* ... */ },
  // 是否处理https请求
  *beforeDealHttpsRequest(requestDetail) { /* ... */ },
  // 请求出错的事件
  *onError(requestDetail, error) { /* ... */ },
  // https连接服务器出错
  *onConnectError(requestDetail, error) { /* ... */ }
};
```


#### 编写rule

```js
// rule2.js
module.exports = {
    summary: 'a rule to hack response',
    * beforeSendRequest(requestDetail) {
        //console.dir(requestDetail);
    },
    * beforeSendResponse(requestDetail, responseDetail) {
        if (responseDetail.response.header['Content-Type'] == "video/mp4") {
            console.log(requestDetail.url);
        }
    }
    // * beforeDealHttpsRequest(requestDetail) {
    //     //只有返回`true`时，AnyProxy才会尝试替换证书、解析https。否则只做数据流转发，无法看到明文数据。
    //     return true;
    // }
}
```

```bash
anyproxy -i -r ./rule2.js
```
####  作为npm模块使用

AnyProxy可以作为一个npm模块使用，整合进其他工具。

> 如要启用https解析，请在代理服务器启动前自行调用`AnyProxy.utils.certMgr`相关方法生成证书，并引导用户信任安装。或引导用户使用`anyproxy-ca`方法。

```bash
npm i anyproxy -S
```
#### 创建代理服务器

* Class: AnyProxy.proxyServer

    ```js
    const proxy = new AnyProxy.proxyServer(options)
    ```
  
  * `options`
    * `port` {number} 必选，代理服务器端口
    * `rule` {object} 自定义规则模块
    * `throttle` {number} 限速值，单位kb/s，默认不限速
    * `forceProxyHttps` {boolean} 是否强制拦截所有的https，忽略规则模块的返回，默认`false`
    * `silent` {boolean} 是否屏蔽所有console输出，默认`false`
    * `dangerouslyIgnoreUnauthorized` {boolean} 是否忽略请求中的证书错误，默认`false`
    * `wsIntercept` {boolean} 是否开启websocket代理，默认`false`
    * `webInterface` {object} web版界面配置
      * `enable` {boolean} 是否启用web版界面，默认`false`
      * `webPort` {number} web版界面端口号，默认`8002
  
  #### 使用示例
  
   ```js
  const AnyProxy = require("anyproxy");
  const options = {
    port: 8001,
    rule: require("./rule2.js"),
    webInterface: {
      enable: true,
      webPort: 8002,
    },
    throttle: 10000,
    forceProxyHttps: true,
    wsIntercept: false, // 不开启websocket代理
    silent: false,
  };
  const proxyServer = new AnyProxy.ProxyServer(options);
  
  proxyServer.on("ready", () => {
    /* */
  });
  proxyServer.on("error", (e) => {
    /* */
  });
  proxyServer.start();
  
  //when finished
  proxyServer.close();
  
   ```
