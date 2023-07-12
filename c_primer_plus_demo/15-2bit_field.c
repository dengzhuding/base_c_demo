/**
 * @file 15-2bit_field.c
 * @brief 位字段是一个signed int 或unsigned int 类型变量中的一组相邻的位
 * （C99和C11新增了_Bool 类型的位字段）
 * @date 2023-07-11
 * 
 * 
 */
#include<stdio.h>


/** 
 * 如果声明的总位数超过了一个unsigned int 类型的大小会怎样？
 * 会用到下一个unsigned int 类型的存储位置。
 * 一个字段不允许跨越两个unsigned int 之间的边界。
 * 编译器会自动移动跨界的字段，保持unsigned int 的边界对齐。
 * 一旦发生这种情况，第1个unsigned int 中会留下一个未命名的“洞”。
*/
struct Prcode{
  unsigned int code1 : 1;
  unsigned int code2 : 1;
  unsigned int code3 : 1;
}; // 4字节


int main(void) {
  struct Prcode prcode;
  printf("sizeof prcode: %zd\n", sizeof prcode);
  prcode.code1 = 1;
  prcode.code2 = 0;
  prcode.code3 = 1;
  //prcode 可能二进制结构: 1|xx|0||1
  printf("prcode.code1, prcode.code2, prcode.code3: %d %d %d\n", 
    prcode.code1, prcode.code2, prcode.code3);
  prcode.code2 = 1;
  printf("prcode.code1, prcode.code2, prcode.code3: %d %d %d\n", 
    prcode.code1, prcode.code2, prcode.code3);

  // 测试对齐
  struct {
    unsigned int field1 : 1;
    unsigned int field2 : 1;
    unsigned int field3 : 1;
  } stuff1; // 4字节
  struct {
    unsigned int field1 : 1;
    unsigned int       : 2;
    unsigned int field2 : 1;
    // unsigned int       : 0;
    unsigned int field3 : 1;
  } stuff2; // 4字节
  struct {
    unsigned int field1 : 1;
    unsigned int       : 2;
    unsigned int field2 : 1;
    /**
     * 可以用未命名的字段宽度“填充”未命名的“洞”。
     * 使用一个宽度为0的未命名字段迫使下一个字段与下一个整数对齐
     */
    unsigned int       : 0;
    unsigned int field3 : 1; // stuff3.field将储存在下一个unsigned int中
  } stuff3; // 8字节 - 因为这里使用一个宽度为0的未命名字段，增加了一个unsigned int类型空间
  printf("sizeof stuff1: %zd\nsizeof stuff2: %zd\nsizeof stuff3: %zd\n",
    sizeof stuff1, sizeof stuff2, sizeof stuff3);
  
  return 0;
}