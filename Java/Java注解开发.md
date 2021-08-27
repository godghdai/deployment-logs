## Java注解开发
#### 什么是注解

Annotation(注解) 就是Java提供了一种为程序元素关联任何信息或任何元数据（metadata）的途径和方法。
Annotion(注解) 是一个接口，程序可以通过反射来获取指定程序元素的Annotion对象，然后通过Annotion对象来获取注解里面的元数据。

#### 注解出现的位置
Annotation(注解)是JDK5.0及以后版本引入的。它可以用于创建文档，跟踪代码中的依赖性，甚至执行基本编译时检查。从某些方面看，annotation就像修饰符一样被使用，并应用于**包、类型、构造方法、方法、成员变量、参数、本地变量**的声明中。这些信息被存储在Annotation的“name=value”结构对中。

#### 注解不会影响程序代码的执行
Annotation能被用来为某个程序元素（类、方法、成员变量等）关联任何的信息。需要注意的是，这里存在着一个基本的规则：**Annotation不能影响程序代码的执行**，无论增加、删除 Annotation，代码都始终如一的执行。另外，尽管一些annotation通过java的反射api方法在运行时被访问，而java语言解释器在工作时忽略了这些annotation。正是由于java虚拟机忽略了Annotation，导致了annotation类型在代码中是“不起作用”的； 只有通过某种配套的工具才会对annotation类型中的信息进行访问和处理

#### 注解的作用

注解（Annotation） 为我们在代码中添加信息提供了一种形式化的方法。
可以在稍后在某个时刻方便地使用这些数据（通过反射来解析注解，来使用这些数据）。

常见的作用有以下几种：

-  生成文档。这是最常见的，也是java最早提供的注解。常用的有@see @param @return 等；
-  在编译时进行格式检查。如@Override放在方法前，如果你这个方法并不是覆盖了超类方法，则编译时就能检查出；
-  跟踪代码依赖性，实现替代配置文件功能。比较常见的是spring 2.5 开始的基于注解配置。作用就是减少配置。现在的框架基本都使用了这种配置来减少配置文件的数量；


## JDK自带的注解

#### @Override
表示当前方法覆盖了父类的方法。
此注释只适用于修辞方法，表示一个方法声明打算重写超类中的另一个方法声明。如果方法利用此注释类型进行注解但没有重写超类方法，则编译器会生成一条错误消息。

#### @Deprecated

表示方法已经过时,方法上有横线，使用时会有警告。
此注释可用于修辞方法、属性、类，表示不鼓励程序员使用这样的元素，通常是因为它很危险或存在更好的选择。在使用不被赞成的程序元素或在不被赞成的代码中执行重写时，编译器会发出警告。

#### @SuppressWarings
表示关闭一些警告信息(通知java编译器忽略特定的编译警告)。
用来抑制编译时的警告信息。与前两个注释有所不同，你需要添加一个参数才能正确使用，这些参数值都是已经定义好了的，我们选择性的使用就好了，

@SuppressWarnings注释只有一个参数，并且参数名为value

- 全部： @SuppressWarnings("all")
- 简写： @SuppressWarnings(value={"deprecation"}) ,可简写为@SuppressWarnings("deprecation")
- 多个： @SuppressWarnings(value={“unchecked”, “deprecation”}),可简写为@SuppressWarnings({"unchecked","fallthrough"})


| 关键字      | 用途                                                         |
| ----------- | ------------------------------------------------------------ |
| unchecked   | 执行了未检查的转换时的警告，例如当使用集合时没有用泛型 (Generics) 来指定集合保存的类型。 |
| unused      | 未使用的变量                                                 |
| resource    | 有泛型未指定类型                                             |
| path        | 在类路径、源文件路径等中有不存在的路径时的警告               |
| deprecation | 使用了不赞成使用的类或方法时的警告                           |
| fallthrough | 当 Switch 程序块直接通往下一种情况而没有 break; 时的警告     |
| serial      | 某类实现Serializable(序列化)， 但没有定义 serialVersionUID 时的警告 |
| rawtypes    | 没有传递带有泛型的参数                                       |
| finally     | 任何 finally 子句不能正常完成时的警告。                      |
| try         | 没有catch时的警告                                            |
| all         | 所有类型的警告                                               |

```java
// 以下是源码引用中见到的，但实际很少用到的
@SuppressWarnings("FragmentNotInstantiable")
@SuppressWarnings("ReferenceEquality")
@SuppressWarnings("WeakerAccess")
@SuppressWarnings("UnusedParameters")
@SuppressWarnings("NullableProblems")
@SuppressWarnings("SameParameterValue")
@SuppressWarnings("PointlessBitwiseExpression")
```

## 开发自定义注解

#### 语法规则

- 使用@interface关键字定义注解，注意关键字的位置
  使用@interface自定义注解时，自动继承了java.lang.annotation.Annotation接口，由编译程序自动完成其他细节。在定义注解时，不能继承其他的注解或接口。

- 成员以无参数无异常的方式声明，注意区别一般类成员变量的声明
  其中的每一个方法实际上是声明了一个配置参数。方法的名称就是参数的名称

- 可以使用default为成员指定一个默认值

- 成员类型是受限的，合法的类型包括原始类型以及String、Class、Annotation、Enumeration （JAVA的基本数据类型有8种：
  byte(字节)、short(短整型)、int(整数型)、long(长整型)、float(单精度浮点数类型)、double(双精度浮点数类型)、char(字符类型)、boolean(布尔类型）

- 注解类可以没有成员，没有成员的注解称为标识注解，例如JDK注解中的@Override、@Deprecation

- 如果注解只有一个成员，并且把成员取名为value()，则在使用时可以忽略成员名和赋值号“=” ,例如JDK注解的@SuppviseWarnings ；如果成员名不为value，则使用时需指明成员名和赋值号"="

```java
@interface MyAnnotation {
    String value();
}
@interface MyAnnotation2 {
    String value() default "yzd";
}
@MyAnnotation(value ="HelloWord")
public class MyAnnotationTest{
    @MyAnnotation2
    public void play(){}
    @MyAnnotation("HelloWord")
    public static void main(String[] args) {}
}
```

#### 元注解
何为元注解？就是注解的注解，就是给你自己定义的注解添加注解，你自己定义了一个注解，但你想要你的注解有什么样的功能，此时就需要用元注解对你的注解进行说明了。Java5.0定义了4个标准的meta-annotation类型，它们被用来提供对其它 annotation类型作说明。

```java
@Target({ElementType.METHOD,ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Inherited
@Documented
public @interface Description{
    String desc();
    String author();
    int age() default 18;
}
```

##### @Target
------
@Target说明了Annotation所修饰的对象范围：即注解的作用域，用于说明注解的使用范围，
即**注解可以用在什么地方，比如类的注解，方法注解，成员变量注解等等**
注意:如果Target元注解没有出现，那么定义的注解可以应用于程序的任何元素。

取值是在java.lang.annotation.ElementType这个枚举中规定的：

- CONSTRUCTOR:用于描述构造器
- FIELD:用于描述域
- LOCAL_VARIABLE:用于描述局部变量
- METHOD:用于描述方法
- PACKAGE:用于描述包
- PARAMETER:用于描述参数
- TYPE:用于描述类、接口(包括注解类型) 或enum声明


##### @Retention
------
@Retention定义了该Annotation被保留的时间长短：

1. 某些Annotation仅出现在源代码中，而被编译器丢弃；
2. 而另一些却被编译在class文件中；编译在class文件中的Annotation可能会被虚拟机忽略，
3. 而另一些在class被装载时将被读取（请注意并不影响class的执行，因为Annotation与class在使用上是被分离的）。
    使用这个meta-Annotation可以对 Annotation的“生命周期”限制。

@Retention的取值是在RetentionPoicy这个枚举中规定的

1. SOURCE:在源文件中有效（即源文件保留）
2. CLASS:在class文件中有效（即class保留）
3. RUNTIME:在运行时有效（即运行时保留）
```java
@Retention(RetentionPolicy.RUNTIME)
@Target({ElementType.METHOD,ElementType.TYPE})
public @interface MyAnnotation {
    String value() default "yzd";
}
```
注意:注解的的RetentionPolicy的属性值是RUNTIME,这样注解处理器可以通过反射，获取到该注解的属性值，从而去做一些运行时的逻辑处理。



##### @Documented
------
@Documented用于描述其它类型的annotation应该被作为被标注的程序成员的公共API，因此可以被例如javadoc此类的工具文档化。Documented是一个标记注解，没有成员。



##### @Inherited
------
@Inherited 元注解是一个标记注解，@Inherited阐述了某个被标注的类型是被继承的。如果一个使用了@Inherited修饰的annotation类型被用于一个class，则这个annotation将被用于该class的子类。
注意：@Inherited annotation类型是被标注过的class的子类所继承。类并不从它所实现的接口继承annotation，方法并不从它所重载的方法继承annotation。
当@Inherited annotation类型标注的annotation的Retention是RetentionPolicy.RUNTIME，则反射API增强了这种继 承性。如果我们使用java.lang.reflect去查询一个@Inherited annotation类型的annotation时，反射代码检查将展开工作：检查class和其父类，直到发现指定的annotation类型被发现， 或者到达类继承结构的顶层。

示例：

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Inherited
public @interface Animal{
    String name() default "animal";
}
```

```java
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
public @interface Duck {
    String name() default "duck";
}
```

```java
@Animal
class SuperClass {}

@Duck
public class SubClass extends SuperClass {
    public static void main(String[] args) {
        Class<SubClass> cls = SubClass.class;
        Annotation[] annotations = cls.getAnnotations();
        for (Annotation annotation : annotations) {
            System.out.println(annotation);
        }
    }
}
```

输出：

```shell
@src.an.Animal(name=animal)
@src.an.Duck(name=duck)
```



## 注解开发实例

####  通过注解创建数据库表

##### 需求分析

1、创建一个学生信息实体类,包括学号，姓名，性别，联系方式，住址
2、创建一些适当的注解，实现根据实体类自动创建数据库中的表
3、在创建的学生信息实体类上应用自定义的注解
4、写一个注解解析器，获取解析学生信息实体类上的注解，然后在mysql数据库中自动创建好表

##### 编写实体类

```java
public class StuInfo {
	private Integer sno;
	private String sname;
	private String tel;	
	private String sex;
	private String addr;
}
```

##### 编写注解
```java
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface TableName {
	public String name() default "";
}
```
```java
@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Constraints {
	public boolean primarykey() default false;
	public boolean allowNull() default true;
	public boolean unique() default false;
	public boolean autoincrement() default false;
}
```
```java
@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Type {
	public String type() default "varchar(20)";
	public Constraints constraints() default @Constraints;
}
```

##### 实体类上标注注解
```java
@TableName
public class StuInfo {
	@Type(type = "int", constraints = @Constraints(primarykey = true, autoincrement = true))
	private Integer sno;
	
	@Type(constraints = @Constraints(allowNull = false, unique = true))
	private String sname;
	
	@Type(type = "varchar(15)", constraints = @Constraints(unique = true))
	private String tel;
	
	@Type(type = "varchar(4)", constraints = @Constraints(allowNull = false))
	private String sex;
	
	@Type(type = "varchar(100)")
	private String addr;
}
```
##### 注解解释器
```java
public class TableCreator {
	public static void main(String[] args) {
		String sql = getSql(StuInfo.class);
		System.out.println(sql);
	}
    
	private static String getSql(Class<StuInfo> cls) {
		TableName tn = cls.getAnnotation(TableName.class);
		
		if(tn == null){//没有TableName这个注解，说明这个类不需要创建表
			return null;
		}
		
		StringBuffer sbf = new StringBuffer();
		String tableName = tn.name(); //获取配置在注解中的表名
		if(tableName == null || "".equals(tableName)){	//如果没有给定表名，则默认为这个类的类名
			tableName = cls.getSimpleName(); //获取这个类的类名，注意不是getName(),getName()会包含这个类的类路径信息
		}
		
		sbf.append("create table ").append(tableName).append("("); // create table stuInfo(
		
		//接下来要拼接的是列信息,这个时候需要获取这个类的所有属性,判断上面是否有Type注解
		Field[] fields = cls.getDeclaredFields();
		if(fields == null || fields.length <= 0){
			return null;
		}
		
		Type type = null;
		for(Field field : fields){
			if(!field.isAnnotationPresent(Type.class)){ //Type注解是否在该类上
				continue;
			}
			
			type = field.getAnnotation(Type.class);
			sbf.append(field.getName()).append(" ").append(type.type()); // sno int primary key auto_increment
			
			// 拼接约束
			if(type.constraints().primarykey()){
				sbf.append(" primary key");
				
				//判断主键是否自增
				if(type.constraints().autoincrement()){
					sbf.append(" auto_increment");
				}
			}else{
				//是否唯一
				if(type.constraints().unique()){
					sbf.append(" unique");
				}
				if(!type.constraints().allowNull()){
					sbf.append(" not null");
				}
			}
			sbf.append(","); //说明这一个字段拼接完成
		}
		String sql = sbf.toString();
		sql = sql.substring(0, sql.lastIndexOf(",")) + ")";
		return sql;
	}
}
```

##### 测试结果

```sql
CREATE TABLE StuInfo (
	sno int PRIMARY KEY AUTO_INCREMENT,
	sname varchar(20) UNIQUE NOT NULL,
	tel varchar(15) UNIQUE,
	sex varchar(4) NOT NULL,
	addr varchar(100)
)
```

