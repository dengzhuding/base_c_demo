/**
 * @file 14-2union-type.c
 * @author your name (you@domain.com)
 * @brief 联合（union ）是一种数据类型，它能在同一个内存空间中储存不同的数据类型（不是同时储存）。
 * 其典型的用法是，设计一种表以储存既无规律、事先也不知道顺序的混合类型。
 * 使用联合类型的数组，其中的联合都大小相等，每个联合可以储存各种数据类型。
 * @date 2023-07-09
 * 
 */

#include <stdio.h>

/**
 * @brief 声明的联合只能储存一个int 类型的值或一个double 类型的值或char 类型的值
 * 
 */
union hold
{
  int digit; // 4 byte
  double bigfl; // 8 byte
  char letter; // 1 byte
};

struct hello
{
  char * world;
  union { // 匿名联合
    int digit; // 4 byte
    double bigfl; // 8 byte
  };
};


int main (void) {
  union hold fit; // 变量
  union hold save[2]; // 数组
  union hold * pu; // 指针

  save[0].digit = 1;
  printf("sizeof(save): %zd\n", sizeof(save));

  struct hello h1;
  h1.world = "hello world!";
  h1.bigfl = 11.2;
  printf("h1.world: %s, h1.bigfl: %.2f\n", h1.world, h1.bigfl);

  printf("siezof(fit): %zd\n", sizeof(fit)); // 8 编译器分配足够的空间以便它能储存联合声明中占用最大字节的类型
  
  // 3种初始化的方法
  fit.digit = 1;
  // fit = 1; // 1. 跟上句同样效果，都是初始化联合的第1个元素
  printf("fit.digit: %d\n", fit.digit);
  fit.bigfl = 12.23; // 清除1，存储12.23，占8字节
  printf("fit.bigfl: %.2f\n", fit.bigfl);
  union hold valA = fit; // 把一个联合初始化为另一个同类型的联合
  union hold valB = {.letter = 'b'}; // 指定初始化器
  printf("valB.letter: %c\n", valB.letter);

  // 和用指针访问结构使用-> 运算符一样，用指针访问联合时也要使用-> 运算符：
  pu = &valA;
  printf("pu->bigfl): %.2f\n", pu->bigfl); // 相当于valA.bigfl
  
  return 0;
  

}