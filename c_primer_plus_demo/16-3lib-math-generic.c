/**
 * @file 16-3lib-math-generic.c
 * @brief generic.c  -- 定义泛型宏
 * 如果不需要双精度，那么用float 类型的单精度值来计算会更快些。
 * 而且把long double 类型的值传递给double 类型的形参会损失精度，形参获得的值可能不是原来的值
 * 
 * 为了解决这些潜在的问题，C标准专门为float 类型和long double 类型提供了标准函数，即在原函数名后加上f 或l 后缀。
 * 因此，sqrtf() 是sqrt() 的float 版本，sqrtl() 是sqrt() 的long double 版本
 * 
 * @date 2023-07-17
 */

#include <stdio.h>
#include <math.h>

/**
  C99标准提供的tgmath.h 头文件中定义了泛型类型宏，其效果与程序下面案例类似
  如果包含了tgmath.h ，要调用sqrt() 函数而不是sqrt() 宏，可以用圆括号把被调用的函数名括起来
  y = sqrt(x);        // 调用宏，所以是 sqrtf(x)
  y = (sqrt)(x);      // 调用函数 sqrt(),还也可以使用(*sqrt)() 的形式来调用sqrt() 函数
 */
// #include <tgmath.h> 

// 如果编译器支持复数运算，就会支持complex.h 头文件，其中声明了与复数运算相关的函数
// #include <complex.h>

#define PI 4 * atanl(1)
#define RAD_TO_DEG (180/PI)

// 泛型平方根函数
// _Generic 表达式的值就是函数名，如sinf 。函数的地址可以代替该函数名，所以_Generic 表达式的值是一个指向函数的指针。
// 然而，紧随整个_Generic 表达式之后的是(X) ，函数指针 (参数 )表示函数指针。因此，这是一个带指定的参数的函数指针
#define SQRT(X) _Generic((X),\
    long double: sqrtl, \
    default: sqrt, \
    float: sqrtf)(X)

// 泛型正弦函数，角度的单位为度
// 每个带标号的值都是函数调用，所以_Generic 表达式的值是一个特定的函数调用，如sinf((X)/RAD_TO_DEG) ，用传入SIN() 的参数替换X 
#define SIN(X) _Generic((X),\
    long double: sinl((X)/RAD_TO_DEG),\
    default:    sin((X)/RAD_TO_DEG),\
    float:     sinf((X)/RAD_TO_DEG)\
)

int main(void)
{
    float x = 45.0f;
    double xx = 45.0;
    long double xxx = 45.0L;

    long double y = SQRT(x);
    long double yy = SQRT(xx);
    long double yyy = SQRT(xxx);
    printf("%.17Lf\n", y);       // 匹配 float
    printf("%.17Lf\n", yy);      // 匹配 default
    printf("%.17Lf\n", yyy);     // 匹配 long double
    int i = 45;
    yy = SQRT(i);                // 匹配 default
    printf("%.17Lf\n", yy);
    yyy = SIN(xxx);              // 匹配 long double
    printf("%.17Lf\n", yyy);

    return 0;
}
