/**
 * @file 13-3addaword.c
 * @brief 文件I/O函数fprintf() 和fscanf() 函数的工作方式与printf() 和scanf() 类似，
 *        区别在于前者需要用第1个参数指定待处理的文件
 * 文件I/O函数fprintf() 和fscanf() 函数的工作方式与printf() 和scanf() 类似，
 * 区别在于前者需要用第1个参数指定待处理的文件
 * 由于fgets() 保留了换行符，fputs() 就不会再添加换行符，它们配合得非常好
 * @date 2023-07-04
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 40
int main () {
  FILE *fp;
  char *file_name = "wordy.txt"; // 创建在程序命令执行路径下
  if ((fp = fopen(file_name, "a+")) == NULL) { // a+ 可读取
    fprintf(stdout, "open file %s fail!", file_name);
    exit(EXIT_FAILURE);
  }
  char words[LENGTH];
  fprintf(stdout, "please enter words, '#' at beganing to stop.\n");
  while ((fscanf(stdin, "%40s", words) == 1) && words[0] != '#') {
    // fputs(words, fp);
    fprintf(fp, "%s\n", words); // 可以格式化输入字符串
  }

  rewind(fp); /* 返回到文件开始处 */

  while (fscanf(fp, "%s", words) == 1) {
    puts(words);
  }
  if (fclose(fp) != 0) {
    fprintf(stderr, "close file %s fail!", file_name);
  }

  return 0;
}