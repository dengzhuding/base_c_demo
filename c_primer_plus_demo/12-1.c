/**
 * @file 12-1.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-29
 * 
 * @copyright Copyright (c) 2023
 * 
 * C对象有4种存储期：
 * 静态存储期 - 文件作用域变量
 * 线程存储期 - _Thread_local 声明的对象
 * 自动存储期 - 块作用域的变量
 *     （块作用域变量也能具有静态存储期，用ststic关键字生命，变量会储存在静态内存中）
 * 动态分配存储期
 * 
 * 5种存储类别：自动、寄存器、静态块作用域、静态外部链接、静态内部链接
 * 
 */

#include <stdio.h>

int imax(int, int);

int giants = 5; // 文件作用域，外部链接,该文件和同一程序的其他文件都可以使用变量giants 
static int dodgers = 3; // 文件作用域，内部链接,属文件私有，该文件中的任意函数都可使用它。

int main(int argc, char **argv) {
  int num1, num2;
  int * pt = &num1;
  int ranks[10];
  const char * pc = "hello world !";
  puts(pc);
  int i;
  printf("please input 2 num:\n");
  scanf("%d %d", &num1, &num2);
  ranks[1] = num1;
  printf("ranks: ");
  for (i; i < 10; i++) {
    printf("%d ", *(ranks + i));
  }
  printf("\nthe max is: %d", imax(num1, num2));
  printf("\nnum1 is: %d", *pt);
}

int imax(int a, int b) {
  return (a > b ? a : b);
}