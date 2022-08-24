/**
 * @file 9-6recur.c
 * @brief 递归演示
 * 
 */
#include<stdio.h>

void up_and_down(int); // 函数原型(声明)

int main(void) {
  int n = 1;
  up_and_down(n); // 函数调用(在声明之后)
}

void up_and_down(int n) { // 函数定义(也相当于函数声明)
  printf("n is: %d and location is: %p\n", n, &n); // &n - 取存储n的内存地址
  if(n < 4) {
    up_and_down(++n); // 递归(注意这里++放前面和后面效果完全不同，必须是先自增再传递参数进去)
  }
  printf("n is: %d and location is: %p\n", n, &n); // &n - 取存储n的内存地址
}
/**
n is: 1 and location is: 0000002d73dff8a0
n is: 2 and location is: 0000002d73dff870
n is: 3 and location is: 0000002d73dff840
n is: 4 and location is: 0000002d73dff810
n is: 4 and location is: 0000002d73dff810
n is: 3 and location is: 0000002d73dff840
n is: 2 and location is: 0000002d73dff870
n is: 1 and location is: 0000002d73dff8a0
 */