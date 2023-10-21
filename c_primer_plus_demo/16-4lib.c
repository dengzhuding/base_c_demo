/**
 * @file 16-4lib.c
 * @brief 通用工具库
 * @date 2023-07-17
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * assert.h 头文件支持的断言库是一个用于辅助调试程序的小型库
 * 它由assert() 宏组成，接受一个整型表达式作为参数。如果表达式求值为假（非零），assert() 宏
 * 就在标准错误流（stderr ）中写入一条错误信息，并调用abort() 函数终止程序（abort() 函数的原型在stdlib.h 头文件中）
 * 
 */
// 如果认为已经排除了程序的bug，就可以把下面的宏定义写在包含assert.h 的位置前面
// 并重新编译程序，这样编译器就会禁用文件中的所有assert() 语句
// #define DEBUGE
#include <assert.h>
#include <limits.h>

// C11新增了一个特性：_Static_assert 声明，可以在编译时检查assert() 表达式
// _Static_assert() 接受两个参数。第1个参数是整型常量表达式，第2个参数是一个字符串。
// 如果第1个表达式求值为0 （或_False ），编译器会显示字符串，而且不编译该程序
// _Static_assert(CHAR_BIT == 16, "16-bit char falsely assumed");



void sign_off(void);
void too_bad(void);

void show_arr(char *name, const int *pt, const int len);
int compar(const void *, const void *);
void test_exit(void);

int main(void)
{
  // test_exit();

  /**
   * @brief 快速排序函数
   * 
   * void qsort(void *_Base, size_t _NumOfElements, size_t _SizeOfElements, 
   * int (*_PtFuncCompare)(const void *, const void *))
   * 第1个参数是指针，指向待排序数组的首元素
   * 第2个参数是待排序项的数量。函数原型把该值转换为size_t 类型
   * 第3个参数显式指明待排序数组中每个元素的大小
   * 第4个参数为一个指向函数的指针，这个被指针指向的比较函数用于确定排序的顺序。 
   *     该函数应接受两个参数：分别指向待比较两项的指针。
   *     如果第1项的值大于第2项，比较函数则返回正数；如果两项相同，则返回0 ；如果第1项的值小于第2项，则返回负数
   */
  int arr[] = {
    2,3,54,67,3,5,52,6,3,7,87,9,22
  };
  const int SIZE = sizeof(int);
  const int LEN = sizeof(arr) / sizeof(int);
  
  int arr_sort[LEN];
  // 物理复制内存数据
  memcpy(arr_sort, arr, sizeof(arr_sort));
  
  show_arr("arr", arr, LEN);

  int (*my_compar)(const void *, const void *);
  my_compar = compar;
  qsort(arr_sort, LEN, SIZE, my_compar);
  show_arr("arr_sort", arr_sort, LEN);

  // assert(1 > 2); // Assertion failed: 1 > 2, file D:\learning\c\base_c_demo\c_primer_plus_demo\16-4lib.c, line 56
  // assert(1+2 == 3);
  // assert(0.1+0.2 == 0.3); // Assertion failed
  return 0;
}

void test_exit(void) {
    int n;
    /**
    int atexit(void (*)(void)) 函数通过退出时注册被调用的函数提供这种功能(指定在执行exit() 时调用的特定函数)，
    atexit() 函数接受一个函数指针作为参数
    ANSI保证，在这个列表中至少可以放32个函数。最后调用exit() 函数时，
    exit() 会执行这些函数（执行顺序与列表中的函数顺序相反，即最后添加的函数最先执行）。
    atexit() 注册的函数（如sign_off() 和too_bad() ）应该不带任何参数且返回类型为void 。
    通常，这些函数会执行一些清理任务，例如更新监视程序的文件或重置环境变量。
    注意，即使没有显式调用exit() ，还是会调用sign_off() ，因为main() 结束时会隐式调用exit() 
    */
    atexit(sign_off);        /* 注册 sign_off()函数 */
    puts("Enter an integer:");
    if (scanf("%d", &n) != 1)
    {
        puts("That's no integer!");
        atexit(too_bad);     /* 注册 too_bad()函数 */
        /**
         * exit() 执行完atexit() 指定的函数后，会完成一些清理工作：
         * 刷新所有输出流、关闭所有打开的流和关闭由标准I/O函数tmpfile() 创建的临时文件。
         * 然后exit() 把控制权返回主机环境，如果可能的话，向主机环境报告终止状态。
         * 通常，UNIX程序使用0 表示成功终止，用非零值表示终止失败。
         * UNIX返回的代码并不适用于所有的系统，所以ANSI C为了可移植性的要求，定义了一个名为EXIT_FAILURE 的宏表示终止失败。
         * 类似地，ANSI C还定义了EXIT_SUCCESS 表示成功终止。
         * 不过，exit() 函数也接受0 表示成功终止。在ANSI C中，在非递归的main() 中使用exit() 函数等价于使用关键字return 。
         * 尽管如此，在main() 以外的函数中使用exit() 也会终止整个程序。
         */
        exit(EXIT_FAILURE);
    }
    printf("%d is %s.\n", n, (n % 2 == 0) ? "even" : "odd");
}

void sign_off(void)
{
    puts("Thus terminates another magnificent program from");
    puts("SeeSaw Software!");
}

void too_bad(void)
{
    puts("SeeSaw Software extends its heartfelt condolences");
    puts("to you upon the failure of your program.");
}

void show_arr(char *name, const int *pt, const int len) {
  printf("show array %s:\n", name);
  int n = 0;
  while (n < len) {
    printf("%5d", *(pt + n));
    n++;
    if (n % 5 == 0)
      putchar('\n');
  }
  putchar('\n');
}

int compar(const void *p1, const void *p2) {
  /* 要使用指向int的指针来访问这两个值 */
  const int *a1 = (const int *)p1;
  const int *a2 = (const int *)p2;
  if (*a1 < *a2)
    return -1;
  else if (*a1 == *a2)
    return 0;
  else 
    return 1;
}
