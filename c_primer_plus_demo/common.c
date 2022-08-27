/**
 * @file common.c
 * @brief 公共函数
 * @date 2022-08-26
 * 
 * 用法步骤：
 *    1. 在使用文件中用#include "common.h"
 *    2. 编译链添加common.c
 */
#include<stdio.h>

/**
 * @brief 当行输入字符串，去掉换行符，限制长度
 * 
 * @param st 
 * @param n 
 * @return char* 
 */
char * s_gets(char * st, int n) {
  char * ret_val;
  ret_val = fgets(st, n, stdin);
  if (ret_val == NULL)
    return ret_val;
  int i = 0;
  while (ret_val[i] != '\n' && ret_val[i] != '\0')
    i++; // // i定位到'\n' 或末尾空字符'\0'
  if (ret_val[i] == '\n') {
    ret_val[i] = '\0'; // 至少少一个存储空间： abc\0\0
  } else {
    while (getchar() != '\n') // 消耗输入行剩余部分
      continue;
  }
  return ret_val;
}