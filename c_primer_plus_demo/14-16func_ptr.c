/**
 * @file 14-16func_ptr.
 * @brief 使用函数指针 
 * @date 2023-07-10
 * 
 * void ToUpper(char *); // 无返回函数
 * void (*pf)(char *); // 函数指针
 * pf = ToUpper;
 * (*pf)(str);
 * pf(str)
 * 1. 由于pf 指向ToUpper 函数，那么*pf 就相当于ToUpper 函数，
 *    所以表达式(*pf)(mis) 和ToUpper(mis) 相同
 * 2. 由于函数名是指针，那么指针和函数名可以互换使用，
 *    所以pf(mis) 和ToUpper(mis) 相同
 * 
 * 
 * 使用函数名的5种方法:
 * 函数原型中的函数名(声明函数)：     int comp(int x, int y);
 * 函数调用中的函数名：              status = comp(q, r);
 * 函数定义中的函数名(函数定义)：     int comp(int x, int y) {}
 * 在赋值表达式语句中作为指针的函数名：p_funct = comp;
 * 作为指针参数的函数名：             slowsort(arr, n, comp);
 */
#include<stdio.h>
#include <string.h>
#include "common.h"

#define LEN 81

extern char * s_gets(char * st, int n);

int main(void) {
  char str[LEN];
  char * (* pfun)(char *, int); // 声明一个函数指针，被指向的函数接收2个参数，返回指向char类型的指针、
  pfun = s_gets; 
  while (pfun(str, LEN) != NULL && str[0] != '\0') {
    puts(str);
  }
  void * n = NULL; // 无类型指针
  if (n == NULL) {
    printf("n == NULL");
  }
  return 0;
}