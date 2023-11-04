/**
 * @file 17-10tree.c
 * @brief 二叉查找数实现 树种不允许有重复的项
 * @date 2023-10-22
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "17-10tree.h"

void showPetItem(Item item);

int main(void) {
  Tree tree;
  Tree * ptree = &tree;
  InitializeTree(ptree);

  Item temp;

  /* 获取用户输入并储存 */
  puts("Enter petname:");
  while(!TreeIsFull(ptree) && s_gets(temp.petname, SLEN) != NULL && temp.petname[0] != '\0') {
    puts("Enter petkind:");
    s_gets(temp.petkind, SLEN);
    // 添加到树
    AddItem(&temp, ptree);
    puts("Enter next petname (empty line to stop):");
  }
  
  /*显示*/
  /*清理*/

  printf("Bye!\n");

  return 0;
}

void showPetItem(Item item) {
  printf("petname: %s, petkind: %s\n", item.petname, item.petkind);
}