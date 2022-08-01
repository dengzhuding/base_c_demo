/*
整数溢出以及printf打印
*/
#include<stdio.h>

int main(void) {

  int num_over = 2147483647; // 32位范围-2147483647~2147483647
  unsigned int num_over_unsigned = 4294967295; // 无符号32位范围0~4294967295

  // 对于有符号，超过最大值时从-2147483647开始
  printf("num_over: %d  %d  %d\n", num_over, num_over + 1, num_over + 2); // num_over: 2147483647  -2147483648  -2147483647

  // 对于无符号整数：超过最大值时从0开始
  printf("num_over_unsigned: %u  %u  %u\n", num_over_unsigned, num_over_unsigned + 1, num_over_unsigned + 2); // num_over_unsigned: 4294967295  0  1

  // 打印int - %d, short - %hd , long - %ld, long long - %lld(%llu - unsigned long long int), unsigned - %u
  // 后缀就x -十六进制，o - 八进制，没有提供二进制打印，可用stdlib.h头文件里的itoa函数进行字符串转换。
  // %lx - 以十六进制打印long类型整数, %lo - 八进制long类型
  unsigned int un = 3000000000; // int为32位
  short end = 200; // short位16位范围-32767~32767
  long big = 65537;
  long long verybig = 12345678908642;

  // printf 必须根据待打印值类型使用正确的转换说明
  printf("un = %u and not %d\n", un, un); // un = 3000000000 and not -1294967296 （无符号3000000000和有符号-1294967296内部表示完全相同）

  printf("end = %hd and %d\n", end, end); // end = 200 and 200 
  /* 上面打印%d和%hd效果一样：
     C编译器把short类型自动转换成int类型-int类型被认为是处理整数类型时最高效的类型
     h修饰符的作用是显示较大整数被截断成short类型(也就是16位)值的情况，下面的输出就演示了这种情况
  */

  printf("big = %ld and not %hd", big, big); // big = 65537 and not 1 (65537 - 1 0000 0000 0000 0001 中short只会查看后16位，所以显示的值是1)
  printf("verbig = %lld and not %ld", verybig, verybig); // big = 65537 and not 1verbig = 12345678908642 and not 1942899938 （原因同上，%ld取到了后32位）

  return 0;
}