/**
 * @file 9-15swap3.c
 * @brief 使用指针解决交换函数的问题
 * 
 * 与指针相关的运算符：
 *   & - 后跟一个变量名时，&给出该变量的地址
 *   * - (间接运算符)后跟一个指针名或地址时，*给出 存储在指针指向地址上 的值
 * 
 * %p是输出地址的转换说明
 * 
 * 声明指针变量必须指定 指针所指向变量的类型 ,
 * 因为不同的变量类型占用不同的存储空间,一些指针操作要求知道操作对象的大小
 * int * pi; // pi是指向int类型变量的指针，*pi是int类型
 * char * pc;
 * float * pf;
 * 
 * *号和指针名之间的空格可有可无，
 * 通常，程序员在声明是使用空格(int * pi)，在解引用变量时省略空格(temp = *pi)
 * 
 * 指针的值是一个地址，在大部分系统内部，
 * 该地址由一个无符号整数表示(实际上指针是一个新类型，ANSI提供了%p格式的转换说明)
 * 
 * C没有引用变量(像javascript Object类型这样)，所以要用变量的地址对值做修改(使用指针在函数间通信)
 * 
 * 变量-名称、地址和值:
 *   普通变量 - 把值作为基本量，把地址作为通过&运算符获得的派生量
 *   指针变量 - 把地址作为基本量，把值作为通过*运算符获得的派生量
 */
#include<stdio.h>

void interchange(int * u, int * v); // 2个参数为指针类型

int main(void) {
  int x, y;
  printf("Enter x y, then the value will be changed: ");

  // 下面的scanf()函数中需要改变主调函数中变量x,y的值，必须传递他们的地址
  // 而printf()函数不需更改变值，所以不用取地址符号&
  while (scanf("%d %d", &x, &y) == 2) {
    printf("before change:\nx: %d, x-addr: %p, y: %d, y-addr: %p\n", x, &x, y, &y);
    // 交换的是变量地址指向的值
    interchange(&x, &y);
    printf("after change:\nx: %d, x-addr: %p, y: %d, y-addr: %p\n", x, &x, y, &y);

    printf("Enter x y, then the value will be changed: ");
  }
  
  return 0;
}

/**
 * @brief 交换2个整数变量的值
 * 
 * @param u 
 * @param v 
 */
void interchange(int * u, int * v) {
  int temp;
  int * p_temp; // 声明指针p_temp-是指向int类型变量的指针
  p_temp = &temp; // &temp - 取出变量temp的地址

  temp = *u; // *u - 获取存取在该地址的值

  printf("u: %p u-value: %d, v: %p v-value: %d, p_temp: %p p_temp-value is temp: %d\n",
      u, *u, v, *v, p_temp, temp);
  
  *u = *v; // 把指针v指向的地址的值取出  赋值给  u指向的地址 --- 相当于 x=y(如果访问得到)
  // *v = temp; // 也可以写成: *v = *p_temp; - 把temp的值赋值给v指向的地址
  *v = *p_temp;

  printf("u: %p u-value: %d, v: %p v-value: %d, p_temp: %p p_temp-value is temp: %d\n",
        u, *u, v, *v, p_temp, temp);
}