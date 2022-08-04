/**
 * @file 3-7escape.c
 * @brief 使用转义序列
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>
#include<unistd.h>

int main(void) {
  float f_salary;

  printf("\aEnter your desired monthly salary:"); // \a - 蜂鸣符
  printf("  $_______\b\b\b\b\b\b\b"); // \b - 退格符
  /**
   * printf() 何时把输出发送到屏幕上？
   *   - printf()语句把输出发送到缓冲区(buffer)-中间存储区域，然后缓冲区的内容不断被发送到屏幕上
   *   - C标准规定：当缓冲区满、遇到换行字符或需要输入的时候(从缓冲区把数据发送到屏幕或文件被称为刷新缓冲区)
   *   - fflush()函数刷新缓冲区
   */
  scanf("%f", &f_salary); 
  printf("\n\t$%.2f month is $%.2f a year.", f_salary, f_salary * 12); // \t - 水平制表符
  printf("\rGee!\n"); // \t - 回车符(回到行首)  \n - 换行符

  printf("hello");
  sleep(3); // 这里windows平台（ubuntu正常）在等待时也把hello输出了(刷新了缓冲区，理论上是等到输出下面换行符一起输出hello world.)
  printf(" world.\n");

  printf("hello");
  fflush(stdout);
  sleep(3);
  printf(" world.\n");

  return 0;
}