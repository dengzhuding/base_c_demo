/**
 * @file 4-2printf-scanf.c
 * @brief printf() 和scanf()函数
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 
----------------转换说明及其打印的输出结果---------------------------------
转换说明  输出
%a,%A,%i 浮点数、十六进制和p记数法(C99/C11)
%c       单个字符
%d       有符号十进制整数
%e,%E    浮点数，e记数法
%f       浮点数，十进制记数法
%g,%G    根据值的不同，自动选择%f或%e. %e用于指数小于-4或者大于或等于精度时
%o       无符号八进制整数
%p       指针
%s       字符串
%u       无符号十进制整数
%x,%X    无符号十六进制整数，使用十六进制数0f，0F
%%       打印一个百分号%

----------------printf()修饰符 - 在%和转符之间插入修饰符可修饰基本的转换说明-------------------
修饰符    含义
标记      5种标记(-+ #0):可以不使用标记或使用多个标记
            减号-(待打印项左对齐); 加号+(打印正负符号);
            空格 (打印前导空格或者减号); 井号#(把结果转换为另一种形式,如进制前面加0或0x);
            零0(对于数值格式，用前导0代替空格填充字段宽度)。
数字      最小字段宽度,%4d

*         printf() - 用*代替字段宽度，表示不想预先指定，希望通过程序来指定：
                    printf("%*d", width, number);
                    printf("%*.*f", width, precision, number)
          scanf() - 把*放在%和转换字符之间时，会使得scanf()跳过相应的输出项
                    scanf("%*d %*d %d", &number); //输入: 1 2 3 (把第三个数拷贝给number)

.数字     表示精度
            对于%e和%f转换,表示小数点右边数字的位数
            对于%g转换,表示有效数字最大位数
            对于%s转换,表示待打印字符的最大数量
            对于整型转换,表示待打印数字的最小位数
            如有必要，使用前导0来达到这个位数，%.f 和%.0f相同
h         和整型转换说明一起使用，表示short int 或 unsigned char类型的值: %hu, %hx, %6.4hd
hh        和整型转换说明一起使用，表示signed char 或 unsigned char类型的值: %hhu, %hhx, %6.4hhd
j         和整型转换说明一起使用，表示intmax_t或uintmax_t类型的值，这些类型定义在stdint.h种，%jd
l         和整型转换说明一起使用，表示long int 或 unsigned long int类型的值
ll        和整型转换说明一起使用，表示long long int 或 unsigned long long int类型的值(C99)
L         和浮点转换说明一起只用，表示long double类型的值, %Lf,%10.4Le
t         和整型转换说明一起使用，表示ptrdiff_t类型的值, ptrdiff_t是指2个指针差值的类型(C99)
z         和整型转换说明一起使用，表示size_t类型的值, size_t是sizeof返回的类型(C99)，%zd

eg.
%1s或者%2s,%3s:取字符串的前1,2或者3位
%*c:屏蔽一个字符
%[A-Z]:取一个A到Z的值
%[^a-z]:不取a到z的值
%[^\n]：取非换行之前的值
printf("%5d", a):左边补

 */
#include<stdio.h>
// #define PAGES 959 // 明示常量
int main(void) {
  // 字段宽度
  const int PAGES = 959;
  printf("*%d*\n*%2d*\n*%10d*\n*%-10d*\n", PAGES, PAGES, PAGES, PAGES); // 减号-使得内容在全部的打印宽度左对齐了

  // 一些浮点修饰符的组合
  const double RENT = 3852.99;
  printf("*%f*\n*%e*\n*%4.2f*\n*%3.1f*\n%3.0f*\n*%10.3f*\n*%10.3e*\n*%+4.2f*\n*%010.3f*\n",
        RENT, RENT, RENT, RENT, RENT, RENT, RENT, RENT, RENT);

  // 演示一些格式标记
  printf("%d  %#o  %x  %X  %#x\n", 31, 31, 31, 31, 31); // 31  037  1f  1F  0x1f
  printf("**%d**% d**% d**\n", 42, 42, -42); // **42** 42**-42**
  printf("**%5d**%5.3d**%05d**\n", 6, 6, 6); // **    6**  006**00006**
  printf("**%05.3d**\n", 6); // **  006**   如果0标记和精度一起出现，0标记会被忽略

  // 字符串格式
  const char BLURB[] = "Authentic imitation!";
  printf("[%2s]  [%24s]  [%24.5s]  [%-24.5s]\n",
      BLURB, BLURB, BLURB, BLURB); // [Authentic imitation!]  [    Authentic imitation!]  [                   Authe]  [Authe                   ]

  return 0;
}