/**
 * @file 9-7factor.c
 * @brief 使用循环和递归计算阶乘
 * 
 * 递归优缺点：
 *   优点 - 为某些比编程问题提供了最简单的解决方案
 *   缺点 - 递归算法会快速消耗计算机的内存资源，且不方便阅读和维护
 */
#include<stdio.h>
#define TIP "Enter a number between 0 of 12: "

long fact(int);
long rfact(int);

int main(void) {
  int n;
  
  printf(TIP);
  while (scanf("%d", &n) == 1) {
    if (n < 0 || n > 12) {
      printf(TIP);
      continue;
    }
    printf("fact(%d) is %ld\n", n, fact(n));
    printf("rfact(%d) is %ld\n", n, rfact(n));
    printf(TIP);
  }
  
  return 0;
}
/**
 * @brief 循环计算阶乘
 * 
 * @param n 
 * @return long 
 */
long fact(int n) {
  long ans;
  for (ans = 1; n > 1; n--) {
    ans *= n;
  }
  return ans;
}
/**
 * @brief 递归计算阶乘
 * 
 * @param n 
 * @return long 
 */
long rfact(int n) {
  if (n == 0) {
    return 1;
  }
  return n * rfact(n - 1);
}