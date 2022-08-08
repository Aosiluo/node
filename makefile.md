# makefile

## makefile的核心规则

target ... : prerequisites ...
     command
     ...
     ...

target也就是一个目标文件，可以是Object File，也可以是执行文件。还可以是一个标签（Label）。
prerequisites就是，要生成那个target所需要的文件或是目标。
command也就是make需要执行的命令（任意的Shell命令），makefile中的命令必须以 [tab] 开头。

这是一个文件的依赖关系，也就是说，target这一个或多个的目标文件依赖于prerequisites中的文件，其生成规则定义在command中。说白一点就是说，prerequisites中如果有一个以上的文件比target文件要新的话，command所定义的命令就会被执行。

#### makefile的五个主要部分

显示规则:说明如何生成一个或多个目标文件(包括 生成的文件, 文件的依赖文件, 生成的命令)
隐晦规则:make的自动推导功能所执行的规则
变量定义:makefile中定义的变量
文件指示:makefile中引用其他makefile; 指定makefile中有效部分; 定义一个多行命令
注释:makefile只有行注释 “#”, 如果要使用或者输出"#"字符, 需要进行转义, “\#”

#### GNU make的工作流程

读入主makefile (主makefile中可以引用其他makefile)
读入被include的其他makefile
初始化文件中的变量
推导隐晦规则, 并分析所有规则
为所有的目标文件创建依赖关系链
根据依赖关系, 决定哪些目标要重新生成
执行生成命令

## makefile语法

### **引用其他makefile**

在Makefile使用include关键字可以把别的Makefile包含进来，这很像C语言的#include，被包含的文件会原模原样的放在当前文件的包含位置。include的语法是：

```makefile
include <filename>;
```

filename可以是当前操作系统Shell的文件模式（可以保含路径和通配符）。
在include前面可以有一些空字符，但是绝不能是[Tab]键开始。

### **makefile变量**

#### 1、变量声明

声明时需要给予初值。例如：foo = c

#### 2、引用变量

变量名前加上“$”符号，但最好用小括号“()”或大括号“{}”把变量给包括起来，这样更安全。

#### 3、变量赋值

1、“=”赋值：

说明：在“=”左侧是变量，右侧是变量的值，右侧变量的值可以定义在文件的任何一处，也就是说右侧中的变量不一定非要是已定义好的值，其也可以使用后面定义的值

例如：

```makefile
foo = $(bar)
ugh = Huh?
all:
      echo $(foo)     
```

==>执行结果：Huh

2、“：=”赋值

说明：使用“:=”操作符，前面的变量不能
3、“?=”赋值

说明：判断变量是否被定义

FOO ?= bar

其含义是，如果 FOO 没有被定义过,那么变量 FOO 的值就是“bar”，如果 FOO 先前被定义过，那么这条语将什么也不做。

#### 4、两种变量的高级使用方法

1、变量替换。

我们可以替换变量中的共有的部分，其格式是“$(var:a=b)”或是“${var:a=b}”,其意思是,把变量“var”中所有以“a”字串“结尾”的“a”替换成“b”字串。

例如： 先定义了一个“$(foo)”变量,而第二行的意思是把“$(foo)”中所有以“.o”字串“结尾”全部替换成“.c”,所以我们的“$(bar)”的值就是“a.c b.cc.c”。

```makefile
foo := a.o b.o c.o
bar := $(foo:.o=.c)
```

2、变量嵌套

```makefile
x = y
y = z
a := $($(x))
```

在这个例子中,$(x)的值是“y”,所以$($(x))就是$(y),于是$(a)的值就是“z”。(注意,是“x=y”,而不是“x=$(y)”)

#### 5、追加变量值

可以使用“+=”操作符给变量追加值 。

```makefile
objects = main.o foo.o bar.o utils.o
objects += another.o
```

于是$(objects)值变成:“main.o foo.o bar.o utils.o another.o”(another.o被追加进去了)

注意：变量之前没有定义过，那么“+=”会自动变成“=”，如果前面有变量定义，那么“+=”会继承于前次操作的赋值符。如果前一次的是“:=”，那么“+=”会以“:=”作为其赋值符，或者前次的赋值符是“=”，那么“+=”也会以“=”来做为赋值。

#### 6、强制赋值（override 指示符）

如果有变量是通过 make 的命令行参数设置的（make a=1），那么 Makefile 中对a这个变量的赋值会被忽略。如果你想在 Makefile 中设置这类参数的值，那么你可以使用“override”指示符。

语法：

```makefile
override <variable> = <value>
override <variable> := <value>
override <variable> += <more text>
override define foo
     bar
endef
```

例如：如果在Makefile里定义：f =11，执行make f =22，执行结果打印f就是22，如果在Makefile里定义：override f =11，执行make f =22，执行结果打印f就是11。

注意：变量在定义时使用了“override”，则后续对它值进行追加时，也需要使用带有“override”指示符的追加方式。否则对此变量值的追加不会生效。

#### 7、多行变量

还有一种设置变量值的方法是使用 define 关键字。使用 define 关键字设置变量的值可以有换行,这有利于定义一系列的命令(前面我们讲过“命令包”的技术就是利用这个关键字)。

```makefile
define two-lines
      echo foo
      echo $(bar)
endef
```

#### 8、环境变量

make 运行时的系统环境变量可以在 make 开始运行时被载入到 Makefile 文件中，但是如果 Makefile 中已定义了这个变量，或是这个变量由 make 命令行带入，那么系统的环境变量的值将被覆盖。(如果 make 指定了“-e”参数，那么系统环境变量将覆盖 Makefile 中定义的变量)

同时，makefile在解析变量时，都是先展开到不能再展开，再得出最终结果。



**条件判断语句**

其语法如下：

```makefile
<conditional-directive>
<text-if-true>
else
<text-if-false>
endif
```

其中表示条件关键字,这个关键字有四个：ifeq \ ifneq \ ifdef \ ifndef

实例如下：

```makefile
ifeq (<arg1>, <arg2>)
```

其中，参数可以为空。

#### makefile函数

函数的调用
makefile中函数的调用与变量类似，都是“$”符号开头，后面跟括号或者大括号

```makefile
$(<function> <arguments>)
${<function> <arguments>}
```

其中，函数名与参数之间以空格间隔，参数之间以逗号分隔。

函数的作用
makefile中有字符串处理函数，可以实现字符串的查找，替换，过滤，排序，连接等操作；也有文件名操作函数（属于特殊的字符串处理函数），可以对文件名实现取目录部分，取文件部分，取后缀，取前缀，加前缀，加后缀等操作。

#### 特殊函数

foreach函数 这个函数是用来**做循环**用的

if函数 这个函数作用与ifeq**条件判断语句**类似

call函数 这个函数可以用来**替换某个表达式中的参数**

origin函数 这个函数用于**查询变量的来源**

shell函数 这个函数用于**执行shell命令**，把**执行操作系统命令后的输出**作为函数**返回**，也就是我们可以**使用shell来获取操作系统命令执行后的返回值**

error函数 这个函数用于产生一个致命错误

warning函数 这个函数用于产生一个警告

## 文件搜寻路径

VPATH
makefile中有个特殊的变量 VPATH 是用于指定文件搜寻路径的,指定了 VPATH 之后, 如果当前目录中没有找到相应文件或依赖的文件, Makefile 会到 VPATH 指定的路径中再去查找

```makefile
VPATH = src:../headers
```

上面的的定义指定两个目录，“src”和“…/headers”，make会按照这个顺序进行搜索。目录由“冒号”分隔。

vpath

这不是变量，这是一个make的关键字，它的使用方法如下：

```makefile
vpath <pattern> <directories>
```

例如：

```makefile
vpath %.h ../headers
```

该语句表示，要求make在“…/headers”目录下搜索所有以“.h”结尾的文件（如果某文件在当前目录没有找到的话）。

## 伪目标

可以使用一个特殊的标记“.PHONY”来显示地指明一个目标是“伪目标”，向make说明，**不管是否有这个文件，这个目标就是“伪目标”。**

 .PHONY : clean

只要有这个声明，不管是否有“clean”文件，要运行“clean”这个目标，只有“make clean”这样。于是整个过程可以这样写：

```makefile
  .PHONY: clean
 clean:
         rm *.o temp
```

## 隐含规则

#### 编译C程序的隐含规则

“.o”的目标的依赖目标会自动推导为“.c”，并且其生成命令是“$(CC) –c $(CPPFLAGS) $(CFLAGS)”

#### 编译C++程序的隐含规则

“.o”的目标的依赖目标会自动推导为“.cc”或是“.C”，并且其生成命令是“$(CXX) –c $(CPPFLAGS) $(CFLAGS)”。（建议使用“.cc”作为C++源文件的后缀，而不是“.C”）

#### 汇编和汇编预处理的隐含规则

“.o” 的目标的依赖目标会自动推导为“.s”，默认使用编译品“as”，并且其生成命令是：“$(AS) ( A S F L A G S ) ” 。 “ < n > . s ” 的 目 标 的 依 赖 目 标 会 自 动 推 导 为 “ < n > . S ” ， 默 认 使 用 C 预 编 译 器 “ c p p ” ， 并 且 其 生 成 命 令 是 ： “ (ASFLAGS)”。“<n>.s” 的目标的依赖目标会自动推导为“<n>.S”，默认使用C预编译器“cpp”，并且其生成命令是：“(ASFLAGS)”。“<n>.s”的目标的依赖目标会自动推导为“<n>.S”，默认使用C预编译器“cpp”，并且其生成命令是：“(AS) $(ASFLAGS)”。

#### 链接Object文件的隐含规则。

“”目标依赖于“.o”，通过运行C的编译器来运行链接程序生成（一般是“ld”），其生成命令是：“$(CC) $(LDFLAGS) .o $(LOADLIBES) $(LDLIBS)”。

以下是关于隐含规则的变量：

#### 命令变量	含义

AR	函数库打包程序。默认命令是“ar”。
AS	汇编语言编译程序。默认命令是“as”。
CC	C语言编译程序。默认命令是“cc”。
CXX	C++ 语言编译程序。默认命令是“g++”。
CPP	C程序的预处理器（输出是标准输出设备）。默认命令是“$(CC) –E”。
RM	删除文件命令。默认命令是“rm –f”。

#### 参数变量（一般默认都是空）	含义

ARFLAGS	函数库打包程序AR命令的参数。默认值是“rv”。
ASFLAGS	汇编语言编译器参数。（当明显地调用“.s”或“.S”文件时）。
CFLAGS	C语言编译器参数。
CXXFLAGS	C++语言编译器参数。
CPPFLAGS	C预处理器参数。（ C 和 Fortran 编译器也会用到）。
LDFLAGS	链接器参数。（如：“ld”）

#### 其他变量	含义

CURDIR	记录当前路径
SHELL	默认为/bin/sh
MAKEFILE_LIST	make程序所处理的所有makefile文件
.DEFAULT_GOAL	用于告知如果在命令行中未指定目标，应该构建哪个目标
MAKEFLAGS	执行make时后面所带的所有参数和选项

## 自动化变量

Makefile 中很多时候通过自动变量来简化书写, 各个自动变量的含义如下:

自动变量	含义
$@	目标集合
$%	当目标是函数库文件时, 表示其中的目标文件名
$<	**第一个依赖目标 如果依赖目标是多个, 逐个表示依赖目标**
$?	比目标新的依赖目标的集合
$^	所有依赖目标的集合, 会去除重复的依赖目标
$+	所有依赖目标的集合, 不会去除重复的依赖目标
$*	这个变量表示目标模式中"%"及其之前的部分
