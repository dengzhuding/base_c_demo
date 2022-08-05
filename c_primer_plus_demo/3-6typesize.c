/**
 * @file 3-6typesize.c
 * @author dzdhello
 * @brief 打印当前系统的指定类型大小
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>

int main(void) {
  /**
   * sizeof是C语言的内置运算符 - 以字节(1字节=8位)为单元给出指定类型的大小
   * C99和C11提供%zd转换说明匹配sizeof的返回类型，一些不支持C99和C11的编译器可用%u或%lu代替%zd
   */
  printf("Type int has a size of %zd bytes.\n", sizeof(int));
  printf("Type short has a size of %zd bytes.\n", sizeof(short));
  printf("Type long has a size of %zd bytes.\n", sizeof(long));
  printf("Type long long has a size of %zd bytes.\n", sizeof(long long));

  printf("Type char has a size of %zd bytes.\n", sizeof(char));

  printf("Type float has a size of %zd bytes.\n", sizeof(float));
  printf("Type double has a size of %zd bytes.\n", sizeof(double));
  printf("Type long double has a size of %zd bytes.\n",
        sizeof(long double)); // 只要不在引号内部或一个单词中间断行，就可以分多行写语句

  printf("Type _Bool has a size of %zd bytes.\n", sizeof(_Bool));
  return 0;
}