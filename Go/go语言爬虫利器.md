# 目录

- [go语言爬虫利器](#go%E8%AF%AD%E8%A8%80%E7%88%AC%E8%99%AB%E5%88%A9%E5%99%A8)
  * [chromedp](#chromedp)
    + [示例：下载西瓜视频](#%E7%A4%BA%E4%BE%8B%E4%B8%8B%E8%BD%BD%E8%A5%BF%E7%93%9C%E8%A7%86%E9%A2%91)
  * [goquery](#goquery)
    + [选择器](#%E9%80%89%E6%8B%A9%E5%99%A8)
      - [元素的选择器](#%E5%85%83%E7%B4%A0%E7%9A%84%E9%80%89%E6%8B%A9%E5%99%A8)
      - [ID 选择器](#id-%E9%80%89%E6%8B%A9%E5%99%A8)
      - [Class选择器](#class%E9%80%89%E6%8B%A9%E5%99%A8)
      - [属性选择器](#%E5%B1%9E%E6%80%A7%E9%80%89%E6%8B%A9%E5%99%A8)
      - [parent > child](#parent--child)
      - [element + next](#element--next)
      - [element~next](#elementnext)
    + [过滤器](#%E8%BF%87%E6%BB%A4%E5%99%A8)
      - [:contains](#contains)
      - [:first-child和:first-of-type](#first-child%E5%92%8Cfirst-of-type)
      - [:last-child 和:last-of-type](#last-child-%E5%92%8Clast-of-type)
      - [:nth-child(n)](#nth-childn)
      - [:nth-of-type(n)](#nth-of-typen)
      - [:nth-last-child(n) 和:nth-last-of-type(n)](#nth-last-childn-%E5%92%8Cnth-last-of-typen)
      - [:only-child 和 :only-of-type](#only-child-%E5%92%8C-only-of-type)
    + [常用方法](#%E5%B8%B8%E7%94%A8%E6%96%B9%E6%B3%95)
      - [类似函数的位置操作](#%E7%B1%BB%E4%BC%BC%E5%87%BD%E6%95%B0%E7%9A%84%E4%BD%8D%E7%BD%AE%E6%93%8D%E4%BD%9C)
      - [循环遍历选择的节点](#%E5%BE%AA%E7%8E%AF%E9%81%8D%E5%8E%86%E9%80%89%E6%8B%A9%E7%9A%84%E8%8A%82%E7%82%B9)
      - [检测或获取节点属性值](#%E6%A3%80%E6%B5%8B%E6%88%96%E8%8E%B7%E5%8F%96%E8%8A%82%E7%82%B9%E5%B1%9E%E6%80%A7%E5%80%BC)
      - [常用的查找节点方法](#%E5%B8%B8%E7%94%A8%E7%9A%84%E6%9F%A5%E6%89%BE%E8%8A%82%E7%82%B9%E6%96%B9%E6%B3%95)

## chromedp

chromedp是一个golang编写的适用于**Chrome DevTools Protocol**的程序，通过它我们可以非常方便地操作浏览器，对于一些需要浏览器js解析的dom树，我们就可以使用chromedp来等待浏览器解析之后进行数据分析。和phantomjs和selenium相比，chromedp不需要其它的依赖，一个可执行文件就可以直接调用访问无头chrome.应为chromedp实现了chrome devtools protocol 协议，所以我们常用的点击，提交，上传，截图都是可以轻松使用代码来实现。

安装

```
 go get -u github.com/chromedp/chromedp
```
- https://github.com/chromedp/chromedp
- https://github.com/chromedp/examples
- https://github.com/ChromeDevTools/awesome-chrome-devtools
- https://chromedevtools.github.io/devtools-protocol/

```
//chrome开启调试端口
chrome --remote-debugging-port=9222
```
### 示例：下载西瓜视频

```go
package main

import (
   "bufio"
   "context"
   "fmt"
   "github.com/chromedp/cdproto/network"
   "github.com/chromedp/cdproto/runtime"
   "github.com/chromedp/chromedp"
   "io"
   "io/ioutil"
   "log"
   "net/http"
   "os"
)

type Video struct {
   Definition string `json:"definition"`
   MainUrl    string `json:"main_url"`
   Bitrate    int32  `json:"bitrate"`
}
type Audio struct {
   MainUrl string `json:"main_url"`
   Bitrate int32  `json:"bitrate"`
}

type Dash struct {
   DynamicType string  `json:"dynamic_type"`
   MainUrl     string  `json:"main_url"`
   VideoList   []Video `json:"dynamic_video_list"`
   AudioList   []Audio `json:"dynamic_audio_list"`
}


// 加载Cookies
func loadCookies() chromedp.ActionFunc {
   return func(ctx context.Context) (err error) {
      if _, _err := os.Stat("cookies.tmp"); os.IsNotExist(_err) {
         return
      }
      cookiesData, err := ioutil.ReadFile("cookies.tmp")
      if err != nil {
         return
      }
      cookiesParams := network.SetCookiesParams{}
      if err = cookiesParams.UnmarshalJSON(cookiesData); err != nil {
         return
      }
      return network.SetCookies(cookiesParams.Cookies).Do(ctx)
   }
}

func download(filename string,url string)  {
   res, err := http.Get(url)
   if err != nil {
      fmt.Println("A error occurred!")
      return
   }
   defer res.Body.Close()

   reader := bufio.NewReaderSize(res.Body, 32 * 1024)
   file, err := os.Create( filename + ".mp4")
   if err != nil {
      panic(err)
   }
   writer := bufio.NewWriter(file)
   written, _ := io.Copy(writer, reader)
   fmt.Printf("Total length: %d", written)
}
func main()  {
   title:= downloadStart("https://www.ixigua.com/6674912660305216007?logTag=3d73f800b4963dbe7adf")
   err := Merge("1.mp4", "2.mp4", title+".mp4")
   if err != nil {
      return
   }
}
func downloadStart(startUrl string) string {
   dir, err := ioutil.TempDir("", "chromedp-example")
   if err != nil {
      log.Fatal(err)
   }
   defer os.RemoveAll(dir)
   //chrome_data_dir := filepath.Join(os.Getenv("USERPROFILE"), `AppData\Local\Google\Chrome\User Data\`)
   opts := []chromedp.ExecAllocatorOption{
      chromedp.DisableGPU,
      chromedp.UserDataDir(dir),
      chromedp.Flag("start-maximized", true),
      chromedp.Flag("disable-extensions", true),
      chromedp.Flag("no-first-run", true),
      chromedp.Flag("no-default-browser-check", true),
      chromedp.Flag("start-maximized", true),
      chromedp.Flag("enable-automation", false),
      chromedp.Flag("enable-blink-features=IdleDetection", false),
      //chromedp.Flag("proxy-server","http://127.0.0.1:8001"),
   }

   allocCtx, cancel := chromedp.NewExecAllocator(context.Background(), opts...)
   defer cancel()

   // also set up a custom logger
   taskCtx, cancel := chromedp.NewContext(allocCtx, chromedp.WithLogf(log.Printf))
   defer cancel()

   downloadComplete := make(chan bool)
   var downloadURL = "https://sf1-cdn-tos.toutiaostatic.com/obj/rc-web-sdk/acrawler.js"
   var requestId network.RequestID
   chromedp.ListenTarget(taskCtx, func(v interface{}) {
      switch ev := v.(type) {
      case *network.EventRequestWillBeSent:
         fmt.Printf("EventRequestWillBeSent: %v: %v\n", ev.RequestID, ev.Request.URL)
         if ev.Request.URL == downloadURL {
            requestId = ev.RequestID
         }
      case *network.EventLoadingFinished:
         fmt.Printf("EventLoadingFinished: %v\n", ev.RequestID)
         if ev.RequestID == requestId {
            close(downloadComplete)
         }
      }
   })

   var res = Dash{}
   var title string
   // ensure that the browser process is started
   if err := chromedp.Run(taskCtx,
      chromedp.Navigate(startUrl),
      chromedp.WaitVisible(`#player_default`),
      chromedp.ActionFunc(func(ctx context.Context) error {
         p := runtime.Evaluate("window._SSR_HYDRATED_DATA.anyVideo.gidInformation.packerData.video.videoResource.dash.dynamic_video")
         p = p.WithReturnByValue(true)
         v, exp, err := p.Do(ctx)
         if err != nil {
            return err
         }
         if exp != nil {
            return exp
         }
         fmt.Printf("%s", v.Value)
         return nil
      }),
      chromedp.ActionFunc(func(ctx context.Context) error {
         cookies, err := network.GetAllCookies().Do(ctx)
         if err != nil {
            return err
         }
         cookiesData, err := network.GetAllCookiesReturns{Cookies: cookies}.MarshalJSON()
         if err != nil {
            return err
         }
         if err = ioutil.WriteFile("cookies.tmp", cookiesData, 0755); err != nil {
            return err
         }
         return nil
      }),
      chromedp.Evaluate("window._SSR_HYDRATED_DATA.anyVideo.gidInformation.packerData.video.videoResource.dash.dynamic_video", &res),
      chromedp.Evaluate(`document.querySelector(".videoTitle h1").innerText`, &title),
   ); err != nil {
      log.Fatal(err)
   }

   <-downloadComplete

   var downloadBytes []byte
   if err := chromedp.Run(taskCtx, chromedp.ActionFunc(func(ctx context.Context) error {
      var err error
      downloadBytes, err = network.GetResponseBody(requestId).Do(ctx)
      return err
   })); err != nil {
      log.Fatal(err)
   }

   // write the file to disk - since we hold the bytes we dictate the name and location
   downloadDest := "download.js"
   if err := ioutil.WriteFile(downloadDest, downloadBytes, 0777); err != nil {
      log.Fatal(err)
   }

   log.Printf("Download Complete: %v", downloadDest)

   for _, video := range res.VideoList {
      fmt.Printf("%s\n", video.MainUrl)
   }

   for _, audio := range res.AudioList {
      fmt.Printf("%s\n", audio.MainUrl)
   }
   download("1","http:"+res.VideoList[0].MainUrl)
   download("2","http:"+res.AudioList[0].MainUrl)
   return title
}
```

## goquery

go语言的爬虫利器goquery，类似jquery，它是jquery的go版本实现，使用它，可以很方便的对HTML进行处理。goquery是基于 Go net/htm包和css选择器库 cascadia。由于net/htm解析器返回的是DOM节点,而不是完整的DOM树,因此, jQuery的状态操作函数没有实现(像height(), css(), detach)

> 注意：goquery只支持utf-8编码，其他编码需要转换
>


```
 go get github.com/PuerkitoBio/goquery
```

- https://github.com/PuerkitoBio/goquery

###  选择器

上面的例子中，我们使用了`元素选择器`,goquery跟jquery一样都支持很多选择器，我们简单的介绍下常用的选择器：

#### 元素的选择器

就是基于a,p等这些HTML的基本元素进行选择。

使用方法 ：使用语法为 `dom.Find("p")`，匹配文档中所有的p标签。

#### ID 选择器
ID选择器是我们使用最频繁的，假如我们有2个p元素，其实我们只需要其中的一个，那么我们只需要给这个标记一个唯一的id即可，这样我们就可以使用id选择器，精确定位了。

使用方法 ：id选择器以`#`开头，紧跟着元素id的值，使用语法为
`dom.Find("#title")` ，匹配文档中所有的 id=title的内容

如果多个标签的ID都是title，我们可以指定某一个标签,如`dom.Find("p#title")`

#### Class选择器

类选择跟ID选择器一样都是使用很频繁的，我们可以通过类选择器快速筛选到需要的内容。

使用方法 ： id选择器以`.`开头，紧跟着元素class的值，使用语法为`dom.Find(".content1")`，匹配文档中所有的 id=title的元素。

类选择权器跟ID选择器一样,也可以指定某一个标签`dom.Find("div.content1")`

#### 属性选择器

一个HTML元素都有自己的属性以及属性值，所以我们也可以通过属性和值筛选元素。

使用方法 ：我们可以通过元素的属性和属性值来筛选数据，使用语法为`dom.Find("p[class=content1]`，匹配文档中所有的 p标签的class属性是content1的元素。

当然我们这里以class属性为例，还可以用其他属性，比如href等很多，自定义属性也是可以的。

刚刚我们使用的是`完全相等`的匹配方式，属性选择器还要很多匹配方式。

| 选择器              | 说明                                                |
| :------------------ | :-------------------------------------------------- |
| Find(“div[my]“)     | 筛选含有my属性的div元素                             |
| Find(“div[my=zh]“)  | 筛选my属性为zh的div元素                             |
| Find(“div[my!=zh]“) | 筛选my属性不等于zh的div元素                         |
| Find(“div[my¦=zh]“) | 筛选my属性为zh或者zh-开头的div元素                  |
| Find(“div[my*=zh]“) | 筛选my属性包含zh这个字符串的div元素                 |
| Find(“div[my~=zh]“) | 筛选my属性包含zh这个单词的div元素，单词以空格分开的 |
| Find(“div[my$=zh]“) | 筛选my属性以zh结尾的div元素，区分大小写             |
| Find(“div[my^=zh]“) | 筛选my属性以zh开头的div元素，区分大小写             |

#### parent > child

筛选出某个元素下的子元素。

使用方法：使用`>`符号连接，使用语法 `dom.Find("div>p")` ， 筛选div标签下的p标签

#### element + next

如果要筛选的元素没有规律，但是该元素的上一个元素有规律，我们就可以使用这种下一个相邻选择器来进行选择。

如：

```
<div>
<p my="a">a</p>
<p>b</p>
<p>c</p>
<div>
12345
```

我想筛选出`b`所在的标签

使用方法：`dom.Find("p[my=a]+p")`筛选出p标签属性my的值为a的相邻p标签。

#### element~next

有时候我们需要筛选同一父元素下，不相邻的标签，可以使用兄弟选择器

比如我想筛选出 b 和c 所在标签
使用方法：`dom.Find("p[my=a]~p")`，筛选出p标签属性my的值为a的兄弟p标签。

### 过滤器

有时候我们选择出来的结果，并不是我们心目中的最优结果，我们希望对其进行过滤。

#### :contains

筛选出的元素要包含指定的文本，比如我想筛选出包含a的p标签

使用方法：`dom.Find("p:contains(a)")`，筛选出内容包含a的p标签

Find(":has(selector)")和contains差不多，只不过这个是包含的是元素节点。

此外还有Find(":empty")表示筛选出的元素都不能有子元素（包括文本元素），只筛选那些不包含任何子元素的元素。

#### :first-child和:first-of-type
筛选出的元素要是他们的父元素的第一个子元素，如果不是，则不会被筛选出来。

使用方法：语法为Find(“p:first-child”)，筛选出第一个p标签

:first-child选择器限制的比较死，必须得是第一个子元素，如果该元素前有其他在前面，就不能用:first-child了，这时候:first-of-type就派上用场了，它要求只要是这个类型的第一个就可以。

#### :last-child 和:last-of-type
这两个正好和上面的:first-child、:first-of-type相反

#### :nth-child(n) 

筛选出的元素是其父元素的第n个元素，n以1开始。所以我们可以知道:first-child和:nth-child(1)是相等的。通过指定n，我们就很灵活的筛选出我们需要的元素。

#### :nth-of-type(n) 

:nth-of-type(n)和 :nth-child(n) 类似，只不过它表示的是同类型元素的第n个,所以:nth-of-type(1) 和 :first-of-type是相等的。

#### :nth-last-child(n) 和:nth-last-of-type(n) 

这两个和上面的类似，只不过是倒序开始计算的，最后一个元素被当成了第一个

#### :only-child 和 :only-of-type

筛选出父元素中，只有它自己的一个的元素。

### 常用方法

#### 类似函数的位置操作

- Find(selection) *Selection //根据选择器查找节点集
- Eq(index int) *Selection //根据索引获取某个节点集
- First() *Selection //获取第一个子节点集
- Last() *Selection //获取最后一个子节点集
- Next() *Selection //获取下一个兄弟节点集
- NextAll() *Selection //获取后面所有兄弟节点集
- Prev() *Selection //前一个兄弟节点集
- Get(index int) *html.Node //根据索引获取一个节点
- Index() int //返回选择对象中第一个元素的位置
- Slice(start, end int) *Selection //根据起始位置获取子节点集

#### 循环遍历选择的节点

- Each(f func(int, *Selection)) *Selection //遍历
- EachWithBreak(f func(int, *Selection) bool) *Selection //可中断遍历
- Map(f func(int, *Selection) string) (result []string) //返回字符串数组

#### 检测或获取节点属性值

- Attr(), RemoveAttr(), SetAttr() //获取，移除，设置属性的值
- AddClass(), HasClass(), RemoveClass(), ToggleClass()
- Html() //获取该节点的html
- Length() //返回该Selection的元素个数
- Text() //获取该节点的文本值

#### 常用的查找节点方法

- Children() //返回selection中各个节点下的孩子节点
- Contents() //获取当前节点下的所有节点
- Find() //查找获取当前匹配的元素
- Next() //下一个元素
- Prev() //上一个元素

