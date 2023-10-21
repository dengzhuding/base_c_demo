/**
 * @file 16-2compiler.c
 * @brief c编译器(cc)
 * @date 2023-07-12
 * 
 * 关于编译器详情信息可参考：https://fabiensanglard.net/dc/index.php
 * 
内存用于存储程序中的数据，由存储期、作用域和链接表征
1.存储期可以是静态的、自动的或动态分配的。
  如果是静态(用static说明符声明)存储期，在程序开始执行时分配内存，并在程序运行时都存在。
  如果是自动存储期，在程序进入变量定义所在块时分配变量的内存，在程序离开块时释放内存。
  如果是动态分配存储期，在调用malloc() （或相关函数）时分配内存，在调用free() 函数时释放内存。
2.作用域决定程序的哪些部分可以访问某数据
  定义在所有函数之外的变量具有文件作用域，对位于该变量声明之后的所有函数可见。
  定义在块或作为函数形参内的变量具有块作用域，只对该块以及它包含的嵌套块可见。
3.链接描述定义在程序某翻译单元中的变量可被链接的程度
  具有块作用域的变量是局部变量，无链接。
  具有文件作用域的变量可以是内部链接或外部链接。
    内部链接意味着只有其定义所在的文件才能使用该变量。
    外部链接意味着其他文件使用也可以使用该变量。

下面是C的5种存储类别（不包括线程的概念）
1.自动 - 块中，auto声明或不带说明符
  具有自动存储期、块作用域、无链接。如果未初始化自动变量，它的值是未定义的
2.寄存器 - 块中，register声明
  具有自动存储期、块作用域、无链接，且无法获取其地址。
  把一个变量声明为寄存器变量即请求编译器将其储存到访问速度最快的区域。
  如果未初始化寄存器变量，它的值是未定义的
3.静态、无链接 - 块中，static声明
  具有静态存储期、块作用域、无链接。只在编译时被初始化一次。如果未显式初始化，它的字节都被设置为0
4.静态、外部链接 - 函数外部且没有使用static说明符
  具有静态存储期、文件作用域、外部链接。只能在编译器被初始化一次。如果未显式初始化，它的字节都被设置为0
5.静态、内部链接 - 函数外部且使用了static说明符
  具有静态存储期、文件作用域、内部链接。只能在编译器被初始化一次。如果未显式初始化，它的字节都被设置为0

限定符const 、volatile 、restrict 和_Atomic ：
1.const 限定符限定数据在程序运行时不能改变。
  对指针使用const 时，可限定指针本身不能改变或指针指向的数据不能改变，这取决于const 在指针声明中的位置。
2.volatile 限定符表明，限定的数据除了被当前程序修改外还可以被其他进程修改。
  该限定符的目的是警告编译器不要进行假定的优化。
3.restrict 限定符也是为了方便编译器设置优化方案。
  restrict 限定的指针是访问它所指向数据的唯一途径。
4._Atomic 限定变量存储的输出操作是一个原子过程，其他线程不能访问

 clang -c -o hello.o hello.c // 输出object file
 readelf -S -W hello.o  // 显示elf文件信息
 nm hello.o  // 列出object 文件的符号信息(symbols)

nm字母代码的完整列表及其含义如下:

// Global symbol / Local symbol: local - 局部符号只在可重定位单元内(内部链接)可见，用static说明符声明
// Weak and strong symbols: 默认情况下，所有符号都是强符号;弱符号可以被强符号覆盖
   如：声明weak函数:__attribute__((weak)) int getNumber() {}
   如果有2个重复函数，将其中一个重复的函数声明为弱函数，则不管编译和链接顺序如何，程序都可以正常编译并运行
// Weak symbols and libc: 大多数libc实现将它们的方法声明为“弱”，以便用户可以拦截它们。
  这并不总是像看起来那么方便,现在最好的方法是通过加载器和LD_PRELOAD进行MITM

A  A global, absolute symbol.
B  A global "bss" (uninitialized data) symbol.         // 全局未初始化
C  A "common" symbol, representing uninitialized data.
D  A global symbol naming initialized data.            // 全局已经初始化
N  A debugger symbol.
R  A read-only data symbol.                            // 只读数据
T  A global text symbol.
U  An undefined symbol.                                // 未定义，一般是外部变量
V  A weak object.
W  A weak reference.
a  A local absolute symbol.
b  A local "bss" (uninitialized data) symbol.          // 本地未初始化
d  A local data symbol.                                // 本地已经初始化
r  A local read-only data symbol.                      // 本地只读数据，已经初始化
t  A local text symbol.                                // 本地文本
v  A weak object that is undefined.
w  A weak symbol that is undefined.
?  None of the above.
 * 
 */
extern int undVar;                 // Should be U  
int defVar;                        // Should be B

extern const int undConst;         // Should be U
const int defConst = 1;            // Should be R

extern int undInitVar;             // Should be U
int defInitVar = 1;                // Should be D

static int staticVar;              // Should be b
static int staticInitVar=1;        // Should be d
static const int staticConstVar=1; // Should be r

static void staticFun(int x) {}    // Should be t

extern void foo(int x);            // Should be U

void bar(int x) {                  // Should be T 
  foo(undVar);
  staticFun(undConst);
  
}
