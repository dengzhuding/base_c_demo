/**
 * @file 7-2cypher1.c
 * @brief 更改输入，空格不变
 * @date 2022-08-19
 * 
 * ctype.h头文件中的字符测试函数：
 * isalnum - 字母数字
 * isalpha - 字母
 * isblank - 标准的空白字符(空格、水平制表符或换行符)或任何其他本地化指定为空白的字符
 * iscntrl - 控制字符，如ctrl + B
 * isdigit - 数字
 * isgraph - 除空格之外的任意可打印字符
 * islower - 小写字母
 * isprint - 可打印字符
 * ispunct - 标点符号(除空格或字母数字字符之外的任意可打印字符)
 * isspace - 空白字符(空格、换行符、换页符、回车符、垂直制表符、水平制表符或其他本地化定义的字符)
 * isupper - 大写字母
 * isxdigit - 十六进制字符
 * 
 * ctype.h头文件中的字符映射函数：
 * tolower - 大写转小写
 * toupper - 小写转大写
 */

#include<stdio.h>
#include<ctype.h>

#define SPACE ' '

int main(void) {
  char ch;
  // getchar() - 相当于scanf("%c", &ch)
  // 赋值表达式=的值是赋值运算符左侧运算对象的值
  // 所以(ch = getchar()) - 的值就是ch的值
  while ((ch = getchar()) != '\n')
  {
    // if (ch == SPACE)
    if (!isalpha(ch)) // 非字符
      putchar(ch);
    else // 如果没有花括号，else与离他最近的if匹配
      putchar(ch + 1);
  }
  // 相当于printf("%c", ch)
  putchar(ch);
  
  return 0;
}