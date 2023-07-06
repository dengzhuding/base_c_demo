/**
 * @file 14-7io-other-fn.c
 * @brief 其他标准I/O函数
 * @date 2023-07-04
 * 
 */
#include <stdio.h>
#include <stdlib.h>

int main (void) {

  /**
   * @brief int ungetc() 函数把c 指定的字符放回输入流中
   * 输入 he:
   * 打印 he:
   * 
   */
  char ch;
  // char ch2;
  // while ((ch = getchar()) != ':') {
  //   putchar(ch);
  // }
  // ungetc(ch, stdin); // 将':'字符放回stdin
  // ch2 = getchar(); // 从缓冲区获取到字符':'
  // putchar(ch2);

  // ungetc('a', stdin); // ANSI C标准保证每次只会放回一个字符,下面2局执行无效
  // ungetc('b', stdin);
  // ungetc('c', stdin);
  // while ((ch = getc(stdin)) != EOF) {
  //   putchar(ch);
  // }

  // 例如，假设要读取下一个冒号之前的所有字符，但是不包括冒号本身，
  // 可以使用getchar() 或getc() 函数读取字符到冒号，然后使用ungetc() 函数把冒号放回输入流中
  printf("test ungetc():");
  while((ch = getc(stdin)) != EOF) {
    if (ch == ':')
      break;
  }
  ungetc(ch, stdin); // 此时':'会重新放回到流中
  char str[40];
  fgets(str, sizeof(str) - 1, stdin);
  fputs(str, stdout); // 打印":"开头的字符串

  // int fflush(FILE *fp); - 调用fflush() 函数引起输出缓冲区中所有的未写入数据被发送到fp 指定的输出文件。
  //                         这个过程称为刷新缓冲区 。如果fp 是空指针，所有输出缓冲区都被刷新
  /**
  int setvbuf(FILE * restrict fp, char * restrict buf, int mode, size_t size);
  setvbuf() 函数创建了一个供标准I/O函数替换使用的缓冲区
  在打开文件后且未对流进行其他操作之前，调用该函数。
  指针fp 识别待处理的流，buf 指向待使用的存储区。
  如果buf 的值不是NULL ，则必须创建一个缓冲区
  假设一个程序要储存一种数据对象，每个数据对象的大小是3000字节。
  可以使用setvbuf() 函数创建一个缓冲区，其大小是该数据对象大小的倍数
  如果操作成功，函数返回0 ，否则返回一个非零值。
   */

  // size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb,FILE * restrict fp);
  // fwrite() 函数把二进制数据写入文件
  // ptr - 在ANSI C函数原型中，这些实际参数都被转换成指向void 的指针类型，这种指针可作为一种通用类型指针
  //（在ANSI C之前，这些参数使用char * 类型，需要把实参强制转换成char * 类型）

  // size_t fread(void * restrict ptr, size_t size, size_t nmemb,FILE * restrict fp);
  // fread函数用于读取被fwrite() 写入文件的数据


  // int feof(FILE *fp) - 上一次输入调用检测到文件结尾时，feof() 函数返回一个非零值，否则返回0 
  
  // int ferror(FILE *fp) - 当读或写出现错误，ferror() 函数返回一个非零值，否则返回0
  
  // 

}