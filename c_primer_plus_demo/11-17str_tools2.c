/**
 * @file 11-17str_tools2.c
 * @brief string 工具函数2
 * @date 2022-08-26
 * 
 */
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "common.h"

#define REPLY "quit"
#define SIZE 20  
#define LIM 5
#define SIZE2 40
#define TARGSIZE 7

int main(void) {
  // goto lastest;
  /**
   * 2.
   * int strcmp(const char *_Str1, const char *_Str2)
   *   - 比较2个字符串是否相等(不是比较地址，而是字符串)
   *   - 相同返回0(返回是否为0，可判断是否相等)
   *   - strcmp(a, b),会比较字符串a, b 分别对应的每个字符的(ASCII码): 
   *     ai < bi 返回-1;ai = bi 返回0(此时比较下一位); ai > bi 返回 1(返回-1 0 1 可用于对字符串排序)
   * 
   * int strncmp(const char *_Str1, const char *_Str2, size_t _MaxCount)
   *   - 最大只比较前_MaxCount个字符
   */
  char str[SIZE];
  printf("enter EOF or quit to quit: \n");
  while (s_gets(str, SIZE)) {
    puts(str);
    // if (strcmp(str, REPLY) == 0) // 输入quit
    if (strncmp(str, REPLY, 2) == 0) // 输入qu*,只要前2个字符一致就识别为一致，返回0
      break;
  }
  /**
   * 3. 
   * char *strcpy(char *__restrict__ _Dest, const char *__restrict__ _Source)
   *   - 把源字符串(第2个参数)拷贝到目标字符串(包括末尾的空字符)
   *   - 返回第一个参数的值，即一个字符的地址
   *   - 第一个参数为目标起始点，源字符串拷贝会从目标地址开始
   *   - 有溢出风险(源字符串空间大于目标剩余空间)
   * 
   * char *strncpy(char *__restrict__ _Dest, const char *__restrict__ _Source, size_t _Count)
   *   - 第三个参数指明可拷贝的最大字符数，多的会忽略
   */

  char qworlds[LIM][TARGSIZE]; // 字符串数组，元素成员字符串空间为7个字符
  char temp[SIZE2]; // 存储临时输入的字符串
  int i = 0;
  printf("Enter %d words beginning with q: \n", LIM); // 输入q开头的5个单词
  while(i < LIM && s_gets(temp, SIZE2)) {
    if (temp[0] != 'q') {
      printf("%s does't begin with q!\n", temp);
      continue;
    }
    strncpy(qworlds[i], temp, TARGSIZE);
    qworlds[i][TARGSIZE - 1] = '\0'; // 防止temp数组长度超过TARGSIZE
    i++;
  }
  printf("qworlds:\n");
  for(i = 0; i < LIM; i++)
    printf("qworlds[%d]: %s\n", i, qworlds[i]);
  
  /**
   * 4.
   * static inline int sprintf(char *__stream, const char *__format, ...)
   *   - 把组合后的字符串存储在目标字符串中而不是显示在屏幕上
   *   - 从目标处存入，还会补入空字符
   *   - 还是有溢出风险(要保证有足够空间存储后面的字符串)
   */
  char s_show[SIZE];
  sprintf(s_show + 1, "hello %s, %d\n", "world", 120);
  puts(s_show);

  /**
   * 5.
   * char *strchr(const char *_Str, int _Val) - 返回查找的字符的地址
   *   - 如果_Str字符串包含_Val字符，返回首次指向的字符的指针(包含空字符)
   *   - 如果没找到，返回空字符
   * char *strrchr(const char *_Str, int _Ch)
   *   - 返回字符最后出现的位置(跟上面函数相反的查找方向)
   */
  char * hello = "hello";
  char * find_l = strchr(hello, 'l');
  printf("find_l: %p, hello + 2: %p, l: %c\n", find_l, hello + 2, *find_l);
  char * find_l_last = strrchr(hello, 'l');
  printf("find_l_last: %p, hello + 3: %p, l: %c\n", find_l_last, hello + 3, *find_l_last);
  char * find_m_last = strrchr(hello, 'm');
  printf("find_m_last: %p, find_m_last == NULL: %d\n", find_m_last, find_m_last == NULL);

  /**
   * 6.
   * char *strpbrk(const char *_Str, const char *_Control)
   *   - 查找在_Str中包含_Control的任意字符，并返回该字符位置，没找到返回NULL指针
   */
  // lastest:
  char * hello2 = "hello";
  if (strpbrk(hello2, "kkkke") == hello2 + 1)
    puts("ok");
  
  /**
   * 7.
   * char *strstr(const char *_Str, const char *_SubStr)
   *   - 返回指向_Str字符串中_SubStr字符串出现的首位置，没找到返回NULL
   */
  char * hello3 = "hello";
  if (strstr(hello3, "lo") == hello3 + 3)
    puts("ok");
  
  return 0;
}