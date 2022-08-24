/**
 * @file 9-8binary.c
 * @brief 以二进制形式打印整数
 * 
 */
#include<stdio.h>

void to_binary(unsigned long int n, int count); // 只是声明，n可要可不要

int main(void) {
  unsigned long int n;
  printf("Enter number: ");
  while (scanf("%lu", &n) == 1)
  {
    to_binary(n, 0);
    printf("\nEnter number: ");
  }

  return 0;
}
// 递归打印为二进制
/**
 * @brief 
 * 
 * @param n - 传入的整数
 * @param count - 从低位的计数，用于控制空格的打印，如: 1 0001
 */
void to_binary(unsigned long int n, int count) {
  int r;
  r = n % 2; // r - 最低位，后打印
  
  if (n > 0) {
    count++;
  }
  if (n >= 2) {
    to_binary(n/2, count); // n/2 - 截断为整数
  }
  if (count > 0 && count % 4 == 0 && n >= 2) { // n非零、二进制计数为4的整数倍、位数还有有高位才打印空格
    putchar(' ');
  }
  putchar(r == 1 ? '1' : '0');
  return;
}