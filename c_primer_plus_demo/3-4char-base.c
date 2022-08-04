/*
C语言把1字节(8位)定义位char类型占用的位数。
在C语言中，用单引号包括起来的单个字符被称为字符常量(character constant)。

根据C90标准，C语言允许在关键字char前面使用signed(有符号)或unsigned(无符号)，
这在用 char类型处理小整数(-128~127 或0~255)时很有用，如果只用chare处理字符，那么无需使用修饰符。
*/

#include<stdio.h>

int main(void) {
  char grade = 'A'; // 单引号定义字符常量，双引号定义字符串
  // 实际上，字符是以数值存储的，所以也可以用数字代码值来赋值
  char geade2 = 65; // 系统使用ASCII码才能正确赋值A,所以用'A'代替65才是妥当的做法

  // 奇怪的是，C语言将字符常量视为int类型而非char类型
  char grade3 = 'B'; // 本来'B'对应的66存储在32位的存储单元中，却可以存储在8位的存储单元中(grade3)

  /*
  定义一个字符常量'FATE',即把4个独立的ASCII码存储在一个32位存储单元中。
  如果把这样的字符常量赋给char类型变量grade4,只有最后8位有效
  */
  char grade4 = 'FATE'; // grade4的值是'E'

  // 表示非打印字符(3中方式)
  // 1. 使用ASCII码
  char beep = 7;
  /* 2. 使用转义序列(escape sequence):
      \a - 警报(蜂鸣，有些系统不起作用), \b - 退格, \f - 换页, \n - 换行, \r - 回车,把活跃位置（光标位置）移动到当前行的开始处
      \t - 水平制表符, \v - 垂直制表符
      \\ - 反斜杠, \' - 单引号, \" - 双引号, \? - 问号
      \0oo - 八进制值(oo必须是有效八进制数0~7)
      \xhh - 十六进制值(hh必须是有效十六进制值0~f)
  */
  char nerf = '\n'; 
  char beer = '\007'; // 可省略前面的零0，任然解释为八进制 \a - \007
  // 3. 使用十六进制表示字符常量
  char ss = '\x0f';

  printf("警报符：\a  \" \' \n hello \r.\n");
  printf("beer：%c  grade：%c\n", beer, grade); // beer：  grade：A   (%c指明待打印的字符)
  printf("ss:%#x 对应的十进制为: %d  geade2对应的字符为%c\n", ss, ss, geade2); //ss:0xf 对应的十进制为: 15  geade2对应的字符为A

  char ch;
  scanf("%c", &ch); // &符号表示把输入的字符赋给变量ch
  printf("The code for %c is %d.", ch, ch);
  // getchar();
  return 0;
}