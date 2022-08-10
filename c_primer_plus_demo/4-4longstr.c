/**
 * @file 4-4longstr.c
 * @brief 给字符串断行
 * @version 0.1
 * @date 2022-08-10
 * 
 */
#include<stdio.h>

int main(void) {
  // 3中方法
  // 1. 使用多个printf函数
  printf("hello ");
  printf("world\n");

  // 2. 用反斜杠(\)和Enter(或Return)键组合类断行,下一行需要不能缩进
  printf("hello \
world\n");

  // 3. ANSI C引入的字符串拼接：
  printf("hello" " word"
        "!");
  return 0;
}