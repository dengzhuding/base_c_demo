/**
 * @file 17-3films3.c
 * @brief 我们的目标是，使用这个接口编写程序，但是不必知道具体的实现细节（如，不知道函数的实现细节）
 * @date 2023-10-21
 * 伪代码方案
    创建一个 List 类型的变量。
    创建一个 Item 类型的变量。
    初始化链表为空。
    当链表未满且有输入时：
    　　 把输入读取到 Item 类型的变量中。
    　　 在链表末尾添加项。
    访问链表中的每个项并显示它们。
 */
#include <stdio.h>
#include "17-3list.h"
#include "common.h"

void showMoviesItem(Item item);

int main(void) {
  List list;
  List * plist = &list;
  InitializeList(plist);

  Item temp;

  /* 获取用户输入并储存 */
  puts("Enter first movie title:");
  while(!ListIsFull(plist) && s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0') {
    puts("Enter your rating <0 - 10>:");
    scanf("%d", &temp.rating);
    while (getchar() != '\n')
      continue;
    // 存入简单链表
    AddItem(temp, plist);
    puts("Enter next movie title (empty line to stop):");
  }
  
  /*显示*/
  Traverse(plist, showMoviesItem);
  /*清理*/
  EmptyTheList(plist);

  printf("Bye!\n");

  return 0;
}

void showMoviesItem(Item item) {
  printf("title: %s, rating: %d\n", item.title, item.rating);
}