# cheerio
https://github.com/cheeriojs/cheerio

为服务器特别定制的，快速、灵活、实施的jQuery核心实现.

## 介绍

把HTML告诉你的服务器.

```
const cheerio = require('cheerio');
const $ = cheerio.load('<h2 class="title">Hello world</h2>');

$('h2.title').text('Hello there!');
$('h2').addClass('welcome');

$.html();
//=> <html><head></head><body><h2 class="title welcome">Hello there!</h2></body></html>
```

## 安装

```
npm install cheerio
```

## 特点

**❤ 相似的语法:**

cheerio实现了核心jQuery的子集。cheerio会从jQuery库中删除所有DOM矛盾和浏览器的尴尬部分,展示她真正华丽的API。

**ϟ 非常快:**

cheerio使用一个非常简单的、一致的DOM模型。作为一个结果分析、处理和呈现的工具非常有效。基础的端到端基准测试显示其速度是JSDOM的__8x__倍。

**❁ 非常的灵活:**

cheerio基于 @FB55's forgiving [htmlparser2](https://github.com/fb55/htmlparser2/)。cheerio可以解析几乎任何HTML或XML文档。

## 关于JSDOM?

我写cheerio主要是因为我发现我自己对JSDOM非常失望。对我来说,主要有三个点让我一直耿耿于怀:

**• JSDOM内建的解析太严格:**

JSDOM捆绑的HTML解析器不能处理今天许多流行的网站。

**• JSDOM 太慢了:**

解析大网站JSDOM有明显的延迟。

**• JSDOM 太笨重了:**

JSDOM的目标是提供一个正如我们在浏览器中所看到的相同DOM环境。我从未真正需要所有这些,我只是想要一个简单,熟悉HTML操作方法。

## 我什么时候会使用JSDOM

cheerio不能解决你所有的问题。我仍然会使用JSDOM如果我需要工作在服务器上的浏览器环境中,特别是如果我想自动化功能测试。

## API

### 我们会一直使用以下例子:

```
<ul id="fruits">
  <li class="apple">Apple</li>
  <li class="orange">Orange</li>
  <li class="pear">Pear</li>
</ul>
```

这是在所有的API例子中一直要使用的HTML例子。

### 加载

首先你需要加载HTML。jQuery的这一步是必须的,因为一个jQuery运行,常用DOM。在cheerio中,我们需要把HTML document传进去。

这是首选的方法:

```
var cheerio = require('cheerio'),
    $ = cheerio.load('<ul id="fruits">...</ul>');
```

根据情况,您还可以通过传递字符串来加载HTML字符串:

```
$ = require('cheerio');
$('ul', '<ul id="fruits">...</ul>');
```

或作为根:

```
$ = require('cheerio');
$('li', 'ul', '<ul id="fruits">...</ul>');
```

如果你需要修改默认的解析选项你也可以传一个额外的对象给`.load()`:

```
$ = cheerio.load('<ul id="fruits">...</ul>', {
    normalizeWhitespace: true,
    xmlMode: true
});
```

这些解析选项直接取自[htmlparser2](https://github.com/fb55/htmlparser2/wiki/Parser-options),因此也可以在cheerio中使用任何在`htmlparser2`中有效的选项。默认的选项是:

```
{
    normalizeWhitespace: false,
    xmlMode: false,
    decodeEntities: true
}
```

至于一个完整的选项列表和他们的影响,看 [this](https://github.com/fb55/DomHandler)和 [htmlparser2's options](https://github.com/fb55/htmlparser2/wiki/Parser-options).

### 选择器

cheerio和jQuery选择器的实现几乎是相同的,所以API非常相似。

#### $( selector, [context], [root] )

`selector` 在 `root` 的范围内搜索 `context` 。`selector`和`context`可以是一个字符串表达式,DOM元素,DOM元素的数组,或cheerio对象。`root` 通常是HTML文档字符串。

这个选择器方法的出发点是遍历和操作文档。就像jQuery,它是选择文档中元素的主要方法,但不像jQuery它基于CSSSelect库来实现大部分的选择器。

```
$('.apple', '#fruits').text()
//=> Apple

$('ul .pear').attr('class')
//=> pear

$('li[class=orange]').html()
//=> Orange
```

### 属性

获取和修改属性的方法。

#### .attr( name, value )

获取和设置属性的方法。在匹配集合中只能获取的第一个元素的属性值。如果你把属性值设置为空，就会删除该属性。你也可以像jQuery函数一样通过传递`键值` 和 `函数`来设置。

```
$('ul').attr('id')
//=> fruits

$('.apple').attr('id', 'favorite').html()
//=> <li class="apple" id="favorite">Apple</li>
```

> See http://api.jquery.com/attr/ for more information

#### .prop( name, value )

获取和设置属性的方法。获取唯一匹配集的第一元素的属性值。

```
$('input[type="checkbox"]').prop('checked')
//=> false

$('input[type="checkbox"]').prop('checked', true).val()
//=> ok
```

> See http://api.jquery.com/prop/ for more information

#### .data( name, value )

获取和设置数据属性的方法。获取或设置仅在匹配集合中的第一个元素的数据属性值。

```
$('<div data-apple-color="red"></div>').data()
//=> { appleColor: 'red' }

$('<div data-apple-color="red"></div>').data('apple-color')
//=> 'red'

var apple = $('.apple').data('kind', 'mac')
apple.data('kind')
//=> 'mac'
```

> See http://api.jquery.com/data/ for more information

#### .val( [value] )

获取和设置input, select, and textarea的值的方法。注：对于传递`键值`,`函数`的支持尚未实现。

```
$('input[type="text"]').val()
//=> input_text

$('input[type="text"]').val('test').html()
//=> <input type="text" value="test"/>
```

#### .removeAttr( name )

通过`name`属性移除属性

```
$('.pear').removeAttr('class').html()
//=> <li>Pear</li>
```

#### .hasClass( className )

检查任何一个匹配的元素中是否有`className`。

```
$('.pear').hasClass('pear')
//=> true

$('apple').hasClass('fruit')
//=> false

$('li').hasClass('pear')
//=> true
```

#### .addClass( className )

在所有匹配的元素中添加类。也像jQuery函数一样接受`函数`。

```
$('.pear').addClass('fruit').html()
//=> <li class="pear fruit">Pear</li>

$('.apple').addClass('fruit red').html()
//=> <li class="apple fruit red">Apple</li>
```

> See http://api.jquery.com/addClass/ for more information.

#### .removeClass( [className] )

从选定的元素中删除一个或多个空格分隔的class。如果removeClass函数的`className`是未定义的(即未传参数)，所有的class值会被删除。也像jQuery函数一样接受`函数`。

```
$('.pear').removeClass('pear').html()
//=> <li class="">Pear</li>

$('.apple').addClass('red').removeClass().html()
//=> <li class="">Apple</li>
```

> See http://api.jquery.com/removeClass/ for more information.

#### .toggleClass( className, [switch] )

从匹配的元素中添加或删除类，这取决于class的存在或切换参数的值。也像jQuery函数一样接受`函数`。

```
$('.apple.green').toggleClass('fruit green red').html()
//=> <li class="apple fruit red">Apple</li>

$('.apple.green').toggleClass('fruit green red', true).html()
//=> <li class="apple green fruit red">Apple</li>
```

> See http://api.jquery.com/toggleClass/ for more information.

#### .is( selector )

#### .is( element )

#### .is( selection )

#### .is( function(index) )

有任何元素匹配selector就返回true。如果使用判定函数，判定函数在选中的元素中执行，所以this指向当前的元素。

### Forms

#### .serializeArray()

将一组表单元素编码为一组键值对。

```
$('<form><input name="foo" value="bar" /></form>').serializeArray()
//=> [ { name: 'foo', value: 'bar' } ]
```

### Traversing

#### .find(selector)

#### .find(selection)

#### .find(node)

通过选择器、jQuery对象或元素来过滤，获取每个匹配元素的后代。

```
$('#fruits').find('li').length
//=> 3
$('#fruits').find($('.apple')).length
//=> 1
```

#### .parent([selector])

获得每个匹配元素的parent,可选择性的通过selector筛选。

```
$('.pear').parent().attr('id')
//=> fruits
```

#### .parents([selector])

获得通过选择器筛选匹配的元素的parent集合。

```
$('.orange').parents().length
// => 2
$('.orange').parents('#fruits').length
// => 1
```

#### .parentsUntil([selector][,filter])

获取从匹配元素到其指定的祖先元素之间的所有节点（不包括那个指定的祖先元素）。

```
$('.orange').parentsUntil('#food').length
// => 1
```

#### .closest(selector)

获得离他最近的祖先元素(可以包括他自己，但不包括其兄弟节点)。

```
$('.orange').closest()
// => []
$('.orange').closest('.apple')
// => []
$('.orange').closest('li')
// => [<li class="orange">Orange</li>]
$('.orange').closest('#fruits')
// => [<ul id="fruits"> ... </ul>]
```

#### .next([selector])

获取他的下一个兄弟节点。

```
$('.apple').next().hasClass('orange')
//=> true
```

#### .nextAll([selector])

获取在他的后面的所有兄弟节点。

```
$('.apple').nextAll()
//=> [<li class="orange">Orange</li>, <li class="pear">Pear</li>]
$('.apple').nextAll('.orange')
//=> [<li class="orange">Orange</li>]
```

#### .nextUntil([selector], [filter])

获取从他本身到指定节点之间的所有节点(不包括他本身和指定节点)。

```
$('.apple').nextUntil('.pear')
//=> [<li class="orange">Orange</li>]
```

#### .prev([selector])

获取选定元素的前一个兄弟节点，可以选择一个选择器筛选。

```
$('.orange').prev().hasClass('apple')
//=> true
```

#### .prevAll([selector])

获取在指定元素的前面的所有兄弟节点。

```
$('.pear').prevAll()
//=> [<li class="orange">Orange</li>, <li class="apple">Apple</li>]
$('.pear').prevAll('.orange')
//=> [<li class="orange">Orange</li>]
```

#### .prevUntil([selector], [filter])

获得从他本身到指定节点之间的所有兄弟节点(不包括他本身和指定节点)。

```
$('.pear').prevUntil('.apple')
//=> [<li class="orange">Orange</li>]
```

#### .slice( start, [end] )

获取指定范围匹配的元素

```
$('li').slice(1).eq(0).text()
//=> 'Orange'

$('li').slice(1, 2).length
//=> 1
```

#### .siblings([selector])

获取选定元素的所有兄弟，不包括它自己(可以通过传入class改变筛选结果)。

```
$('.pear').siblings().length
//=> 2

$('.pear').siblings('.orange').length
//=> 1
```

#### .children([selector])

获取选定元素的孩子元素。

```
$('#fruits').children().length
//=> 3

$('#fruits').children('.pear').text()
//=> Pear
```

#### .contents()

获取匹配元素集合中的每个元素的孩子元素，包括文本和注释节点。

```
$('#fruits').contents().length
//=> 3
```

#### .each( function(index, element) )

迭代一个cheerio对象，为每个匹配元素执行一个函数。当回调函数执行后，该函数所处的环境是DOM element，所以`this`指向当前元素，这相当于函数的参数`element`。要提前打破的`each`循环，那么返回`false`。

```
var fruits = [];

$('li').each(function(i, elem) {
  fruits[i] = $(this).text();
});

fruits.join(', ');
//=> Apple, Orange, Pear
```

#### .map( function(index, element) )

通过每个在匹配函数产生的匹配集合中的匹配元素，产生一个新的包含返回值的cheerio对象。该函数可以返回一个单独的数据项或一组数据项被插入到所得到的集合中。如果返回一个数组，数组中的元素插入到集合中。如果函数返回空或未定义，则将插入任何元素。

```
$('li').map(function(i, el) {
  // this === el
  return $(this).text();
}).get().join(' ');
//=> "apple orange pear"
```

#### .filter( selector ) .filter( selection ) .filter( element ) .filter( function(index) )

遍历一个cheerio对象，降低通过选择器匹配的元素，或传递函数的测试的选择器元素组。当一个cheerio的选择是特定的，只返回元素的选择。当指定元素时，返回该元素（如果它包含在原始选择中）。如果使用该函数方法，该函数将在选定的元素的环境中执行，所以`this`是指当前元素。

Selector:

```
$('li').filter('.orange').attr('class');
//=> orange
```

Function:

```
$('li').filter(function(i, el) {
  // this === el
  return $(this).attr('class') === 'orange';
}).attr('class')
//=> orange
```

#### .not( selector ) .not( selection ) .not( element ) .not( function(index, elem) )

从匹配的元素集合中删除元素。给定一个jQuery对象表示一组DOM元素，`.not() `方法从匹配的元素的子集构造了一种新的jQuery对象。所提供的选择器对每个元素进行了测试；结果中不匹配选择器的元素将被包含在该结果中。`.not() `方法可以把一个函数作为参数就像`.filter() `一样。将函数返回为真的元素从过滤的集合中排除，所有其他元素都包括在内。

选择器:

```
$('li').not('.apple').length;
//=> 2
```

Function:

```
$('li').not(function(i, el) {
  // this === el
  return $(this).attr('class') === 'orange';
}).length;
//=> 2
```

#### .has( selector ) .has( element )

匹配一个拥有指定孩子元素的父元素。相当于`.filter(':has(selector)')`。

选择器:

```
$('ul').has('.pear').attr('id');
//=> fruits
```

元素:

```
$('ul').has($('.pear')[0]).attr('id');
//=> fruits
```

#### .first()

选择一个cheerio的对象的第一个元素

```
$('#fruits').children().first().text()
//=> Apple
```

#### .last()

选择一个cheerio对象的最后一个元素

```
$('#fruits').children().last().text()
//=> Pear
```

#### .eq( i )

根据索引来确定元素。使用 `.eq(-i)` 的则是倒过来计数。

```
$('li').eq(0).text()
//=> Apple

$('li').eq(-1).text()
//=> Pear
```

#### .get( [i] )

检索出匹配的cheerio对象的DOM元素。如果指定索引，检索出一个匹配的cheerio对象的元素：

```
$('li').get(0).tagName
//=> li
```

如果没有指定索引，检索出所有匹配的cheerio对象元素：

```
$('li').get().length
//=> 3
```

#### .index()

#### .index( selector )

#### .index( nodeOrSelection )

在匹配元素中搜索给定元素。

```
$('.pear').index()
//=> 2
$('.orange').index('li')
//=> 1
$('.apple').index($('#fruit, li'))
//=> 1
```

#### .end()

结束当前链中最新的过滤操作，将匹配的元素集合返回到它的前一状态。

```
$('li').eq(0).end().length
//=> 3
```

#### .add( selector [, context] )

#### .add( element )

#### .add( elements )

#### .add( html )

#### .add( selection )

在匹配元素集合中添加元素。

```
$('.apple').add('.orange').length
//=> 2
```

#### .addBack( [filter] )

将堆栈上的前一组元素添加到当前集合中，选择一个选择器进行筛选。

```
$('li').eq(0).addBack('.orange').length
//=> 2
```

### 操作

修改DOM结构的方法。

#### .append( content, [content, ...] )

插入内容为每个选定元素的 *last* 孩子。

```
$('ul').append('<li class="plum">Plum</li>')
$.html()
//=>  <ul id="fruits">
//      <li class="apple">Apple</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//      <li class="plum">Plum</li>
//    </ul>
```

#### .appendTo( target )

将每一个元素插入到目标的末端。

```
$('<li class="plum">Plum</li>').appendTo('#fruits')
$.html()
//=>  <ul id="fruits">
//      <li class="apple">Apple</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//      <li class="plum">Plum</li>
//    </ul>
```

#### .prepend( content, [content, ...] )

插入内容为每个选定元素的 *first* 孩子。

```
$('ul').prepend('<li class="plum">Plum</li>')
$.html()
//=>  <ul id="fruits">
//      <li class="plum">Plum</li>
//      <li class="apple">Apple</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//    </ul>
```

#### .prependTo( target )

将每一个元素插入到目标的开始。

```
$('<li class="plum">Plum</li>').prependTo('#fruits')
$.html()
//=>  <ul id="fruits">
//      <li class="plum">Plum</li>
//      <li class="apple">Apple</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//    </ul>
```

#### .after( content, [content, ...] )

在匹配元素集合中的元素后面插入内容。

```
$('.apple').after('<li class="plum">Plum</li>')
$.html()
//=>  <ul id="fruits">
//      <li class="apple">Apple</li>
//      <li class="plum">Plum</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//    </ul>
```

#### .insertAfter( target )

将每一个元素插入匹配元素集合中的目标后。

```
$('<li class="plum">Plum</li>').insertAfter('.apple')
$.html()
//=>  <ul id="fruits">
//      <li class="apple">Apple</li>
//      <li class="plum">Plum</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//    </ul>
```

#### .before( content, [content, ...] )

在匹配元素集合的元素前插入元素。

```
$('.apple').before('<li class="plum">Plum</li>')
$.html()
//=>  <ul id="fruits">
//      <li class="plum">Plum</li>
//      <li class="apple">Apple</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//    </ul>
```

#### .insertBefore( target )

在目标元素前插入元素。

```
$('<li class="plum">Plum</li>').insertBefore('.apple')
$.html()
//=>  <ul id="fruits">
//      <li class="plum">Plum</li>
//      <li class="apple">Apple</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//    </ul>
```

#### .remove( [selector] )

将匹配的元素集合从DOM和他们的孩子节点中删除。

```
$('.pear').remove()
$.html()
//=>  <ul id="fruits">
//      <li class="apple">Apple</li>
//      <li class="orange">Orange</li>
//    </ul>
```

#### .replaceWith( content )

将匹配的元素替换为 `content`。

```
var plum = $('<li class="plum">Plum</li>')
$('.pear').replaceWith(plum)
$.html()
//=> <ul id="fruits">
//     <li class="apple">Apple</li>
//     <li class="orange">Orange</li>
//     <li class="plum">Plum</li>
//   </ul>
```

#### .empty()

清空一个元素，去除所有的孩子。

```
$('ul').empty()
$.html()
//=>  <ul id="fruits"></ul>
```

#### .html( [htmlString] )

获取第一个选中元素的HTML内容字符串。如果`htmlstring`被指定，那么选中元素的内容被新内容所取代。

```
$('.orange').html()
//=> Orange

$('#fruits').html('<li class="mango">Mango</li>').html()
//=> <li class="mango">Mango</li>
```

#### .text( [textString] )

获取元素集合中的每个元素的合并文本内容，包括它们的后代。如果 `textString` 指定文本字符串，每个元素的内容被新的内容替换。

```
$('.orange').text()
//=> Orange

$('ul').text()
//=>  Apple
//    Orange
//    Pear
```

#### .wrap( content )

.wrap()函数可以使用任何可以传递给$()工厂函数字符串或对象来指定DOM结构。这种结构可以嵌套多个层次，但应该只包含一个内心深处的元素。这一结构的副本将在匹配的元素集合中的每一个元素被包装。此方法返回的链接目标的原始元素集。

```
var redFruit = $('<div class="red-fruit"></div>')
$('.apple').wrap(redFruit)

//=> <ul id="fruits">
//     <div class="red-fruit">
//      <li class="apple">Apple</li>
//     </div>
//     <li class="orange">Orange</li>
//     <li class="plum">Plum</li>
//   </ul>

var healthy = $('<div class="healthy"></div>')
$('li').wrap(healthy)

//=> <ul id="fruits">
//     <div class="healthy">
//       <li class="apple">Apple</li>
//     </div>
//     <div class="healthy">
//       <li class="orange">Orange</li>
//     </div>
//     <div class="healthy">
//        <li class="plum">Plum</li>
//     </div>
//   </ul>
```

#### .css( [propertName] ) .css( [ propertyNames] ) .css( [propertyName], [value] ) .css( [propertName], [function] ) .css( [properties] )

得到一个匹配元素的style属性值或者设置匹配元素的css属性。

### 渲染

当你准备好要渲染的文件，你可以使用`html`效用函数：

```
$.html()
//=>  <ul id="fruits">
//      <li class="apple">Apple</li>
//      <li class="orange">Orange</li>
//      <li class="pear">Pear</li>
//    </ul>
```

如果你想返回outerHTML，你可以使用 `$.html(selector)`：

```
$.html('.pear')
//=> <li class="pear">Pear</li>
```

默认情况下，`html`会留下一些开放标签。有时你可能会想要渲染一个有效的文档。例如，你可能会对下面的XML片段：

```
$ = cheerio.load('<media:thumbnail url="http://www.foo.com/keyframe.jpg" width="75" height="50" time="12:05:01.123"/>');
```

…后来要渲染到XML。要做到这一点，你可以使用 'xml' 效用函数：

```
$.xml()
//=>  <media:thumbnail url="http://www.foo.com/keyframe.jpg" width="75" height="50" time="12:05:01.123"/>
```

### 其他

DOM元素的方法不适合的地方

#### .toArray()

检索jQuery中所有的DOM元素然后设置为一个数组。

```
$('li').toArray()
//=> [ {...}, {...}, {...} ]
```

#### .clone()

克隆cheerio对象

```
var moreFruit = $('#fruits').clone()
```

### 实用工具

#### $.root

有时你需要与顶级根元素一起工作。要查询它，您可以使用 `$.root()`.。

```
$.root().append('<ul id="vegetables"></ul>').html();
//=> <ul id="fruits">...</ul><ul id="vegetables"></ul>
```

#### $.contains( container, contained )

检查`contained`DOM元素的容器是否是 `container`DOM元素的后代。

#### $.parseHTML( data [, context ] [, keepScripts ] )

将一个字符串解析成DOM节点数组。`context`参数对cheerio对象没有意义，但它可以保持API的兼容性。

#### $.load( html[, options ] )

在HTML加载。（请参阅上一节题为 "Loading" 以了解更多信息。）

### 插件

当你加载一个文件，你可以用定义插件的方法将原型或等效 `fn` 属性扩展：

```
var $ = cheerio.load('<html><body>Hello, <b>world</b>!</body></html>');
$.prototype.logHtml = function() {
  console.log(this.html());
};

$('body').logHtml(); // logs "Hello, <b>world</b>!" to the console
```

### "DOM Node" 对象

cheerio集合是由一些相似于[browser-based DOM nodes](https://developer.mozilla.org/en-US/docs/Web/API/Node)的对象组成。你可以期待他们定义以下属性：

- `tagName`
- `parentNode`
- `previousSibling`
- `nextSibling`
- `nodeValue`
- `firstChild`
- `childNodes`
- `lastChild`
