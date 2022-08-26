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
    // i定位到'\n' 或末尾空字符'\0'
    i++;
  if (ret_val[i] == '\n') {
    // 至少少一个存储空间： abc\0\0
    ret_val[i] = '\0';
    return ret_val;
  }
  else {
    /**
     * 读到末尾都没有换行符，有2种可能：
     *   1. 换行符刚好在空字符处被截断 - 输入的字符完全存储了
     *   2. 在换行符前面就被截断了 - 存储不完整
     * 者两种情况无法区分,只能都算存储不完整，然后就全部舍弃了
     */
    while (getchar() != '\n') // 消耗输入行剩余部分
      continue;
    // 重制存储单元为空字符
    ret_val[0] = '\0';
    // NULL指针的值为: 0000000000000000
    return NULL;
  }
}