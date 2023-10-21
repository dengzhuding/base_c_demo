/**
 * @file 16-1preprocessor.c
 * @brief C预处理器在程序执行之前查看程序(故称之为预处理器)。
 * 根据程序中的预处理器指令,预处理器把符号缩写替换成其表示的内容。
 * 预处理器可以包含程序所需的其他文件,可以选择让编译器查看哪些代码
 * 
 * @date 2023-07-17
 * 预处理之前的步骤：
 * 1. 首先,编译器把源代码中出现的字符映射到源字符集。
 *    该过程处理多字节字符和三字符序列 ——字符扩展让C更加国际化
 * 2. 编译器定位每个反斜杠后面跟着换行符的实例,并删除它们
 * 3. 编译器把文本划分成预处理记号序列、空白序列和注释序列(这里要注意的是,
 *    编译器将用一个空格字符替换每一条注释)
 *    而且,实现可以用一个空格替换所有的空白字符序列(不包括换行符)
 * 最后,程序已经准备好进入预处理阶段,预处理器查找一行中以# 号开始的预处理指令
 * 
 * 每行#define(逻辑行)都由3部分组成：
 * 1. 第1部分是#define 指令本身。
 * 2. 第2部分是选定的缩写,也称为宏.
 *    有些宏代表值(如本例),这些宏被称为类对象宏(object-like macro);
 *    C语言还有类函数宏(function-like macro)
 * 3. 第3部分(指令行的其余部分)称为替换列表或替换体
 *    一旦预处理器在程序中找到宏的示实例后,就会用替换体代替该宏(也有例外,在字符串中不替换)
 *    从技术角度来看,可以把宏的替换体看作是记号(token)型字符串,而不是字符型字符串。
 *    C预处理器记号是宏定义的替换体中单独的“词”。用空白把这些词分开
 * 从宏变成最终替换文本的过程称为宏展开(macro expansion)
 * 
 * 在#define中使用参数,在#define中使用参数可以创建外形和作用与函数类似的类函数宏:
 * #define MEAN(x,y) (((x) +(y))/2)
 * 
 * 宏和函数的选择:
 * 宏和函数的选择实际上是时间和空间的权衡。
 * 宏生成内联代码，即在程序中生成语句。如果调用20次宏，即在程序中插入20行代码。
 * 如果调用函数20次，程序中只有一份函数语句的副本，所以节省了空间。
 * 然而另一方面，程序的控制必须跳转至函数内，随后再返回主调程序，这显然比内联代码花费更多的时间
 * 1. 宏的一个优点是，不用担心变量类型（这是因为宏处理的是字符串，而不是实际的值）。
 *    因此，只要能用int 或float 类型都可以使用SQUARE(x) 宏
 * 2. C99提供了第3种可替换的方法——内联函数
 * 3. 对于简单的函数，程序员通常使用宏，如下所示：
      #define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
      #define ABS(X) ((X) < 0 ? -(X) : (X))
      #define ISSIGN(X) ((X) == '+' || (X) == '-' ? 1 : 0)
 * 
 * 文件包含：#include
 * 当预处理器发现#include 指令时，会查看后面的文件名并把文件的内容包含到当前文件中，
 * 即替换源文件中的#include 指令。这相当于把被包含文件的全部内容输入到源文件#include 指令所在的位置。
 * #include 指令有两种形式：
 *   <> - 尖括号告诉预处理器在标准系统目录中查找该文件
 *   "" - 双引号告诉预处理器首先在当前目录中（或文件名中指定的其他目录）查找该文件，如果未找到再查找标准系统目录
 * 
 * 包含一个大型头文件不一定显著增加程序的大小。
 * 在大部分情况下，头文件的内容是编译器生成最终代码时所需的信息，而不是添加到最终代码中的材料。
 * 
 * 头文件中最常用的形式如下:
      明示常量     - 例如，stdio.h 中定义的EOF 、NULL 和BUFSIZE （标准I/O缓冲区大小）。
      宏函数       - 例如，getchar() 通常用getc(stdin) 定义，而getc() 经常用于定义较复杂的宏，
                     头文件ctype.h 通常包含ctype 系列函数的宏定义。
      函数声明     - 例如，string.h 头文件（一些旧的系统中是strings.h ）包含字符串函数系列的函数声明。
                     在ANSI C和后面的标准中，函数声明都是函数原型形式。
      结构模版定义 - 标准I/O函数使用FILE 结构，该结构中包含了文件和与文件缓冲区相关的信息。FILE 结构在头文件stdio.h 中。
      类型定义     - 标准I/O函数使用指向FILE 的指针作为参数。通常，stdio.h 用#define 或typedef 把FILE 定义为指向结构的指针。
                     类似地，size_t 和time_t 类型也定义在头文件中。

 * 另外，还可以使用头文件声明外部变量供其他文件共享
 * extern int status; 
 * // 在头文件中，这样使用该系列函数的文件都能使用这个变量。
 * // 虽然源代码文件中包含该头文件后也包含了该声明，但是只要声明的类型一致，
 * // 在一个文件中同时使用定义式声明和引用式声明没问题 
 * 
 */
/* preproc.c -- 简单的预处理示例 */
#include <stdio.h>

#define TWO 2        /* 可以使用注释 */
#define OW "Consistency is the last refuge of the unimagina\
tive. - Oscar Wilde" /* 反斜杠把该定义延续到下一行 */

#define FOUR  TWO*TWO
#define PX printf("X is %d.\n", x1)
#define FMT  "X is %d.\n"

#define LIMIT 20
const int LIM = 50;
static int data1[LIMIT];          // 有效
// static int data2[LIM];            // 无效
const int LIM2 = 2 * LIMIT;       // 有效
// const int LIM3 = 2 * LIM;         // 无效
/**
 * 这里解释一下上面代码中的“无效”注释。
 * 在C中,非自动数组的大小应该是整型常量表达式,这意味着表示数组大小的必须是整型常量的组合(如5)、
 * 枚举常量和sizeof 表达式,不包括const 声明的值(这也是C++和C的区别之一,在C++中可以把const 
 * 值作为常量表达式的一部分)。
 * 但是,有的实现可能接受其他形式的常量表达式。
 * 例如,GCC 4.7.3不允许data2 的声明,但是Clang 4.6允许。
 * 
 */


#define SQUARE(X) X*X
#define PR(X)   printf("The result is %d.\n", X)

/** 
 * @brief C允许在字符串中包含宏参数。在类函数宏的替换体中,# 号作为一个预处理运算符,
 * 可以把记号转换成字符串。例如,如果x 是一个宏形参,
 * 那么#x 就是转换为字符串"x" 的形参名。这个过程称为字符串化(stringizing)
 * 
*/ 
#define PSQR(x) printf("The square of " #x " is %d.\n",((x)*(x)))

/**
 * @brief 与# 运算符类似，## 运算符可用于类函数宏的替换部分。
 * 而且，## 还可用于对象宏的替换部分。## 运算符把两个记号组合成一个记号
 * 
 */
#define XNAME(n) x ## n
// XNAME(4); // -> x4
int XNAME(2) = 2; // -> int x1 = 1;

/**
 * @brief 变参宏：... 和_ _VA_ARGS_ _
 * 预定义宏__VA_ARGS__ 可用在替换部分中，表明省略号代表什么
 */
#define PR_V(...) printf(__VA_ARGS__)
#define PR_V2(X, ...) printf("Message " #X ": " __VA_ARGS__)


int main(void)
{
    int x1 = TWO;

    PX;
    x1 = FOUR;  // -> TWO*TWO
    printf(FMT, x1);
    printf("%s\n", OW);
    printf("TWO: OW\n");


    /**
     * @brief 预处理器不做计算、不求值,只替换字符序列
     * 
     */
    int x = 5;
    int z;

    printf("x = %d\n", x);
    z = SQUARE(x); // x*x
    printf("Evaluating SQUARE(x): ");
    PR(z); //  printf("The result is %d.\n", z)
    z = SQUARE(2); // 2*2
    printf("Evaluating SQUARE(2): ");
    PR(z);  //  printf("The result is %d.\n", z)
    printf("Evaluating SQUARE(x+2): ");
    PR(SQUARE(x + 2)); // printf("The result is %d.\n", x+2*x+2)
    printf("Evaluating 100/SQUARE(2): ");
    PR(100 / SQUARE(2)); // printf("The result is %d.\n", 100 / 2*2)
    printf("x is %d.\n", x); // 5
    printf("Evaluating SQUARE(++x): ");
    PR(SQUARE(++x));  // printf("The result is %d.\n", ++x*++x) - 未定义行为
    printf("After incrementing, x is %x.\n", x); // 7

    int y = 5;
    PSQR(y); // printf("The square of " "y" " is %d.\n",((y)*(y)));
    PSQR(2 + 4); // printf("The square of " "2 + 4" " is %d.\n",((2 + 4)*(2 + 4)));

    printf("XNAME(1): %d, x2: %d\n", XNAME(1), x2);

    PR_V("hello %s\n", "world");
    PR_V2(1, "y is %d\n", y);
    PR_V2(2, "y is %d, x1 is %d \n", y, XNAME(1));

    return 0;
}
