/**
 * @file 14-3-enum-type.c
 * @brief 可以用枚举类型（enumerated type ）声明符号名称来表示整型常量。
 * 使用enum 关键字，可以创建一个新“类型”并指定它可具有的值
 * （实际上，enum 常量是int 类型，因此，只要能使用int 类型的地方就可以使用枚举类型）。
 * 枚举类型的目的是提高程序的可读性。它的语法与结构的语法相同
 * 
 * 虽然枚举符（如red 和blue ）是int 类型，但是枚举变量可以是任意整数类型，前提是该整数类型可以储存枚举常量。
 * 例如，spectrum 的枚举符范围是0 ～5 ，所以编译器可以用unsigned char 来表示color 变量
 * 
 * 枚举类型的目的是为了提高程序的可读性和可维护性
 * @date 2023-07-10
 */
#include <stdio.h>
#include <time.h>

enum spectrum {
  // 这些符号常量被称为枚举符（enumerator ）
  // 从技术层面看，它们是int 类型的常量,默认情况下，枚举列表中的常量都被赋予0 、1 、2 等
  red, // 0
  orange, // 1
  yellow, // 2
  green,
  blue,
  violet
};

enum feline {
  // 如果只给一个枚举常量赋值，没有对后面的枚举常量赋值，那么后面的常量会被赋予后续的值
  cat, // 0
  lynx = 10, // 10
  puma, // 11
  tiger // 12
};

int main (void) {
  enum spectrum color;
  color = yellow;
  printf("color is: %d\n", color); // 2
  for (color = red; color <= violet; color ++) {
    printf("color number is : %d\n", color);
  }
  time_t t;
  time(&t);
  printf("%lld", t);
  return 0;
}

/**
 * C语言使用名称空间（namespace ）标识程序中的各部分，即通过名称来识别。
 * 作用域是名称空间概念的一部分：两个不同作用域的同名变量不冲突；两个相同作用域的同名变量冲突。
 * 名称空间是分类别的。
 * 在特定作用域中的结构标记、联合标记和枚举标记都共享相同的名称空间，该名称空间与普通变量使用的空间不同。
 * 这意味着在相同作用域中变量和标记的名称可以相同，不会引起冲突，但是不能在相同作用域中声明两个同名标签或同名变量。
 * 例如，在C中，下面的代码不会产生冲突：
 *  struct rect { double x; double y; };
    int rect;    // 在C中不会产生冲突
 * 尽管如此，以两种不同的方式使用相同的标识符会造成混乱。
 * 另外，C++不允许这样做，因为它把标记名和变量名放在相同的名称空间中
 */
