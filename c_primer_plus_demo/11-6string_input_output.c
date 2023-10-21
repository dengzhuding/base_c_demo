/**
 * @file 11-6string_input_output.c
 * @brief 字符串输入输出
 * 
 * 字符串数组和字符串区别： 字符串末尾有空字符(\0)
 * 用双引号括起来的内容是字符串常量，且被视为该字符串的地址
 * 存储字符串的数组名也被看做是地址
 * 
 */
#include<stdio.h>

#define STLEN 6 // 存储5个字符和一个空字符(\0)

char * s_gets(char * st, int n);
void fputs_all(char * st, int n);
char * my_gets_s(char * st, int n);

int main(void) {
  /**
   * @brief 应该避免使用goto语句
   * 这里目的是快速定位到要执行的语句，方便调式
   */
  // goto lastest;

  // 必须分配空间，如果不分配就使用可能会擦写掉程序中的数据或代码，从而导致程序异常终止
  char words[STLEN] = "hello"; // 数组名words时常量
  char * p_words = words; // 指针名p_words时变量，可改变指针地址
  p_words++;
  putchar(*p_words); // 打印第二个字符

  /**
   * 
   * @brief gets() puts()
   * 
   * gets() - 读取整行，直至遇到换行符，然后丢弃换行符，存储其余字符，并在末尾添加一个空字符
   *   (不推荐使用)无法检查数组是否装的下输入行，如果输入太长，会导致缓存区溢出(buffer overflow)，即多余的字符超出了指定的目标空间
   * puts() - 打印字符串，并在末尾补上一个换行符
   *   遇到空字符时就停止输出，所以不能用来输出字符串数组
   * 
   */
  printf("\nuse gets() set words: ");
  gets(words); // 输入超过空间会报错:Segmentation fault - 说明该程序试图访问未分配的内存
  puts(words); // 输出字符串
  printf("gets() end.\n");

  /**
   * @brief fgets() fputs 最佳选择
   * 
   * fgets(str, LIMIT, file) - 通过第二个参数限制读入的字符数
   *   - 遇到换行符，如果空间足够，会存储换行符
   *   - 第三个参数指明要读入的文件(键盘输入用stdin)
   *   - 返回指向char的指针，如果函数读到文件结尾，他将返回一个特殊的指针- 空指针(null pointer)
   *     NULL: 该指针保证不会指向有效的数据，所以可用于标识这种特殊情况
   *   - 只能从文件识别EOF,键盘输入EOF(^D)不行
   * fputs(str, file) - 打印字符串-与printf("%s", str)一致，第二个参数指明它要写入的文件(屏幕输入同stdout)
   *   不会再输出的末尾添加换行符
   * 
   * 空指针（或NULL ）有一个值，该值不会与任何数据的有效地址对应。
   * 通常，函数使用它返回一个有效地址表示某些特殊情况发生，例如遇到文件结尾或未能按预期执行。
   */
  printf("use fgets() set words: ");
  fgets(words, STLEN, stdin); // 输入
  fputs(words, stdout);

  printf("use s_gets() set words: ");
  char * s_gets_ret_val = s_gets(words, STLEN);
  // 空指针(或NULL)有一个值，该值不会与任何有效数据的有效地址对应
  printf("s_gets_ret_val: %p, words: %p, NULL: %p, s_gets_ret_val == NULL: %d\n",
        s_gets_ret_val, words, NULL, s_gets_ret_val == NULL);
  fputs(words, stdout); // 这时候换行符已被替换
  printf("-----here hava not \\n\n");

  printf("Enter string (empty line to quit):\n");
  fputs_all(words, STLEN);

  printf("fgets() end.\n");

  /**
   * @brief gets_s() C11新增
   * 
   * gets_s(* str, LIMIT) - 与fgets()类似，用一个参数限制读入的字符数
   *   - 读到换行符，丢弃换行符
   *   - 读到最大字符数都没有读到换行符：
   *     1. 把目标数组中的首字符设置为空字符(\0)
   *     2. 读取并丢弃随后的输入直至读取到换行符或文件结尾，然后返回空指针
   *     3. 接着调用依赖实现的“处理函数”(或你选择的其他函数)，可能会中止或退出函数
   * 
   * 因为目前GCC中还没有完全实现此标准， 因此 gets_s() 函数尚未包含在目前的GNU 工具链中。
   * Clang里也暂时没有增加对 gets_s 的支持
   * 所以自己实现了一个函数my_gets_s()
   */
  char * gets_s_ret_val;
  do {
    printf("use gets_s() set words( enter more then %d characters to quit): ", STLEN);
    gets_s_ret_val = my_gets_s(words, STLEN);
    printf("gets_s_ret_val: %p, words: %p, NULL: %p, gets_s_ret_val == NULL: %d\n",
          gets_s_ret_val, words, NULL, gets_s_ret_val == NULL);
    puts(words);
  } while (gets_s_ret_val != NULL);
  printf("gets_s() end.\n");

  /**
   * @brief scanf() printf()
   * 使用%s转换说明转换字符单词
   *   - 以下一个空白字符(空行、空格、制表符或换行符)作为字符串的结束(字符串不包括空白字符)
   * 在%s转换或民通过中使用字段宽度(%5s)可防止溢出
   *   - 如%10s,那么scanf()将读取10个字符或读取到第一个空白字符停止
   * printf()的形式比puts()更复杂些，需要输入更多代码，而且计算机执行的事件也更长(但是你察觉不到)
   */

  printf("use scanf() to set words: ");
  // 谨慎使用%s，有溢出风险,应该指定宽度
  scanf("%5s",words); // 返回一个整数，该值等于scanf()成功读取的项数或EOF
  while (getchar() != '\n') // 消耗掉输入行剩余字符
    continue;
  printf("words: %s\n", words);
  printf("scanf() end.\n");

  // lastest:
  // 输入文件结束符终止: windows是CTRL+Z,linux是CTRL+D
  printf("use fputs to printf your enter(enter EOF to quit):\n");
  while (fgets(words, STLEN, stdin) != NULL)
    fputs(words, stdout);
  return 0;
}

/**
 * @brief 读取整行输入并用空字符代替换行符，或者读取一部分输入，并丢弃其余部分
 * 
 * @param st 
 * @param n 
 * @return char* 
 */
char * s_gets(char * st, int n) {
  char * ret_val;
  int i;

  ret_val = fgets(st, n, stdin);
  if (ret_val == NULL) {
    // 如果fgets返回为NULL,说明读到文件结尾或出现读取错误
    return ret_val;
  }
  while (ret_val[i] != '\n' && ret_val[i] != '\0')
    i++;
  if (ret_val[i] == '\n') {
    // 替换换行符
    ret_val[i] = '\0';
  } else {
    // 舍弃输入行其余输入
    while (getchar() != '\n')
      continue;
  }
  return ret_val;
}

/**
 * @brief 完全打印输入行,知道第一个字符为EOF或\n
 * 
 * @param st 
 * @param n 
 */
void fputs_all(char * st, int n) {
  // 按下Return键之前，输入都被存储在临时存储区(缓冲区)，按下Retrurn键就在输入中增加了一个换行符，并把整行输入发送到fgets()
  while (fgets(st, n, stdin) != NULL && st[0] != '\n')
    // 对于输出，fputs()把字符发送给另一个缓冲区，当发送换行符时，缓冲区中的内容被发送至屏幕上
    fputs(st, stdout);
}

/**
 * @brief 比gets安全一点的函数
 * 在C语言中是不能重名的，但是在C++中是可以重名的，C++有函数重载机制，可以解决掉函数重名问题。
 * 
 * @param st 
 * @param n 
 * @return char* 
 */
char * my_gets_s(char * st, int n) {
  char * ret_val;
  ret_val = fgets(st, n, stdin);
  if (ret_val == NULL)
    return ret_val;
  int i = 0;
  while (ret_val[i] != '\n' && ret_val[i] != '\0')
    // i定位到'\n' 或末尾空字符'\0'
    i++;
  if (ret_val[i] == '\n') {
    // 至少少一个存储空间： abc\0\0
    ret_val[i] = '\0';
    return ret_val;
  }
  else {
    /**
     * 读到末尾都没有换行符，有2种可能：
     *   1. 换行符刚好在空字符处被截断 - 输入的字符完全存储了
     *   2. 在换行符前面就被截断了 - 存储不完整
     * 者两种情况无法区分,只能都算存储不完整，然后就全部舍弃了
     */
    while (getchar() != '\n') // 消耗输入行剩余部分
      continue;
    // 重制存储单元为空字符
    ret_val[0] = '\0';
    // NULL指针的值为: 0000000000000000
    return NULL;
  }
}