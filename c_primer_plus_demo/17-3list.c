/**
 * @file 17-3list.c
 * @brief 支持链表操作的函数
 * @date 2023-10-21
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "17-3list.h"

/**
 * @brief List类型为指向Node类型的指针，List *类型为指向指针的指针 
 * 
 * @param plist 
 */

/* 局部函数原型 */
/*
具有内部链接的函数只能在其声明所在的文件夹可见。在实现接口时，有时编写一个辅助函数（不作为正式接口的一部分）很方便。
由于该函数是实现的一部分，但不是接口的一部分，所以我们使用static 存储类别说明符把它隐藏在list.c 文件中
*/
static void CopyToNode(Item item, Node * pnode);

/* 接口函数   */
void InitializeList(List * plist){
  *plist = NULL;
}
bool ListIsEmpty(const List *plist){ // 把const List * plist 作为形参，表明这些函数不会更改链表
  bool retval = (*plist == NULL) ? true : false;
  return retval;
}
bool ListIsFull(const List *plist){
  Node * pt = (Node *)malloc(sizeof(Node));
  bool full;
  if (pt == NULL) {
    full = true;
  } else {
    full = false;
  }
  free(pt);
  return full;
}
unsigned int ListUtemCount(const List *plist) {
  int count = 0;
  Node * pnode = *plist;
  while (pnode->next != NULL) {
    count++;
    pnode = pnode->next;
  }
  return count;
}
bool AddItem(Item item, List * plist) {
  Node * pnew;
  Node * scan = *plist;
  pnew = (Node *)malloc(sizeof(Node));
  if (pnew == NULL)
    return false;

  /* 把一个项拷贝到节点中 */
  CopyToNode(item, pnew);
  // pnew->item = item;

  /* 设置新节点next为NULL */
  pnew->next = NULL;

  if (scan == NULL)
    *plist = pnew;/* pnew放在链表的开头 */
  else {
    while (scan->next != NULL)
    {
      scan = scan->next;
    }
    scan->next = pnew;/* 把pnew添加到链表的末尾 */
  }
  return true;

}
void Traverse(const List * plist, void(*pfun)(Item item)) {
  Node * pnode = *plist;
  while (pnode != NULL)
  {
    (*pfun)(pnode->item);/* 把函数应用于该项*/
    pnode = pnode->next;
  }

}
void EmptyTheList(List * plist) {
  Node * psave;
  while (*plist != NULL)
  {
    psave = (*plist)->next;
    free(*plist);
    *plist = psave;
  }
}

/* 局部函数定义 */
/* 把一个项拷贝到节点中 */
static void CopyToNode(Item item, Node * pnode)
{
  // 当项是一个数组时，就不能通过赋值来拷贝。
  pnode->item = item;  /* 拷贝结构 */
}