/**
 * @file 8-1echo_eod.c
 * @brief 重复输入，直到文件结尾
 * 
 * 运算符：
 *   1. <  把文件中的内容导入程序,windows不能用<符号 echo_eof < words.txt
 *   2. >  把程序输出重定向至目标文件,会覆盖全部内容 echo_eof > words_bak.txt
 *   3. >> 把数据添加到现有文件末尾
 *   4. |  把一个文件的输出连接到另一个文件的输入
 * 使用2个重定向运算符(<和>)时，要遵循以下原则：
 *   1. 只能连接一个可执行文件和一个数据文件
 *   2. 不能读取多个文件输入，也不能输出至多个文件
 *   3. 通常，文件名和运算符之间的空格不是必须的
 */
#include<stdio.h>

int main(void) {
  int ch; // 使用int类型，EOF为-1

   // 使用linux - ctrl + d(^d) 或 windows - ctrl + z(^z)识别为文件结尾信号
   // 按下回车键时把缓冲区字符传入
   // EOF 在stdio.h已声明，一般为-1
  while ((ch = getchar()) != EOF)
    putchar(ch);
  
  return 0;
}