/**
 * @file 10-14arf.c
 * @brief 处理数组的函数
 * 
 * 
 * 普通变量(非const)类型变量可以传递给const 或 非const形参，但是const声明的变量不能传递给非const形参
 * 
 * 指针变量也有地址
 * int * p; // 千万不要解引用(*p = val)为初始化的指针，p未初始化，其值是一个随机值，可能会擦写数据或代码，或者导致程序崩溃
 */
#include<stdio.h>
#define SIZE 5


// 这样使用const不是要求原数组是常量，而是该函数在处理数组时将其视为常量，不可修改
void show_array(const double ar[], int n);
// ar[] 也可以用 * ar替代(声明可省略ar,定义不可省略ar)
void mult_array(double ar[], int n, double mult); // 数组表示法-让函数处理数组这一意图更加明显
void mult_array_p(double * start, double * end, double mult);

int main(void) {
  double dip[SIZE] = {1.1, 2.2};
  const int MULT = 2;

  printf("before:\n");
  show_array(dip, SIZE);

  // 使用数组函数
  mult_array(dip, SIZE, MULT);


  printf("\nshow_array after:\n");
  show_array(dip, SIZE);

  // 使用指针运算函数
  mult_array_p(dip, dip + SIZE, MULT);

  printf("\nmult_array_p:\n");
  show_array(dip, SIZE);

  // 指针差值 - 用%td转换说明，单位为地址指向类型的长度
  printf("\n&dip[1] - dip: %td\n", &dip[1] - dip); // 1

  /**
   * @brief const 的3种用法
   *   1. const TYPE * p; - 不能改变值，即*a_arr = newVal(报错)，当时能改变地址a_arr = &arr[0](ok)
   *   2. TYPE * const p = arr; - 声明并初始化一个不能指向别处的指针，可以改变值
   *   3. const TYPE * const p = arr; - 即不能更改它所指向的地址，也不能修改指向地址上的值
   */
  printf("\n\nconst 的3种用法:\n");

  // 1. 不能改变值，能改变地址
  const double * p_arr = dip; 
  printf("p_arr: %p, *p_arr: %8.3f\n", p_arr, *p_arr);
  // *p_arr = 100.0; 
  // p_arr[0] = 100.0; // error: assignment of read-only location '*p_arr'
  p_arr++; // ok
  printf("p_arr: %p, *p_arr: %8.3f\n", p_arr, *p_arr);

  // 2. 能改变值，不能改变地址，
  double * const p_arr2 = dip;
  // p_arr2++; // error: increment of read-only variable 'p_arr2'
  *p_arr2 = 100.0;
  p_arr2[1] = 200.0; // ok - p_arr2[1]是一个新的表达式计算地址,相当于p_arr2 + 1
  printf("p_arr2: %p, *p_arr2: %8.3f\n", p_arr2, *p_arr2);
  printf("&p_arr2[1]: %p, p_arr2[1]: %8.3f\n", &p_arr2[1], p_arr2[1]);

  // 3. 都不能改，声明时必须初始化
  const double * const p_arr3 = dip;
  // p_arr3 = p_arr3 + 1; // assignment of read-only variable 'p_arr3'
  // *p_arr3 = 100.0; // assignment of read-only location '*(const double *)p_arr3'

  return 0;
}

/**
 * @brief 显示数组内容
 * 
 * @param ar 
 * @param n 
 */
void show_array(const double ar[], int n) {
  int i;
  for(i = 0; i < n; i++)
    printf("%8.3f ", ar[i]); // 也能用*(ar + i)取值
}

/**
 * @brief 数组表示法
 * 
 * @param ar 
 * @param n 
 * @param mult 
 */
void mult_array(double ar[], int n, double mult) {
  int i;
  for(i = 0; i < n; i++)
    ar[i] *= mult;
}

/**
 * @brief 指针表示法
 * 
 * @param start - ar, &ar[0]
 * @param end - start + SIZE
 * @param mult - 倍数
 */
void mult_array_p(double * start, double * end, double mult) {
  while (start < end) {
    *start *= mult;
    start++;
  }
}
