/*
功能：输入整数字符串，输出转换为各种进制
  - 当前版本：仅支持输入十进制数字转换显示
*/

#include<stdio.h>
#include<stdlib.h>

int main(void) {
  // char *numStr;
  int numStr; 
  // printf("转换整数，支持类似0b123,123,0123,0x123这种多种进制\n请输入:");
  printf("转换整数，暂时仅支持十进制整数\n请输入:");
  scanf("%d", &numStr); // &是一个取地址运算符
  char s[10];
  itoa(numStr, s, 2);
  printf("二进制binary: 0b%s\n八进制octal: %#o\n十进制decimal: %d\n十六进制hex: %#x\n", s, numStr, numStr, numStr);
  // 去空格
  // 识别前缀判定进制123
  // printf("%s识别为进制", numStr);
  // 分别输入各种进制显示
  // print_num(numStr);
  return 0;
}
/*
void print_num(char * numStr) {
  char numStr_s;
  // printf("二进制binary: %s\n八进制octal: %#o\n十进制decimal: %d\n十六进制hex: %#x", numStr, );
}
*/