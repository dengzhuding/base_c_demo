/**
 * @file 12-5parta.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 * C语言有6个关键字作为存储类别说明符：
 * auto 表明变量是自动存储期,只能用于块作用域的变量声明中
 *       (主要是为了明确表达要使用与外部变量同名的局部变量的意图)
 * register 只用于块作用域的变量，它把变量归为寄存器存储类别，请求最快速度访问该变量
 *       (同时，还保护了该变量的地址不被获取)
 * static 创建的对象具有静态存储期，载入程序时创建对象，当程序结束时对象消失
 *        (如果static 用于文件作用域声明，作用域受限于该文件。如果static 用于块作用域声明，作用域则受限于该块)
 * extern 表明声明的变量定义在别处
 * _Thread_local
 * typedef 
 */

// parta.c 不同的存储类别
// 与partb.c 一起编译
#include <stdio.h>

void report_count();
extern void accumulate(int k); // 声明定义在其他文件中的函数
int count = 0; // 文件作用域，外部链接

int main () {
  int value; //自动变量
  register int i; // 寄存器变量
  printf("Enter a positive integer (0 to quit): ");
  while(scanf("%d", &value) == 1 && value > 0) {
    ++count;
    for (i = value; i >=0; i--)
      accumulate(i);
    printf("Enter a positive integer (0 to quit): ");
  }
  report_count();

  return 0;

}

void report_count() {
  printf("Loop executed %d times.", count);
}