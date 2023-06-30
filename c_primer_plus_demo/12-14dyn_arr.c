/**
 * @file 12-14dyn_arr.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int main () {
  double * ptd; // 声明为指向一个double 类型
  // malloc 返回动态分配内存块的首字节地址，与free() 配套使用(参数 - 所需的内存字节数)
  // 在C中，不一定要使用强制类型转换(double *) ，但是在C++中必须使用
  ptd = (double *) malloc(30 * sizeof(double)); // 新的创建动态数组方式
  if (ptd == NULL) {
    puts("Memory allocation failed. Goodbye.");
    exit(EXIT_FAILURE); // 表示程序异常中止, EXIT_SUCCESS （或者，相当于0 ）表示普通的程序结束
  }
  // 内存泄漏 （memory leak ）。在函数末尾处调用free() 函数可避免这类问题发生。
  free(ptd); // 释放之前malloc() 分配的内存

  // 分配内存还可以使用calloc(),它把块中的所有位都设置为0
  int * ptd2;
  // 第1个参数是所需的存储单元数量，第2个参数是存储单元的大小（以字节为单位）
  ptd2 = calloc(10, sizeof(int));
  free(ptd2);

  return;
}