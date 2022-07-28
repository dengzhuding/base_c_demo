#include<stdio.h>
#include<math.h>

int main(void) {
  double x = sqrt(2.0);
  printf("The square root of 2.0 is %f.\n", x);
  return 0;
}

/*
如果编译的时候报错（目前ubuntn,windows编译都不报错，正常编译）：
$ gcc -Wall calc.c -o calc
/tmp/ccbR6Ojm.o: In function `main':
/tmp/ccbR6Ojm.o(.text+0x19): undefined reference 
  to `sqrt'

需要将 sqrt 函数链接到主程序“calc.c”
gcc -Wall calc.c /usr/lib/libm.a -o calc

或者编译器提供了一个快捷选项“-l”(-lNAME)来链接库（等效于上面使用完整库名称“/usr/lib/libm.a”的原始命令）
gcc -Wall calc.c -lm -o calc

链接器的传统行为是在命令行指定的库中从左到右搜索外部函数
大多数当前链接器将搜索所有库，无论顺序如何，但由于有些不这样做，因此最好遵循从左到右排序库的约定。
gcc -Wall data.c -lglpk -lm // ok - data用到了glpk库中的函数(引用)， glpk库用到了m库的函数

使用警告选项 -Wall 来检测可能很容易被忽略的严重问题
*/