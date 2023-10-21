/**
 * @file 15-1bit.c
 * @author your name (you@domain.com)
 * @brief 位操作
 * @date 2023-07-11
 * 
 * 每个八进制(0开头)位对应3个二进制(0b开头)位 0 - 000, 7 - 111
 *   0o567 - 101 110 111
 * 每个十六进制位都对应一个4位的二进制数（即4个二进制位），
 * 那么两个十六进制(0x开头)位恰好对应一个8位字节 0 - 0000, 15 - 1111
 *   0xa36 - 1010 0011 0111
 * 
 * C有两个操控位的工具(用一般形式的整型变量或常量即可运算)
 * 1. 第1个工具是一套（6个）作用于位的按位运算符
 *   (4个按位逻辑运算符都用于整型数据，包括char)
 *   二进制反码或按位取反(~):
 *      把1变为0，把0变为1 ~(1010) -> 0101
 *   按位与(&, &=  用法：掩码、打开位、关闭位、检查位的值): 
 *      通过逐位比较2个运算对象生成一个新值，对于每个位，只有两个对象中相应的位都为1时，
 *      结果才为1(任何位与0 组合都得0 ,1 号位的值不变)
 *   按位或(|, |=): 
 *       逐位比较两个运算对象，生成一个新值。对于每个位，如果两个运算对象中相应的位有1，
 *       结果就为1(任何位与0 组合，结果都为本身；任何位与1 组合，结果都为1)
 *   按位异或(^, ^=  用法：切换位): 
 *        逐位比较两个运算对象。对于每个位,如果两个运算对象中相应位一个为1，结果为1 
 *   (移位运算符)
 *   左移(<<, <<=):
 *        左移运算符（<< ）将其左侧运算对象每一位的值向左移动其右侧运算对象指定的位数。
 *        左侧运算对象移出左末端位的值丢失，用0 填充空出的位置
 *   右移(>>, >>=):
 *        右移运算符（>> ）将其左侧运算对象每一位的值向右移动其右侧运算对象指定的位数。
 *        左侧运算对象移出右末端位的值丢失
 *        对于无符号类型，用0填充空出的位置；对于有符号类型，其结果取决于机器。
 *        空出的位置可用0填充，或者用符号位（即，最左端的位）的副本填充
 * 
 * 2. 第2个工具是字段 （field ）数据形式，用于访问int 中的位
 *   操控位的第2种方法是位字段 （bit field ）
 *  struct {unsigned int a : 1;unsigned int b : 1;} p; p包含2个1位的字段
 *  可以通过普通的结构成员运算符（. ）单独给这些字段赋值
 *  p.a = 1; p.b = 0; (但是，要确保所赋的值不超出字段可容纳的范围)
 * 
 */
#include <stdio.h>
#include<stdlib.h>
#include <limits.h>  // 提供 CHAR_BIT 的定义，CHAR_BIT 表示每字节的位数

#define BYTE_MASK 0xff

// 通过查看此联合类型的存储情况确认大端还是小端存储模式
union StorageMode {
  unsigned short num; // 2 byte
  struct {
    char big; // 1 byte
    char small; // 1 byte
  };
};
union Four_num {
  unsigned int num;
  struct {
    char one;
    char two;
    char three;
    char four;
  };
};

/**
 * @brief 
 * 小端模式：强制类型转换数据不需要调整字节内容。
 * 大端模式：符号位判断固定为第一个字节，容易判断正负，便于人类阅读
------ 常见的处理器大小端架构 ---------
处理器     端模式 
IntelX86  Little-Endian
Power-PC  Big-Endian
IBM       Big-Endian
ARM       默认 Little-Endian
STM32     Little-Endian
-------------------------------------
 */
void show_Endian(void);

/**
 * @brief 表示interger to binary string ，即整数转换成二进制字符串
 * @param num int类型数字
 * @param str 存储二进制字符串,需要str数组比int类型字节大1，用于存储'\0'
 * @return char* 返回指向char类型的指针，即str
 */
char * itobs(int num , char *str);
char * ftobs(float num , char *str);
/*4位一组显示二进制字符串 */
void show_bstr(const char * str);
/**
 * @brief 切换一个值中的后n 位，待处理值和n 都是函数的参数。
 * 
 * @param num 处理值
 * @param bits 后bits位需要切换
 * @return int 
 */
int invert_end(int num, int bits);

int main(void) {
  show_Endian();

  float f = 0.527;
  int n = 10;
  char str[33];
  itoa(n, str, 2);
  printf("%f %s", f, str);

  /** 移位运算符还可用于从较大单元中提取一些位 */
  unsigned long color = 0x002a162f; // 4字节，存2种色值
  unsigned char blue, green, red;
  red = color & BYTE_MASK; // 按位与操作 0x002a162f & 0xff -> 0x2f
  green = (color >> 8) & BYTE_MASK; // 先右移8位，用0填充，再进行按位与 -> 0x16
  blue = (color >> 16) & BYTE_MASK; // 先右移16位，用0填充，再进行按位与 -> 0x2a
  printf("red, green, blue: 0x%x 0x%x 0x%x\n",red, green, blue);

  /** 整数显示位二进制 */
  char bin_str[CHAR_BIT * sizeof(int) + 1];
  itobs(0x12, bin_str);
  show_bstr(bin_str); // 0000 0000 0001 0010
  itobs(0x1f1f, bin_str);
  show_bstr(bin_str); // 0001 1111 0001 1111
  // 切换一个值中的后8位
  itobs(invert_end(0x1f1f, 8), bin_str);
  show_bstr(bin_str); // 0001 1111 1110 0000
  // float test
  printf("test float number\n");
  ftobs(0.1, bin_str);
  show_bstr(bin_str); //
  ftobs(0.2, bin_str);
  show_bstr(bin_str);
  ftobs(0.3, bin_str);
  show_bstr(bin_str);
  ftobs(0.1 + 0.2, bin_str);
  show_bstr(bin_str);

  return 0;
}

void show_Endian(void) {
  // 占用2个字节，看是0000 0001 - 高地址存低字节（大端）, 0001 0000 - 底地址存高字节（小端）
  union StorageMode num = {1}; 
  union Four_num n;
  // 十六进制整数，方便与二进制格式做对比(因为F - 15 正好对应1111 1111)
  n.num = 0x12345678;
  // 地址顺序(左->右)：底地址->高地址
  // 0001 0010  0011 0100  0101 0110  0111 1000 (这样书写是大端，方便人类查看)
  // 实际存储内容为: 0111 1000  0101 0110  0011 0100  0001 0010
  if (n.one == 0x78) { // n.one 取 0111 1000也就是0x78
    printf("Little-Endian");
  }
  if (num.big == 1) {
    printf("Little-Endian"); // intelx86打印这条(小端模式)
  } else {
    printf("big-Endian");
  }
}

char * itobs(int num , char *str) {
  const static int size = CHAR_BIT * sizeof(int);
  int temp = num;
  char ch;
  for (int n = size - 1; n >= 0; n--, temp >>= 1) {
    ch = (01 & temp) == 1 ? '1' : '0';
    str[n] = ch;
  }
  str[size] = '\n';
  return str;
}

char * ftobs(float num , char *str) {
  const static int size = CHAR_BIT * sizeof(float);
  int *c_pt = (int *)&num;
  int temp = *c_pt;
  char ch;
  for (int n = size - 1; n >= 0; n--, temp >>= 1) {
    ch = (01 & temp) == 1 ? '1' : '0';
    str[n] = ch;
  }
  str[size] = '\n';
  return str;
}

void show_bstr(const char * str)
{
    int i = 0;

    while (str[i])  /* 不是一个空字符 */
    {
        putchar(str[i]);
        if (++i % 4 == 0 && str[i])
            putchar(' ');
    }
}

int invert_end(int num, int bits) {
  int mask = 0; // 最终形成的掩码
  int bitval = 1;
  while (bits-- > 0) {
    mask |= bitval; //按位或，位数为1的对应位转为1
    bitval <<= 1; // 左移一位，0填充

  }
  return num ^ mask;
}
