/**
 * @file 7-7worfcnt.c
 * @brief 统计字符数、单词数、行数
 * @date 2022-08-21
 * 
 */
#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>

#define STOP '|'

int main(void) {
  char c;
  char prev;
  long n_chars = 0L;
  int n_lines = 0;
  int n_words = 0;
  int p_lines = 0;
  bool inword = false;
  prev = '\n';
  // printf("please enter words and enter 'CTRL + B' to exit:\n");
  while((c = getchar()) && c != STOP) {
    n_chars++;
    if (c == '\n') {
      n_lines++;
    }
    if (!inword && isgraph(c)) { // 没有进入单词 且 非空白字符
      n_words++;
      inword = true;
    }
    if (inword && isspace(c)) {
      inword = false;
    }
    prev = c;
  }
  if (prev != '\n')
    p_lines = 1;
  printf("characters = %ld, worlds = %d, lines = %d, ", n_chars, n_words , n_lines);
  printf("partial lines = %d\n", p_lines);

  return 0;
}