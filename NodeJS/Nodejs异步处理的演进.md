# Nodejs异步处理的演进

**场景**

> 当我们使用Nodejs 作为后台服务器语言时， 常常要处理大量的异步I/O 操作。例如当我们想要向mongodb 更改一条数据时，我们在最开始使用chunk 函数来实现异步I/O 操作。

## Chunck 函数实现异步操作

```js
//存储一条留言信息
Comment.prototype.save = function(callback) {
  var name = this.name,
      comment = this.comment;
  //打开数据库
  mongodb.open(function (err, db) {
    if (err) {
      return callback(err);
    }
    //读取 posts 集合
    db.collection('posts', function (err, collection) {
      if (err) {
        mongodb.close();
        return callback(err);
      }
      //通过用户名、时间及标题查找文档，并把一条留言对象添加到该文档的 comments 数组里
      collection.update({
        "name": name,
      }, {
        $push: {"comments": comment}
      } , function (err) {
          mongodb.close();
          if (err) {
            return callback(err);
          }
          callback(null);
      });   
    });
  });
};
```

这就是我们诟病的callback hell， 不易阅读与维护。

## Promise 函数实现异步操作

Promise 函数依靠链式操作的特性和catch exception 的函数，可以很好的避免Chunk 函数的callback hell。但是我们还是需要把各个逻辑分别封装在不同的then() 函数中，每一个函数都有自己独特的作用域。如果我们要共用某个常量或是变量还要把它定义在函数外，Generator 函数最早实现了异步函数同步化的功能。

```js
var name = this.name,
    comment = this.comment;
mongoDb
    .open()
    .then(function(db){
      return db.collection("posts");
    })
    .then(function(collection){
      return collection.update({
            "name": name,
        }, {
            $push: {"comments": comment}
        });
    })
    .then(){
      mongodb.close();
    })
    .catch(function(e){
      throw new Error(e);
    })
```

## Genetrator 函数实现异步操作

借着ES6的Generator迭代器，TJ大神写出了co 库最早实现异步编程同步化的功能。我们通过co(function *(){})可以使函数内部通过迭代器来控制。而co在这里则是充当了启动器的角色。

```js
var co = require("co");
var name = this.name,
    comment = this.comment;

co(function *(){
    var db, collection; 
    try{
        db = yield mongodb.open();
        collection = yield db.collection("posts");
        yield collection.update({
            "name": name,
        }, {
            $push: {"comments": comment}
        });
    }catch(e){
        console.log(e);
    }
     mongodb.close();
});
```

## async/await 函数实现异步操作

ES7的async/await的出现为实现异步函数操作提供了另一种方式，await 关键字的作用与generator 函数的yield 作用相类似。

```js
var db, collection, result; 
async function UpateDB () {
    var name = this.name,
    comment = this.comment;
    try{
        db = await mongodb.open();
        collection = await db.collection("users");
        await collection.update({
                "name": name,
            }, {
                $push: {"comments": comment}
        });
    }catch(e){
        console.log(e);
    }
    mongodb.close();
}
```
