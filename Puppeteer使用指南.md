## Puppeteer使用指南
#### 环境搭建

```shell
npm i puppeteer-core -S
npm i typescript ts-node -D
tsc -init
```
####  启动参数配置

```js
const browser = await puppeteer.launch({
        headless: false,
        timeout: 30000,
        ignoreDefaultArgs: ['--enable-automation', '--enable-blink-features=IdleDetection'],
        executablePath: `C:/Program Files/Google/Chrome/Application/chrome.exe`,
        userDataDir: `C:/Users/yzd/AppData/Local/Google/Chrome/User Data/`,
        args: [
            '--disable-extensions',
            '--no-first-run',
            '--no-default-browser-check',
            '--start-maximized'
        ],
        defaultViewport: {
            width: 1920,
            height: 1080
        }
    });
    const [page] = await browser.pages();
    await page.goto('https://www.ixigua.com/');
```

#### 四个简写的脚本执行命令

```
npm start === npm run start
npm stop === npm run stop
npm test === npm run test
npm restart === npm run stop && npm run restart && npm run start
```

nodejs 14 以后支持  与可选链操作符 ?.      ?? 空值合并运算符

es2019以后才支持

https://node.green/

https://www.jianshu.com/p/5e764cefd41e

React-Native/React/Redux snippets for es6/es7
