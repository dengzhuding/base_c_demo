/**
 * @file 11-31repeat.c
 * @brief 命令行参数
 * 
 * 编译： gcc -Wall repeat.c -o repeat
 * 执行命令: repeat -name test
 * 
 * C编译器允许main()没有参数或有2个参数(一些实现允许main()有更多参数，属于对标准的拓展)
 *   - argc(argument count) 参数计数，包括执行文件名argc >= 1 
 *   - argv(argument alue) 是一个指向指针的指针，它所指向的指针指向char
 *     - argv[0] 执行文件路径字符串
 *     - argv[1] 第一个参数
 *   - int main(int argc, char **argv)
 *   - **argv 和 char *argv[] 等价
 *   - 许多环境(UNIX,DOS)都允许用双引号把多个单词括起来形成一个参数字符串
 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 40

int main(int argc, char **argv) {
  int i;
  puts("argv: ");
  for (i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }

  /**
   * 字符串转数字(需要包含stdlib.h)
   *   - atoi() atof() atod()
   *   - 以下函数的智能之处在于能够识别和报告字符串中的首字母是否为数字：
   *     long strtol(const char *__restrict__ _Str, char **__restrict__ _EndPtr, int _Radix)
   *     static inline float strtof(const char *__restrict__ _Str, char **__restrict__ _EndPtr)
   *     static inline double strtod(const char *__restrict__ _Str, char **__restrict__ _EndPtr)
   *       - _Str(源字符串)
   *       - _EndPtr(将被设置为标识输入数字结束字符的地址)
   *       - _Radix(进制-最多可转换三十六进制)
   * 
   * 数字转字符串：
   *   - static inline int sprintf(char *__stream, const char *__format, ...)
   *       - 存到__stream
   *     
   * 
   */
  char input_num[SIZE];
  puts("Enter nunmbe(empty line or EOF to quit):");
  while (fgets(input_num, SIZE, stdin) != NULL && input_num[0] != '\n') {
    char * p_enter = strchr(input_num, '\n');
    // 替换换行符
    if (p_enter != NULL)
      *p_enter = '\0';
    else
      // 消耗输入行剩余字符
      while (getchar() != '\n')
        continue;

    printf("your input is: %s\n", input_num);
    printf("And convert to number:\n ");
    //
    printf("atoi: %d, atol: %ld, atof: %f\n",
        atoi(input_num), atol(input_num), atof(input_num));
    char * endptr0;
    char * endptr1;
    char * endptr2;
    char * endptr3;
    // 注意第二个参数用了&endptr1，说明传入的参数是一个指向指针的指针
    printf("strtol_10: %ld, strtol_16: %ld, strtof: %f, strtod: %f\n",
        strtol(input_num, &endptr0, 10), strtol(input_num, &endptr1, 16), strtof(input_num, &endptr2), strtod(input_num, &endptr3));
    if (endptr0 == input_num)
      printf("first character [%c] maybe is not a available number.\n", *endptr0);
    printf("endptr1: %s, endptr2: %s, endptr3: %s\n", endptr1, endptr2, endptr3);
    
    puts("Enter nunmbe(empty line or EOF to quit):");
  }
  
  return 0;
}