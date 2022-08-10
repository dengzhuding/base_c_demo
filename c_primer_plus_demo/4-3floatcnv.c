/**
 * @file 4-3floatcnv.c
 * @brief 不匹配的浮点型转换
 * @date 2022-08-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<stdio.h>

int main(void) {
  float n1 = 3.0; // 4字节
  double n2 = 3.0; // 8字节
  long n3 = 2000000000; // 4字节（根据环境不同，可能是8字节）
  long n4 = 1234567890; // 4字节

  // 正常打印: 3.0e+00 3.0e+00 2000000000:0x77359400 1234567890:0x499602d2
  printf("%.1e %.1e %ld:%#lx %ld:%#lx\n", n1, n2, n3, n3, n4, n4);

  /**
   * 1. %e转换说明没有把整型转换成浮点型
   * 2. float类型的值作为printf()参数时会被转换成double类型,n1被扩成8字节
   */
  printf("%.1e %.1e %.1e %.1e\n", n1, n2, n3, n4); // 3.0e+00 3.0e+00 9.9e-315 6.1e-315
  
  /**
   * 参数传递：
   *   - 程序把传入的值放入被称为栈(stack)的内存区域
   *   - 计算机根据变量类型(不是根据转换说明)把这些值放入栈中
   *   - printf根据转换说明(不是根据变量类型)从栈中取值
   */
  printf("n1 size: %zd, n2 size: %zd, n3 size: %zd, n4 size: %zd\n",
    sizeof(n1), sizeof(n2), sizeof(n3), sizeof(n4)); // n1 size: 4, n2 size: 8, n3 size: 4, n4 size: 4
  printf("%ld %ld %ld %ld\n", n1, n2, n3, n4); // 0 0 2000000000 1234567890
  return 0;
}