/**
 * @file 13-1count.c
 * @brief 用标准I/O读取文件和统计文件中的字符数
 * @date 2023-07-03
 * 如果main() 在一个递归程序中，exit() 仍然会终止程序，
 * 但是return 只会把控制权交给上一级递归，直至最初的一级。然后return 结束程序。
 * return 和exit() 的另一个区别是，即使在其他函数中（除main() 以外）调用exit() 也能结束整个程序。
 * 
fopen() 的模式字符串:

"r"-以读模式打开文件
"w"-以写模式打开文件，把现有文件的长度截为0，如果文件不存在，则创建一个新文件
"a"-以写模式打开文件，在现有文件末尾添加内容，如果文件不存在，则创建一个新文件
"r+"-以更新模式打开文件（即可以读写文件）
"w+"-以更新模式打开文件（即，读和写），如果文件存在,则将其长度截为0；
      如果文件不存在,则创建一个新文件
"a+"-以更新模式打开文件（即，读和写），在现有文件的末尾添加内容，
      如果文件不存在则创建一个新文件；可以读整个文件，但是只能从末尾添加内容

"rb" 、"wb" 、"ab" 、
"rb+" 、"r+b" 、"wb+" 、
"w+b" 、"ab+" 、"a+b" - 与上一个模式类似，但是以二进制模式而不是文本模式打开文件
(像UNIX和Linux这样只有一种文件类型的系统，带b 字母的模式和不带b 字母的模式相同。)

"wx" 、"wbx" 、
"w+x" 、"wb+x" 或"w+bx" - （C11）类似非x模式，但是如果文件已存在或以独占模式打开文件，则打开文件失败
(新的C11新增了带x 字母的写模式，与以前的写模式相比具有更多特性。
第一，如果以传统的一种写模式打开一个现有文件，fopen() 会把该文件的长度截为0 ，
    这样就丢失了该文件的内容。但是使用带x 字母的写模式，即使fopen() 操作失败，原文件的内容也不会被删除。
第二，如果环境允许，x 模式的独占特性使得其他程序或线程无法访问正在被打开的文件)

指向标准文件的指针,stdio.h 头文件把3个文件指针与3个标准文件相关联，C程序会自动打开这3个标准文件
标准文件  文件指针  通常使用的设备
标准输入  stdin    键盘
标准输出  stdout   显示器
标准错误  stderr   显示器
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief 执行时接收一个需要统计字符数文件路径的参数
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) {
  char ch; // 接收文件字符
  unsigned long count = 0; // 计数统计
  // "文件指针" - 是指向FILE 的指针，FILE 是一个定义在stdio.h 中的派生类型
  // 文件指针fp 并不指向实际的文件，它指向一个包含文件信息的数据对象，
  // 其中包含操作文件的I/O函数所用的缓冲区信息
  FILE *fp; 

  if (argc == 1)
    exit(EXIT_FAILURE); // exit() 函数关闭所有打开的文件并结束程序。exit() 的参数被传递给一些操作系统
  if ((fp = fopen(argv[1], "r")) == NULL)
    exit(EXIT_FAILURE);
  while ((ch = getc(fp)) != EOF) {
    putc(ch, stdout); // 把字符ch 放入FILE 指针fpout 指定的文件中.相当于putchar, getc(stdin)相当于getchar()
    count++;
  }
  if (fclose(fp) != 0)
    printf("Error in closing file %s\n", argv[1]); // 关闭fp 指定的文件，必要时刷新缓冲区

  printf("File %s has %lu characters\n", argv[1], count);
  
  return 0;
}