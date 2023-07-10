/**
 * @file 14-13complex-declarations.c
 * @brief 其他复杂的声明
 * @date 2023-07-10
 * 
 * 声明时可使用的符号:
 * *  - 表示一个指针
 * () - 表示一个函数
 * [] - 表示一个数组
 * 
 * 
 */
#include <stdio.h>
// 函数原型
char m_getchar(int);

int main (void) {
/** * *、() 和[]的优先级规则： **/
  // 1. 数组名后面的[] 和函数名后面的() 具有相同的优先级。它们比*（解引用运算符）的优先级高
  int * risks[10]; // 声明一个内含10个元素的数组，每个元素都是一个指向int的指针
  // 2．[] 和() 的优先级相同，由于都是从左往右结合，所以下面的声明中，在应用方括号之前，*先与rusks 结合
  int (* rusks)[10]; // 声明一个指向数组的指针，该数组内含10个int类型的元素
  // 3．[] 和() 都是从左往右结合
  int goods[2][3]; // 声明一个由2个内含3个int类型元素的数组组成的二维数组,
  // 类似[[int, int, int], [int, int, int]]

  int * goods_arr[2][3]; // 声明一个2x3的数组，每个元素都是指向int类型的指针

  int (* goods_pt)[2][3]; // 圆括号使得*先与goods_pt 结合，说明goods_pt 是一个指针，
  // 指向2x3的二维数组(元素为int类型)

  /** 根据这些规则，还可以声明(这3个函数都接受int 类型的参数) */
  char * fump(int); // 返回字符指针的函数
  char (* frump)(int); // 指向函数的指针，该函数的返回类型为char
  char (* flump[3])(int); // 内含3个指针的数组，每个指针都指向返回类型为char的函数

  // 函数名是指针，那么指针和函数名可以互换使用
  frump = m_getchar; // 与frump = &m_getchar相同效果
  printf("65 is %c %c\n", (*frump)(65), frump(65)); // 65 is A  与frump(65)相同效果

  // 可以使用typedef 建立一系列相关类型：
  typedef int arr5[5];
  typedef arr5 * p_arr5;
  typedef p_arr5 arrp10[10];
  arr5 togs;    // togs 是一个内含5个int类型值的数组
  p_arr5 p2;    // p2 是一个指向数组的指针，该数组内含5个int类型的值
  arrp10 ap;    // ap 是一个内含10个指针的数组，每个指针都指向一个内含5个int类型值的数组
}
// 函数声明
char m_getchar(int num) {
  char ch;
  ch = (char)num;
  return ch;
}