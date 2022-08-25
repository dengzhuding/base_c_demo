/**
 * @file 10-9day_mon3.c
 * @brief use pointer notation
 * 
 */
#include<stdio.h>
#include<stdbool.h>

#define MONTHS 12

int main(void) {
  int days[MONTHS] = {31, 28, 31, 30};

  int * p_days = &days[0];

  int **p_p_days = &p_days; // **p_p_days 值为指针的地址
  printf("p_p_days: %p, *p_p_days: %p, p_days: %p, *p_days: %d, days: %p, *days: %d, days[0]: %d\n",
        p_p_days, *p_p_days, p_days, *p_days, days, *days, days[0]); // *p_p_days, p_days, *p_days, days是同一个地址

  // 数组名是数组首个元素的地址
  printf("p_days == days: %d\n", p_days == days); // 1
  /**
   * 在C中，指针+1值得是增加一个存储单元(这也是为什么必须声明指针所指向对象的类型)
   */
  printf("p_days + 1 == &days[1]): %d\n", p_days + 1 == &days[1]); // 1
  printf("*(p_days + 1) == days[1]: %d\n", *(p_days + 1) == days[1]); // 1

  int index;
  printf("sizeof(int): %zd\n", sizeof(int));
  for(index = 0; index < MONTHS; index++)
    // p_days + index, &days[index] 完全相同，且地址增加的单位为siziof(int) - 4个字节
    printf("Month %2d has %2d days. p_days + %2d: %p, &days[index]: %p\n",
          index + 1, *(days + index), index, p_days + index, &days[index]);
  
  char chs[2] = {'a', 'b'};
  printf("sizeof(char): %zd\n", sizeof(char));
  // 地址增加单位为sizeof(char) - 1字节
  printf("chs: %p, chs + 1: %p, *(chs): %c, *(chs +1): %c", chs, chs + 1, *(chs), *(chs +1));

  return 0;
}