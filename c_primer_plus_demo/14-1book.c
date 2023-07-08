/**
 * @file 14-1book.c
 * @brief 一本书的图书目录
 * @date 2023-07-07
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXTITL 41
#define MAXAUTL 31
#define MAXBKS 100
#define LEN 5

#define EXEC_SUCCESS 0
#define EXEC_FAILURE -1



struct names {
  char first[LEN];
  char last[LEN];
};

/**
 * @brief 结构模板：标记是book
 * 结构声明（structure declaration ）描述了一个结构的组织布局
 * 声明并未创建实际的数据对象，只描述了该对象由什么组成
 * 
 * 从本质上看，book 结构声明创建了一个名为struct book 的新类型
 * 
 * 如果打算多次使用结构模板，就要使用带标记的形式；或者，使用typedef
 * 
 * 使用结构成员运算符——点（. ）访问结构中的成员
 */
struct book
{
  // 成员（member ）或字段（field ），成员可以是任意一种C的数据类型，甚至可以是其他结构
  // 成员顺序有影响，声明后第一个成员起始位置就是结构变量的位置，如&book_item == &book_item.title
  char title[MAXTITL];
  char author[MAXAUTL];
  float price;
  
  // 成员还可以是其他匿名结构
  struct {
    char first[LEN];
    char last[LEN];
  } handle2;
  // 如果不加handle2,可直接用item.first访问匿名结构里面的first
  // (里面的成员相当于平铺到了上一层,实质还是有一个anonymous struct的成员包含)
  struct {
    char first[LEN];
    char last[LEN];
  };
  // 或者使用已经声明的结构,如其中names已经声明
  struct names handle;

};

/**
 * @brief 设置包含空格的字符串
 * 
 * @param str 存入的字符指针
 * @param max_count 最大字符数
 * 限定符：
 * const 指针str指向目标不可改变(目标的值可改变)，max_count值不可改变
 * restrict 表明该指针是访问数据对象的唯一且初始的方式
 */
char * s_gets(char * const restrict str, const int max_count);

/**
 * @brief 分配内存
 * 
 * @param n 数量
 * @return struct book* 
 */
struct book * malloc_book(int n);
/**
 * @brief 打印结构数据，自动添加换行符
 * @param pt 指向book结构的指针
 */
void show_data_book(const struct book * pt);

/**
 * @brief 显示文件内容
 * 
 * @param fp 指向文件的指针
 * @param size 结构大小
 * @return int 返回获取的数据条数
 */
int get_data(FILE *fp, struct book *lib_pt[]);

/**
 * @brief 将结构数据数组存入文件
 * 
 * @param fp 
 * @param library 
 * @return int 
 */
int save_datas(FILE *fp, const struct book item);

/**
 * @brief 根据传入序号查找第n条数据
 * 
 * @param fp 
 * @param num 
 * @return struct book 返回结构
 */
struct book find_data(const FILE *fp, int num);

int main(void) {
  // struct book 所起的作用相当于一般声明中的int 或float
  struct book book_item; /* 把 book_item 声明为一个 book 类型的变量 */
  // struct book book_item = { // 初始化结构变量，与初始化数组的语法类似
  //     "The Pious Pirate and the Devious Damsel",
  //     "Renee Vivotte",
  //     1.95
  // };
  // struct book gift = { //可以按照任意顺序使用指定初始化器
  //   .value = 25.99, 
  //   .author = "James Broadfool",
  //   .title = "Rue for the Toad"};
  // 与数组类似，在指定初始化器后面的普通初始化器，为指定成员后面的成员提供初始值。
  // 另外，对特定成员的最后一次赋值才是它实际获得的值。
  // struct book gift= {.value = 18.90,
  //                  .author = "Philionna Pestle",
  //                  0.25};

  printf("sizeof(book_item): %zd, sizeof(book_item.title): %zd, \
sizeof(book_item.author): %zd, sizeof(book_item.price): %zd\n", 
    sizeof(book_item), sizeof(book_item.title),
    sizeof(book_item.author), sizeof(book_item.price));  // 76 = 41 + 31 + 4
  // sizeof(book); // error
  // sizeof(int); // ok
  // sizeof(struct book); // ok

  struct book book_arr[2] = {
    {
      "t1",
      "a1",
      12.01,
      {},
      {
        "f_n", "l_n"
      }
    },
    {
      .price = 13
    }
  };
  /**
   * @brief 声明结构指针
   * 1. 使用-> 运算符 访问成员(不用能pt.item,因为pt不是结构名)
   * 2. 用*运算符，如(*pt).price 相当于book_arr[0].price (必须要使用圆括号，因为. 运算符比*运算符的优先级高)
   */
  struct book * pt;
  // 和数组不同的是，结构变量名并不是结构的地址，因此要在结构变量名前面加上& 运算符
  pt = &book_arr[0]; /* 告诉编译器该指针指向何处  */
  printf("address #1: %p, #2: %p\n", &book_arr[0], &book_arr[2]);
  printf("pointer #1: %p, #2: %p\n", pt, pt + 1);
  printf("book_arr[0].handle.first: %s, (pt->handle).first: %s, (*pt).price: %.2f",
    book_arr[0].handle.first, (pt->handle).first, (*pt).price);

  /** 声明结构数组 */
  struct book library[MAXBKS]; // library[0].title[1] - 访问数组第1个结构变量中书名的第2个字符

  int i = 0; // 存入的book计数
  printf("please input book info: \n");
  printf("book title:");
  while (i < MAXBKS && s_gets(library[i].title, MAXTITL) != NULL && (*library[i].title) != '\0') {
    printf("book author:");
    s_gets(library[i].author, MAXAUTL);
    printf("book price:");
    while (scanf("%f", &library[i].price) != 1) { // 取了数值，缓冲中至少剩余换行符
      printf("please set price again:");
      while (getchar() != '\n')
        continue;
    }
    // 消耗缓冲数据
    while (getc(stdin) != '\n')
      continue;
    printf("please input the next book info(enter to end): \n");
    i++;
  }

  FILE *fp = fopen("books.dat", "a+b");
  if (fp == NULL)
    exit(EXIT_FAILURE);
  
  char ch;
  // 保持数据到文件
  if (i > 0 && printf("save data to file? ('y' to coniune): ") && (ch = getchar()) == 'y') {
    for (int j = 0, cur_count = i; j < cur_count; j++) {
      save_datas(fp, library[j]);
    }
  }
  while ( i > 0 && ch != '\n' && getchar() != '\n')
    continue;
  
  // 获取文件数据
  if (printf("show data from file? ('y' to coniune): ") && (ch = getchar()) == 'y') {
    // 获取文件大小，分配最大指针内存
    fseek(fp, 0, SEEK_END);
    // 从文件开始处到文件结尾的字节数
    long int max_byte = ftell(fp);
    // 回归文件开头
    fseek(fp, 0, SEEK_SET);

    // rewind(fp); /* 定位到文件开始 */

    const int max_count = (int)(floor(max_byte / sizeof(struct book))); // 向下取整
    struct book *lib_pt[max_count]; // 定义数组，里面成员是指针
    int num = get_data(fp, lib_pt);
    for (int j = 0; j < num; j++) {
      show_data_book(lib_pt[j]);
      // 释放已分配的数据块
      free(lib_pt[j]);
    }
  }
  while (ch != '\n' && getchar() != '\n')
    continue;
  // 关闭文件
  fclose(fp);

  // printf("all book:\n");
  // for (int j = 0; j < i; j++) {
  //   fprintf(stdout, "%s by %s, sell price: $%.2f\n",
  //    library[j].title, library[j].author, library[j].price);
  // }
  


  // printf("book title:");
  // s_gets(book_item.title, MAXTITL);
  // printf("book author:");
  // s_gets(book_item.author, MAXAUTL);
  // printf("book price:");
  // scanf("%f", &book_item.price);

  // printf("book info:\nauthor:%s;\ntitle:%s;\nprice: $%.2f\n", book_item.title, book_item.author, book_item.price);

  return 0;
}

char * s_gets(char * const restrict str, const int max_count) {
  char *ret_val;
  char *find;
  ret_val = fgets(str, max_count, stdin); // 可能会截断输入，作物会放回NULL
  find = strchr(str, '\n');
  if (find == NULL) { // 如果零截断了，处理输入行中剩余的字符
    while (getchar() != '\n')
      continue;
  } else {
    *find = '\0';
  }
  return ret_val;
}
struct book * malloc_book(int n) {
  static int fail_count = 3; // 允许分配失败次数
  if (fail_count <= 0) {
    return NULL;
  }
  struct book * pt;
  pt = (struct book *)malloc((sizeof(struct book)) * n);
  if (pt == NULL) {
    fail_count--;
    return malloc_book(n);
  }
  return pt;
}
void show_data_book(const struct book * pt) {
    fprintf(stdout, "%s by %s, sell price: $%.2f\n",
     pt->title, pt->author, pt->price);
}
int get_data(FILE *fp, struct book *lib_pt[]) {
  struct book *temp_pt;
  int count = 0; // 记录计数
  struct book temp;
  // 使用fread() 和fwrite() 函数读写结构大小的单元
  while (fread(&temp, sizeof(struct book), 1, fp) == 1) { // 一次读取一条
    // 分配内存
    temp_pt = malloc_book(1);
    if (temp_pt == NULL) { // 分配内存失败
      exit(EXIT_FAILURE);
      break;
    }
    memcpy(temp_pt, &temp, sizeof(temp));
    lib_pt[count] = temp_pt;

    count++;
    if (feof(fp)) {
      break;
    }
  }
  return count;
}
int save_datas(FILE *fp, const struct book item) {
  int ret_val = 0;
  // 也可以一次写入一块数据，需要源数据空间大小支持(如把item改为struct book lib[]; size改为count)
  ret_val = fwrite(&item, sizeof(item), 1, fp);
  if (ret_val != 1) {
    exit(EXIT_FAILURE);
  }
  return ret_val;
}