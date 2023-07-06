/**
 * @file 14-reverse.c
 * @brief 倒序显示文件的内容
 * @date 2023-07-04
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#define CNTL_Z '\032'
#define SLEN 81

int main (void) {
  char file[SLEN];
  FILE *fp;
  long offset, last;
  char ch;

  printf("please input the filename that need to be processed:");
  scanf("%80s", file);
  if ((fp = fopen(file, "rb")) == NULL) // 只读模式
  {
    fprintf(stderr ,"open file %s fail.", file);
    exit(EXIT_FAILURE);
  }
  // _Offset 偏移量，_Origin 初始位置，可设置3种(SEEK_END 末尾, SEEK_SET 开头, SEEK_CUR 当前位置)
  fseek(fp, 0L, SEEK_END);  // 指针位移到末尾

  // ftell用于获取文件位置指针当前位置相对于文件首的偏移字节数
  // 文件的第1个字节到文件开始处的距离是0 ，以此类推
  last = ftell(fp);

  /*
    * fseek() 和ftell() 潜在的问题是，它们都把文件大小限制在long 类型能表示的范围内
    * 鉴于此，ANSI C新增了两个处理较大文件的新定位函数：fgetpos() 和fsetpos() 。
    * 这两个函数不使用long 类型的值表示位置，它们使用一种新类型：
    * fpos_t （代表file position type，文件定位类型）
  fpos_t pos;
  // fgetpos() - 把fpos_t 类型的值放在pos 指向的位置上，该值描述了文件中的当前位置距文件开头的字节数
  fgetpos(fp, pos);
  // 使用pos 指向位置上的fpos_t 类型值来设置文件指针指向偏移该值后指定的位置
  fsetpos(fp, pos);
  */
 
  for (offset = 1L; offset <= last; offset++)
  {
    fseek(fp, -offset, SEEK_END); // 第1轮迭代，把程序定位到文件结尾的第1个字符（即，文件的最后一个字符）
    ch = getc(fp);
    if (ch != CNTL_Z && ch != '\r')     /* MS-DOS 文件 */
      putchar(ch);
  }
  
  if (fclose(fp) != 0)
  {
    fprintf(stderr ,"close file %s fail.", file);
  }
  return 0;
  
}