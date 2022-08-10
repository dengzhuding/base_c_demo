/**
 * @file 4-5scanf.c
 * @brief scanf()说明
 * @date 2022-08-10
 * 
 * scanf() 与 printf():
 * 1. scanf()把输入的字符串转换成整数、浮点数或字符串;
 *    printf()正好相反，把整数、浮点数、字符和字符串转换成显示在屏幕上的文本;
 * 2. prinf()函数使用变量、常量和表达式，而scanf()函数使用指向变量的指针:
 *    - 读取基本变量类型的值：变量名前加上一个&符号(地址运算符)
 *    - 把字符串读入字符串数组中，不要用&
 * 
 */
#include<stdio.h>
#include<string.h>

int main(void) {
  int age;
  float assets;
  char pet[30];

  /**
   * 格式字符串中的空白意味着跳过下一个输入项签名的所有空白;
   * 
   * 除了%c，其他转换说明都会自动跳过待输入值前面所有的空白,
   * 因此scanf("%d %d", &m, &n)与scanf("%d%d", &m, &n)行为相同;
   * 
   * 对于%c,scanf("%c", $ch)从输入的第一个字符开始读取,
   * 而scanf(" %c", $ch)从第一个【非空】字符开始读取
   * 
   * 
   */
  scanf("%d %f", &age, &assets); // 可用空格隔开，或换行符隔开

  // 还允许把普通字符放在格式化字符串中，如"%d,%f",这样的话就必须严格匹配输入1,2.0这样
  // scanf("%d,%f", &age, &assets);

  scanf("%s", pet);
  printf("age: %d\nassets: %f\npet: %s\n", age, assets, pet);

  int c_n = getchar(); // 这里会去取得换行键 ASCII编号为10

  // 读取单个字符
  int c_a = getchar(); // 这里才是输入的字符
  printf("you input char is %c, and c_n's number is %d", c_a, c_n);

  getchar();

  // 读取包含空格的字符
  char s_input[20];
  printf("size of *s_input is %zd\n", sizeof(s_input));
  fgets(s_input, sizeof(s_input), stdin); // 文件或者流中获取字符串 - 存sizeof(s_input) - 1个字符
  printf("you input the str is: %s and strlen is: %zd\n", s_input, strlen(s_input));

  return 0;
}