目录
- [Sass、LESS 和 Stylus区别总结](#sassless-%E5%92%8C-stylus%E5%8C%BA%E5%88%AB%E6%80%BB%E7%BB%93)
    + [1. 什么是 CSS 预处理器](#1--%E4%BB%80%E4%B9%88%E6%98%AF-css-%E9%A2%84%E5%A4%84%E7%90%86%E5%99%A8)
    + [2.基本语法区别](#2%E5%9F%BA%E6%9C%AC%E8%AF%AD%E6%B3%95%E5%8C%BA%E5%88%AB)
    + [3.变量](#3%E5%8F%98%E9%87%8F)
      - [1. sass](#1--sass)
      - [2. less](#2-less)
      - [3. stylus](#3-stylus)
    + [4.嵌套](#4%E5%B5%8C%E5%A5%97)
    + [5.运算符](#5%E8%BF%90%E7%AE%97%E7%AC%A6)
    + [6.颜色函数](#6%E9%A2%9C%E8%89%B2%E5%87%BD%E6%95%B0)
      - [1. sass的颜色处理函数](#1-sass%E7%9A%84%E9%A2%9C%E8%89%B2%E5%A4%84%E7%90%86%E5%87%BD%E6%95%B0)
      - [2. Less css颜色处理函数](#2-less-css%E9%A2%9C%E8%89%B2%E5%A4%84%E7%90%86%E5%87%BD%E6%95%B0)
      - [3. Stylus颜色处理函数](#3-stylus%E9%A2%9C%E8%89%B2%E5%A4%84%E7%90%86%E5%87%BD%E6%95%B0)
    + [7.导入 (Import)](#7%E5%AF%BC%E5%85%A5-import)
    + [8. 继承](#8-%E7%BB%A7%E6%89%BF)
      - [1. sass](#1--sass-1)
      - [2. Less css：](#2-less-css)
    + [9. Mixins（混入）](#9-mixins%E6%B7%B7%E5%85%A5)
      - [1. Sass 的混入语法](#1-sass-%E7%9A%84%E6%B7%B7%E5%85%A5%E8%AF%AD%E6%B3%95)
      - [2. Less CSS 的混入语法](#2-less-css-%E7%9A%84%E6%B7%B7%E5%85%A5%E8%AF%AD%E6%B3%95)
      - [3. Stylus 的混入语法](#3-stylus-%E7%9A%84%E6%B7%B7%E5%85%A5%E8%AF%AD%E6%B3%95)
    + [10. 3D文本](#10-3d%E6%96%87%E6%9C%AC)
      - [1. sass](#1-sass)
      - [2. Less CSS](#2-less-css)
      - [3. Stylus](#3-stylus)
    + [11. 列 (Columns)](#11-%E5%88%97-columns)
      - [1. Sass](#1-sass)
      - [2. Less CSS](#2-less-css-1)
      - [3. Stylus](#3-stylus-1)
    + [12.高级语法](#12%E9%AB%98%E7%BA%A7%E8%AF%AD%E6%B3%95)
      - [sass中高级语法](#sass%E4%B8%AD%E9%AB%98%E7%BA%A7%E8%AF%AD%E6%B3%95)
        * [条件语句](#%E6%9D%A1%E4%BB%B6%E8%AF%AD%E5%8F%A5)
        * [for循环](#for%E5%BE%AA%E7%8E%AF)

----
CSS 预处理器技术已经非常的成熟了，而且也涌现出了越来越多的 CSS 的预处理器框架。本文便总结下 Sass、Less CSS、Stylus这三个预处理器的区别和各自的基本语法。

### 1.  什么是 CSS 预处理器

CSS 预处理器是一种语言用来为 CSS 增加一些编程的的特性，无需考虑浏览器的兼容性问题，例如你可以在 CSS 中使用变量、简单的程序逻辑、函数等等在编程语言中的一些基本技巧，可以让CSS 更见简洁，适应性更强，代码更直观等诸多好处。

### 2.基本语法区别

在使用 CSS 预处理器之前最重要的是理解语法，幸运的是基本上大多数预处理器的语法跟 CSS 都差不多。

首先 Sass 和 Less 都使用的是标准的 CSS 语法，因此如果可以很方便的将已有的 CSS 代码转为预处理器代码，默认 Sass 使用 .sass 扩展名，而 Less 使用 .less 扩展名。

```css
/* style.scss or style.less */
h1 {
  color: #0982C1;
}
```

这是一个再普通不过的，不过 Sass 同时也支持老的语法，就是不包含花括号和分号的方式：

```css
/* style.sass */
h1
  color: #0982c1
```

而 Stylus 支持的语法要更多样性一点，它默认使用 .styl 的文件扩展名，下面是 Stylus 支持的语法：

```css
/* style.styl */
h1 {
  color: #0982C1;
}

/* omit brackets */
h1
  color: #0982C1;

/* omit colons and semi-colons */
h1
  color #0982C1
```

可以在同一个样式单中使用不同的变量，例如下面的写法也不会报错：

```css
h1 {
  color #0982c1
}
h2
  font-size: 1.2em
```

### 3.变量

#### 1.  sass

Sass让人们受益的一个重要特性就是它为css引入了变量。你可以把反复使用的css属性值 定义成变量，然后通过变量名来引用它们，而无需重复书写这一属性值。

     sass变量必须是以$开头的，然后变量和值之间使用冒号（：）隔开，和css属性是一样的，例如：

```css
$maincolor : #092873;
$siteWidth : 1024px;
$borderStyle : dotted;
body {
  color: $maincolor;
  border: 1px $borderStyle $mainColor;
  max-width: $siteWidth;
}
```

#### 2. less

在less文件中，当一个值需要反复使用时，可以通过@符号定义变量。已经被赋值的变量以及其他的常量（如像素、颜色等）都可以参与运算。

 Less css中变量都是用@开头的，其余与sass都是一样的，例如：

```css
@maincolor : #092873;
@siteWidth : 1024px;
@borderStyle : dotted;
body {
  color: @maincolor;
  border: 1px @borderStyle @mainColor;
  max-width: @siteWidth;
}
```

#### 3. stylus

 stylus对变量是没有任何设定的，可以是以$开头，或者任何的字符，而且与变量之间可以用冒号，空格隔开，
 但是在stylus中不能用@开头，例如：    

```css
maincolor = #092873
siteWidth = 1024px
borderStyle = dotted
body 
  color maincolor
  border 1px borderStyle mainColor
  max-width siteWidth
```

以上三种写法都如同一下这种css：

```css
body {
  color: #092873;
  border: 1px dotted #092873;
  max-width: 1024px;
}
```

这样做的好处也是显而易见的，在修改多处相同颜色的时候，这时就只需要修改变量值即可。

### 4.嵌套

如果我们需要在CSS中相同的 parent 引用多个元素，这将是非常乏味的，你需要一遍又一遍地写 parent。例如：

```css
div {
  margin: 10px;
}
div nav {
  height: 25px;
}
div nav a {
  color: #0982C1;
}
div nav a:hover {
  text-decoration: underline;
}
```

如果用 CSS 预处理器，就可以少写很多单词，而且父子节点关系一目了然，并且sass，Less，stylus都支持下面这样的写法，且都是相同的：

```css
//scss style //----------------------------------- 
nav { 
    ul { 
       margin: 0; 
       padding: 0; 
    } 
    li { 
       display: inline-block; 
    } 
    a { 
       display: block; 
       padding: 6px 12px; 
       text-decoration: none; 
    } 
}
//css style //----------------------------------- 
nav ul { 
    margin: 0; 
    padding: 0; 
    list-style: none; 
} 
nav li { 
    display: inline-block; 
} 
nav a { 
    display: block; 
    padding: 6px 12px; 
    text-decoration: none; 
}
```

这样做是非常方便的，也很直观。

### 5.运算符

在 CSS 预处理器中还是可以进行样式的计算如下：

```css
body {
  margin: (14px/2);
  top: 50px + 100px;
  right: 80 * 10%;
}
```

在sass，Less与stylus中都是可以这样做的。

### 6.颜色函数

CSS 预处理器一般都会内置一些颜色处理函数用来对颜色值进行处理，例如加亮、变暗、颜色梯度等。

#### 1. sass的颜色处理函数

```css
lighten($color, 10%); 
darken($color, 10%);  
saturate($color, 10%);   
desaturate($color, 10%);
grayscale($color);  
complement($color); 
invert($color); 
mix($color1, $color2, 50%); 
```

实例如下：

```css
$color: #0982C1;
h1 {
  background: $color;
  border: 3px solid darken($color, 50%);
}
```

#### 2. Less css颜色处理函数

```css
lighten(@color, 10%); 
darken(@color, 10%);  
saturate(@color, 10%);  
desaturate(@color, 10%); 
spin(@color, 10); 
spin(@color, -10); 
mix(@color1, @color2);
```

示例如下：

```css
@color: #0982C1;
h1 {
  background: @color;
  border: 3px solid darken(@color, 50%);
```

#### 3. Stylus颜色处理函数

```css
lighten(color, 10%); 
darken(color, 10%);  
saturate(color, 10%);  
desaturate(color, 10%); 
```

示例如下;

```css
color = #0982C1 
h1
  background color
  border 3px solid darken(color, 50%)
```

### 7.导入 (Import)

很多 CSS 开发者对导入的做法都不太感冒，因为它需要多次的 HTTP 请求。但是在 CSS 预处理器中的导入操作则不同，它只是在语义上包含了不同的文件，但最终结果是一个单一的 CSS 文件，如果你是通过 @ import “file.css”; 导入 CSS 文件，那效果跟普通的 CSS 导入一样。

注意：导入文件中定义的混入、变量等信息也将会被引入到主样式文件中，因此需要避免它们互相冲突。
例如：

```css
//1.css
/* file.{type} */
body {
  background: #000;
}
```

```css
@ import "1.css";
@ import "file.{type}";

p {
  background: #092873;
}
```

最终生成的 CSS：

```css
@ import "1.css";
body {
  background: #000;
}
p {
  background: #092873;
}
```

### 8. 继承

当我们需要为多个元素定义相同样式的时候，我们可以考虑使用继承的做法.

#### 1.  sass

sass可通过@extend来实现代码组合声明，使代码更加优越简洁。

```css
.message {
  border: 1px solid #ccc;
  padding: 10px;
  color: #333;
}
.success {
  @extend .message;
  border-color: green;
}
.error {
  @extend .message;
  border-color: red;
}
.warning {
  @extend .message;
  border-color: yellow;
}
```

#### 2. Less css

但是在这方面 Less 表现的稍微弱一些，更像是混入写法：

```css
.message {
  border: 1px solid #ccc;
  padding: 10px;
  color: #333;
}
.success {
  .message;
  border-color: green;
}
.error {
  .message;
  border-color: red;
}
.warning {
  .message;
  border-color: yellow;
}
```

上面两种写法其最终呈现的css样式都如下：

```css
.message, .success, .error, .warning {
  border: 1px solid #cccccc;
  padding: 10px;
  color: #333;
}
.success {
  border-color: green;
}
.error {
  border-color: red;
}
.warning {
  border-color: yellow;
}
```

.message的样式将会被插入到相应的你想要继承的选择器中，但需要注意的是优先级的问题。

### 9. Mixins（混入）

Mixins 有点像是函数或者是宏，当某段 CSS 经常需要在多个元素中使用时，可以为这些共用的 CSS 定义一个 Mixin，然后只需要在需要引用这些 CSS 地方调用该 Mixin 即可。

#### 1. Sass 的混入语法

sass中可用mixin定义一些代码片段，且可传参数，方便日后根据需求调用。比如说处理css3浏览器前缀：

```css
@mixin error($borderWidth: 2px) {
  border: $borderWidth solid #F00;
  color: #F00;
}
.generic-error {
  padding: 20px;
  margin: 4px;
  @ include error(); //这里调用默认 border: 2px solid #F00;
}
.login-error {
  left: 12px;
  position: absolute;
  top: 20px;
  @ include error(5px); //这里调用 border:5px solid #F00;
}
```

#### 2. Less CSS 的混入语法

less也支持带参数的混合以及有默认参数值的混合，如下面的例子所示：

```css
.error(@borderWidth: 2px) {
  border: @borderWidth solid #F00;
  color: #F00;
}
.generic-error {
  padding: 20px;
  margin: 4px;
  .error(); //这里调用默认 border: 2px solid #F00;
}
.login-error {
  left: 12px;
  position: absolute;
  top: 20px;
  .error(5px); //这里调用 border:5px solid #F00;
}
```

#### 3. Stylus 的混入语法

```css
error(borderWidth= 2px) {
  border: borderWidth solid #F00;
  color: #F00;
}
.generic-error {
  padding: 20px;
  margin: 4px;
  error(); 
}
.login-error {
  left: 12px;
  position: absolute;
  top: 20px;
  error(5px); 
}
```

他们最终呈现的效果都如下：

```css
.generic-error {
  padding: 20px;
  margin: 4px;
  border: 2px solid #f00;
  color: #f00;
}
.login-error {
  left: 12px;
  position: absolute;
  top: 20px;
  border: 5px solid #f00;
  color: #f00;
}
```

### 10. 3D文本

要生成具有 3D 效果的文本可以使用 text-shadows ，唯一的问题就是当要修改颜色的时候就非常的麻烦，而通过 mixin 和颜色函数可以很轻松的实现：

#### 1. sass

```css
@mixin text3d($color) {
  color: $color;
  text-shadow: 1px 1px 0px darken($color, 5%),
               2px 2px 0px darken($color, 10%),
               3px 3px 0px darken($color, 15%),
               4px 4px 0px darken($color, 20%),
               4px 4px 2px #000;
}

h1 {
  font-size: 32pt;
  @ include text3d(#0982c1);
}
```

#### 2. Less CSS

```css
.text3d(@color) {
  color: @color;
  text-shadow: 1px 1px 0px darken(@color, 5%),
               2px 2px 0px darken(@color, 10%),
               3px 3px 0px darken(@color, 15%),
               4px 4px 0px darken(@color, 20%),
               4px 4px 2px #000;
}

span {
  font-size: 32pt;
  .text3d(#0982c1);
}
```

#### 3. Stylus

```css
text3d(color)
  color: color
  text-shadow: 1px 1px 0px darken(color, 5%), 
               2px 2px 0px darken(color, 10%), 
               3px 3px 0px darken(color, 15%), 
               4px 4px 0px darken(color, 20%), 
               4px 4px 2px #000
span
  font-size: 32pt
  text3d(#0982c1)
```

其生成的css最终的效果如下：

```css
span {
  font-size: 32pt;
  color: #0982c1;
  text-shadow: 1px 1px 0px #097bb7,
               2px 2px 0px #0875ae,
               3px 3px 0px #086fa4,
               4px 4px 0px #07689a,
               4px 4px 2px #000;
}
```

### 11. 列 (Columns)

使用数值操作和变量可以很方便的实现适应屏幕大小的布局处理。

#### 1. Sass

```css
$siteWidth: 1024px;
$gutterWidth: 20px;
$sidebarWidth: 300px;
body {
  margin: 0 auto;
  width: $siteWidth;
}
.content {
  float: left;
  width: $siteWidth - ($sidebarWidth+$gutterWidth);
}
.sidebar {
  float: left;
  margin-left: $gutterWidth;
  width: $sidebarWidth;
}
```

#### 2. Less CSS

```css
@siteWidth: 1024px;
@gutterWidth: 20px;
@sidebarWidth: 300px;

body {
  margin: 0 auto;
  width: @siteWidth;
}
.content {
  float: left;
  width: @siteWidth - (@sidebarWidth+@gutterWidth);
}
.sidebar {
  float: left;
  margin-left: @gutterWidth;
  width: @sidebarWidth;
}
```

#### 3. Stylus

```css
siteWidth = 1024px;
gutterWidth = 20px;
sidebarWidth = 300px;

body {
  margin: 0 auto;
  width: siteWidth;
}
.content {
  float: left;
  width: siteWidth - (sidebarWidth+gutterWidth);
}
.sidebar {
  float: left;
  margin-left: gutterWidth;
  width: sidebarWidth;
}
```

其最终生成的css效果如下：

```css
body {
  margin: 0 auto;
  width: 1024px;
}
.content {
  float: left;
  width: 704px;
}
.sidebar {
  float: left;
  margin-left: 20px;
  width: 300px;
}
```

### 12.高级语法

#### sass中高级语法

##### 条件语句

```css
@if可一个条件单独使用，也可以和@else结合多条件使用
```

代码如下：

```css
$lte7: true;
$type: monster;
.ib{
    display:inline-block;
    @if $lte7 {
        *display:inline;
        *zoom:1;
    }
}
p {
  @if $type == ocean {
    color: blue;
  } @else if $type == matador {
    color: red;
  } @else if $type == monster {
    color: green;
  } @else {
    color: black;
  }
}
```

其最终的css代码如下：

```css
.ib{
    display:inline-block;
    *display:inline;
    *zoom:1;
}
p {
  color: green; 
}
```

##### for循环

for循环有两种形式，分别为：

```css
1.@for $var from <start> through <end>
2.@for $var from <start> to <end>。
```

其中$i表示变量，start表示起始值，end表示结束值，这两个的区别是关键字through表示包括end这个数，而to则不包括end这个数。

```css
@for $i from 1 to 10 {
  .border-#{$i} {
    border: #{$i}px solid blue;
  }
}
```

同时也支持while循环：

```css
$i: 6;
@while $i > 0 {
  .item-#{$i} { width: 2em * $i; }
  $i: $i - 2;
}
```

最后，同时支持each命令，作用与for类似：

```css
$animal-list: puma, sea-slug, egret, salamander;
@each $animal in $animal-list {
  .#{$animal}-icon {
    background-image: url('/images/#{$animal}.png');
  }
}
```

其css最终效果如下：

```css
.puma-icon {
  background-image: url('/images/puma.png'); 
}
.sea-slug-icon {
  background-image: url('/images/sea-slug.png'); 
}
.egret-icon {
  background-image: url('/images/egret.png'); 
}
.salamander-icon {
  background-image: url('/images/salamander.png'); 
}
```


以上就是sass，Less css与stylus的最显著的区别。


>版权声明：本文为CSDN博主「黛梨」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
>原文链接：https://blog.csdn.net/pedrojuliet/article/details/72887490
