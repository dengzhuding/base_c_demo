/**
 * @file 7-1talkback.c
 * @brief 演示与用户交互
 * @version 0.1
 * @date 2022-08-04
 * 
 * @copyright Copyright (c) 2022
 * 
 * 字符串(character string) - 是一个或多个字符的序列，用双引号(")包括,而字符常量用单引号(')
 * C语言没有专门用于存储字符串的变量类型，字符串都被存储在char类型的数组中
 * C语言中的字符串一定以空字符(\0)结束，这意味着数组的容量至少比待存储字符串中的字符多1
 * strlen - 字符串占用长度(不包括空字符)
 * sizeof - 存储单元长度,
 * 
 * 定义常量：
 * 1. 声明赋值：int PI = 3.14; (可能无意间修改值)
 * 2. 预处理器定义常量:#define NAME value  (运行时不可改)
 *   经过编译时替换(compile-time substitution)
 *   在运行程序时，程序中所有的替换已经完成，这样的常量也称为明示常量(manifest costant)
 * 3. const 限定符(C99新增): const int KEY = value; (不可修改)
 */
#include<stdio.h>
#include<string.h> // 提供strlen()原型

#define DENSITY 62.4 // 定义常量 人体密度
#define PRAISE "hello "

#include<limits.h> // 这里面提供了整数类型大小限定的相关信息，float.h提供浮点型的
#include<float.h>

int main(void) {
  // 空格不是空字符
  char c_space = '\x20'; // 空格 32 '\040' '\x20'
  char c_space2 = ' ';
  char c_null = '\00'; // 空字符 0 '\00' '\x00'
  printf("c_space's number is %d, c_space2's number is %d, c_nul's number is %d\n",
        c_space, c_space2, c_null);
  printf("c_space is:----%c----, c_space2 is:----%c----, c_null is:----%c----\n",
        c_space, c_space2, c_null); // c_space is:---- ----, c_space2 is:---- ----, c_null is:--------
  // return 0;

  float weight, volume;
  int size, letters;
  char name[40]; // 分配固定存储空间 可容纳40个字符(40字节)的数组 - 最后一个是空字符,所以可以存储输入的39个字符
  printf("your name: ");

  // 根据%s转换说明，scanf只会读取字符串中的一个单词(遇到空格，制表符，换行符就不再读取输入)，而不是一整句
  // C语言还有其他输入函数(如fgets())，用于读取一般字符串
  scanf("%s", name); // %s 处理字符串输入输出， name没有用&(取地址符)

  // char name2[40] = "test name";
  // strcpy(name, name2); // 使用strcopy函数初始化


  printf("%s, your weight: ", name);
  scanf("%f", &weight); // 用了& - 引用
  // weight = 80;

  size = sizeof(name);
  letters = strlen(name);
  volume = weight / DENSITY;

  printf("size: %d  letters: %d  volume: %f\n", size, letters, volume); // size: 40  letters: 3  volume: 0.801282

  char c_x = 'x'; // x
  // s_x是个指针,存储单元为8字节 = 64位
  char *s_x = "x123456789"; // 将字符串地址赋值给指针变量 (char [11])"x123456789" -> *S_X 
  printf("c_x is - %c, s_x is - %s, PRAISE is - %s, name is - %s\n",
        c_x, s_x, PRAISE, name);
  printf("c_x strlen: %d, s_x strlen: %zd, PRAISE strlen: %zd, name strlen: %zd\n",
        1, strlen(s_x), strlen(PRAISE), strlen(name)); // 
  printf("c_x sizeof: %zd, s_x sizeof: %zd, PRAISE sizeof: %zd, name sizeof: %zd\n",
        sizeof(c_x), sizeof(s_x), sizeof(PRAISE), sizeof(name)); // 
  /*
    c_x is - x, s_x is - x123456789, PRAISE is - hello , name is - DZD
    c_x strlen: 1, s_x strlen: 10, PRAISE strlen: 6, name strlen: 3
    c_x sizeof: 1, s_x sizeof: 8, PRAISE sizeof: 7, name sizeof: 40
  */

  // 使用limits.h 和float.h头文件中的明示常量
  printf("range for int: %d ~ %d\n", INT_MIN, INT_MAX);
  printf("One byte = %d bits on this system.\n", CHAR_BIT);
  printf("float precision = %d digits\n", FLT_DIG);
  return 0;
}