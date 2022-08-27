/**
 * @file 11-14customize_nput_output.c
 * @brief 自定义输入输出
 * 
 */
#include<stdio.h>
#define HELLO "hello world !"

void put1(const char * str);

int main(void) {
  const char * P_hello = "hello world !";
  char hello[] = HELLO;
  
  /**
   * 输出：
   * hello: 0000000b68bff6ba, P_hello: 00007ff6ad359000, HELLO: 00007ff6ad359000, "hello world !": 00007ff6ad359000
   * 
   * 说明"hello world !"是静态常量
   * 数组 - hello 复制了一边常量(用于可修改操作)
   * 指针 - P_hello, HELLO, "hello world !" 指向同一个地址(用于不可修改)
   * 
   */
  printf("hello: %p, P_hello: %p, HELLO: %p, \"hello world !\": %p\n",
      hello, P_hello, HELLO, "hello world !");
  char c_null = '\0';
  printf("character '\\0' and the number is: %d\n", c_null); // '\0' 的存储整数码为0
  
  put1(P_hello);
  return 0;
}

void put1(const char * str) {
  while (*str != '\0') // 或用 while(*str) - 当str指向空字符时，*str的值是0，循环结束
    // ++ 的优先级高于*(间接运算符或解引用运算符)，因此打印str的值，递增的是str本身
    putchar(*str++);
}