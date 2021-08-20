## Typescript高级语法之装饰器
### 1、环境搭建

```shell
npm init -y 
tsc -init 
npm install typescript -D 
npm install reflect-metadata -D 
npm install ts-node -D 
```
打开装饰器的开关，修改**tsconfig.json**如下:

```json
/* Experimental Options */
"experimentalDecorators": true,             /* Enables experimental support for ES7 decorators. */
"emitDecoratorMetadata": true,   			/* Enables experimental support for emitting type metadata for decorators. */
```
### 2、类的装饰器

```typescript
import 'reflect-metadata';
// 装饰器本身是一个函数，参数是构造函数
function Controller(path: string): ClassDecorator {
    return function (target: Function) {
        Reflect.defineMetadata('root', path, target);
    }
}

@Controller("http://www.hello.com")
class User {}
console.log(Reflect.getMetadata("root", User))
```

```typescript
function DecoratorNew
    <T extends new (...args: any[]) => any>//为传参使用构造函数类型
    (constructor: T) {
    return class extends constructor {
        getName = () => {//扩展一个函数，但是ts不会自动识别到函数
            console.log(this.name)
        }
    }
}

const Person = DecoratorNew(
    class {//原始匿名类
        name: string
        constructor(name: string) {
            this.name = name
        }
    }
)
const person = new Person("hello");
person.getName();
```

### 3、类的属性装饰器

```typescript
function WritableDecorator(target: any, key: string): any {
    //新建descriptor替换掉原本的，需要返回类型为any
    const descriptor: PropertyDescriptor = {
        writable:false
    }
    return descriptor
}
class User {
    @WritableDecorator
    name: string
    constructor(name: string) {
        this.name = name
    }
}
const user = new User('test1');
// TypeError: Cannot assign to read only property 'name' of object '#<Test>'
user.name="hello" //无法赋值
console.log(user.name)
```

### 4、类的参数装饰器

```typescript
function paramDecorator(target: any, key: string, paramIndex: number) {
    //原型，方法名，参数序号
    console.log(target, key, paramIndex)
}
class Test {
    constructor() { }
    getInfo(name: string, @paramDecorator age: number) {
        console.log(name, age)
    }
}
const test = new Test();
test.getInfo('yzd', 30)

```

### 5、reflect-metadata

Reflect是es6中的内容，作用就是可以实现对变量操作的函数化

Relfect Metadata，简单来说，你可以通过装饰器来给类添加一些自定义的信息。然后通过反射将这些信息提取出来。当然你也可以通过反射来添加这些信息

因为用的symbol，需要改一下target，修改**tsconfig.json**如下:

```json
//target值由es5修改为es2015
{
  "compilerOptions": {
    "target": "es5"
  }
}
```

```typescript
import 'reflect-metadata'
function Decorator(key: symbol, value: string) {
    return function (target: any, name?: string | undefined, des?: PropertyDescriptor) {
        //console.log(arguments)
        if (typeof name === 'string') {
            //console.log(key, value, target, name)
            Reflect.defineMetadata(key, value, target, name)
        } else {
            Reflect.defineMetadata(key, value, target)//key,value,target
        }
    }
}
const key: symbol = Symbol.for('key')
@Decorator(key, 'value')
@Reflect.metadata('name', 'A')//key,value
class A {
    @Reflect.metadata('hello', 'world')
    @Decorator(key, 'value')
    public hello(): string {
        return 'hello world'
    }
}

console.log(Reflect.getMetadata('name', A),// 'A'~key,target
    Reflect.getOwnMetadata('name', A)) // 'A'~key,target
console.log(Reflect.getMetadata('hello', new A(), 'hello'),// 'world'~key,target,name
    Reflect.getOwnMetadata('hello', new A(), 'hello')) // undefined~key,target,name~因为是实例不是原型
console.log(Reflect.getMetadata(Symbol.for('key'), A),//value~key,target
    Reflect.getOwnMetadata(Symbol.for('key'), A))//value~key,target
console.log(Reflect.getMetadata(Symbol.for('key'), A.prototype, 'hello'),//value~key,target,name
    Reflect.getOwnMetadata(Symbol.for('key'), A.prototype, 'hello'))//value~key,target,name
```
**运行结果**

```shell
D:\ts>ts-node ./src/test.ts
A A
world undefined
value value
value value
```

### 6、装饰器执行顺序

属性->方法->方法参数->类

同样的装饰器，倒序执行

```typescript
const logClass1 = (params?: string) => (target: any) => { console.log('类装饰器1') }
const logClass2 = (params?: string) => (target: any) => { console.log('类装饰器2') }
const logAttribute1 = (params?: string) => (target: any, attrName: any) => { console.log('属性装饰器1') }
const logAttribute2 = (params?: string) => (target: any, attrName: any) => { console.log('属性装饰器2') }
const logMethod1 = (params?: string) => (target: any, attrName: any, desc: any) => { console.log('方法装饰器1') }
const logMethod2 = (params?: string) => (target: any, attrName: any, desc: any) => { console.log('方法装饰器2') }
const logParams1 = (params?: string) => (target: any, attrName: any, desc: any) => { console.log('方法参数装饰器1') }
const logParams2 = (params?: string) => (target: any, attrName: any, desc: any) => { console.log('方法参数装饰器2') }
@logClass1()
@logClass2()
class C {
    @logAttribute1()
    @logAttribute2()
    public a: string | undefined;

    constructor() {
    }

    @logMethod1()
    @logMethod2()
    getData() {
        return true;
    }

    setData(@logParams1() attr1: any, @logParams2() attr2: any,) {
    }
}
var c: any = new C();
```

**运行结果**

```shell
D:\ts>ts-node ./src/test.ts
属性装饰器2
属性装饰器1
方法装饰器2
方法装饰器1
方法参数装饰器2
方法参数装饰器1
类装饰器2
类装饰器1
```

