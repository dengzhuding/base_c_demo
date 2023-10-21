/**
 * @file 11-17str_tools.c
 * @brief 字符串函数
 * 
 */
#include<stdio.h>
#include<string.h>
#include "common.h"

#define HELLO "hello world."
#define SIZE 30
#define LIMIT 10


int main(void) {
  /**
   * 1.
   * size_t strlen(const char *_Str)
   *   - 统计字符串的长度(不包含空字符'\0')
   */
  const char * p_hello = HELLO;
  printf("\"%s\" - length: %llu\n", HELLO, strlen(HELLO));
  while(*p_hello)
    putchar(*p_hello++);
  printf("*p_hello: %d\n", *p_hello);

  /**
   * 1. 
   * char *strcat(char *__restrict__ _Dest, const char *__restrict__ _Source)
   *   - 拼接字符串，该函数把第二个字符串的备份附加再第一个字符串末尾，
   *     并把拼接后形成的新字符串作为第一个字符串，第二个字符串不变
   *   - 无法检查第一个数组是否能容纳第2个字符串
   * 
   * 下面把多行输入合并到一个单行字符串(没有换行符)
   */
  char s_lines[SIZE];
  *s_lines = 0; // 设置首字符为空字符
  char s_line_limit[LIMIT];
  char * ret_strcat;
  printf("Enter string (enter empty line or EOF to quit):\n");
  while(fgets(s_line_limit, LIMIT, stdin) != NULL && *s_line_limit != '\n') {
    printf("------\nsatrt deal:\n");

    // 去除输入的换行符
    char * p_i = s_line_limit;
    while (*p_i != '\n' && *p_i != '\0')
      p_i++;
    if (*p_i == '\n')
      *p_i = '\0';

    // fputs(s_lines, stdout); // 这个如果没有换行符，是不会从缓冲区输出到屏幕的
    printf("s_lines: %s\n", s_lines);
    printf("strlen(s_lines): %llu, strlen(s_line_limit): %llu\n",strlen(s_lines), strlen(s_line_limit));
    
    if (strlen(s_lines) + strlen(s_line_limit) >= SIZE) { // 溢出
      printf("length overflow %d and break.\n", SIZE);
      break;
    }

    ret_strcat = strcat(s_lines, s_line_limit);
    printf("s_lines: %p, s_line_limit: %p, ret_strcat: %p\n",s_lines, s_line_limit, ret_strcat);
    
    printf("s_lines: %s\n", s_lines);
    printf("strlen(s_lines): %llu, strlen(s_line_limit): %llu\n",strlen(s_lines), strlen(s_line_limit));
  }

  /**
   * 
   * char *strncat(char *__restrict__ _Dest, const char *__restrict__ _Source, size_t _Count)
   *   - 第三个参数指定了最大添加字符数，在加到_Count个字符或遇到空字符时停止
   */
  char addonp[] = "appended strings.";
  char s_input[SIZE];
  printf("Enter the string Merge to s_line2: ");
  s_gets(s_input, SIZE);
  int available;
  available = SIZE - strlen(s_input) - 1; // 允许添加的最大字符数
  puts(s_input);
  printf("sizeof(s_input): %zd, strlen(s_input): %llu, available: %d\n", sizeof(s_input), strlen(s_input), available);
  
  strncat(s_input, addonp, available); // 这里可限制第二个字符串合并字符数最大是available
  
  puts(s_input);

  /**
   * void *memcpy(void * restrict s1, const void * restrict s2, size_t n);
   * void *memmove(void *s1, const void *s2, size_t n);
   * 这两个函数都从s2 指向的位置拷贝n 字节到s1 指向的位置，而且都返回s1 的值。
   * 所不同的是，memcpy() 的参数带关键字restrict ，即memcpy() 假设两个内存区域之间没有重叠；
   * 而memmove() 不作这样的假设，所以拷贝过程类似于先把所有字节拷贝到一个临时缓冲区，然后再拷贝到最终目的地。
   */

  return 0;
}