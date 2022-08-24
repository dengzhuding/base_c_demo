/**
 * @file 10-1array_base.c
 * @brief 数组声明以及初始化
 * 
 * 在C标准中，使用越界下标的结果是未定义的 
 *   - 可能会导致程序改变其他变量的值，有些编译器会导致程序异常终止
 * C语言为何会允许这种麻烦事发生？
 *   - 这要归功于C信任程序员的原则
 *   - 不检查边界，C程序可以运行更快
 *   - 在程序运行之前，数组的下标值可能尚未确定
 */
#include<stdio.h>
#define MONTHS 12

int main(void) {
  int numbers[10]; //方括号[]表明数组类型,里面的数字表面元素个数
  char code[20];
  // 二维数组初始化
  int rain[5][10] = {
    {10, 11, 12},
    {20},
    {[9] = 39} // 设置arr[2][8] = 39
  };
  int rain_i, rain_j;
  printf("rain:\n");
  for(rain_i = 0; rain_i < 5; rain_i ++) {
    for(rain_j = 0; rain_j < 10; rain_j ++)
      printf("[%d][%d]: %2d ", rain_i, rain_j, rain[rain_i][rain_j]);
    putchar('\n');
  }
  /** 
   * 用以逗号分隔的值列表(花括号{}括起来)来初始化数组
   */
  int powers[8] = {1,}; 
  // 只读数组 - 用const声明并初始化数组，
  const int days[MONTHS] = {31, 28, 31}; // 值少于元素个数，编译器会把剩余的元素都初始化为0
  // const int days_2[2] = {31, 28, 31}; // 如果项数大于数组元素个数，编译器会视为错误: excess elements in array initializer

  // 可以省略方括号中的数字，让编译器自动匹配数组大小和初始化列表中的项数
  // 弊端：无法察觉到初始化列表中的项数有误
  const int days_3[] = {1, 2, 3};

  /**
   * C99新增新特性-指定初始化器(designated initalizer),两个重要特征：
   *   - 如果指定初始化器后面由更多的值，那么后面这些值被用于初始化指定元素后面的片段
   *   - 如果再次初始化指定的元素，那么后面的初始化将会取代之前的初始化
   * 如果没指定元素大小(下面这样): 编译器会把数组的大小设置为足够装得下初始化的值
   */
  int arr[] = {1, [5] = 5, 6, [0] = 10}; // arr[5] - 5，arr[6] - 6, arr[0] - 10,其他为0
  int arr_i;
  int arr_length = sizeof(arr) / sizeof(arr[0]);
  printf("arr_length: %d\n", arr_length);
  for(arr_i = 0; arr_i < arr_length; arr_i++)
    printf("arr[%d]: %d ", arr_i, arr[arr_i]); // arr[0]: 10 arr[1]: 0 arr[2]: 0 arr[3]: 0 arr[4]: 0 arr[5]: 5 arr[6]: 6

  return 0;
}