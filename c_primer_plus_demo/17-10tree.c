/**
 * @file 17-10tree.c
 * @brief 二叉查找数实现 树种不允许有重复的项
 * @date 2023-10-22
 * 
 */
#include <stdlib.h>
#include <string.h>
#include "17-10tree.h"

/* 局部函数原型 */
static void InitializeTnode(Trnode * ptrnode);
static bool ToLeft(const Trnode * pnewnode, const Trnode * pnode);
static bool CompareItem(const Item * a, const Item * b);
static void SetTreeNode(Trnode * pnewnode, Trnode * pnode);

/* 函数实现 */
void InitializeTree(Tree * ptree) {
  ptree->root = NULL;
  ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree) {
  bool isEmpty;
  isEmpty = (*ptree).root == NULL && (*ptree).size == 0;
  return isEmpty;
}
bool TreeIsFull(const Tree * ptree) {
  Trnode * ptnodetemp = malloc(sizeof(Trnode));
  Tree * ptreetemp = malloc(sizeof(Tree));
  bool isFull = ptnodetemp == NULL || ptreetemp == NULL;
  free(ptnodetemp);
  free(ptreetemp);
  if ((*ptree).size >= MAXITEMS) {
    isFull = true;
  }
  return isFull;
}
int TreeItemCount(const Tree * ptree) {
  return ptree->size;
}
bool AddItem(const Item * pi, Tree * ptree) {
  Trnode * ptnodenew = malloc(sizeof(Trnode));
  Tree * ptreenew = malloc(sizeof(Tree));
  // 初始化新节点，新树
  InitializeTnode(ptnodenew);
  InitializeTree(ptreenew);
  // 挂载item到节点
  ptnodenew->item = *pi; //复制了*pi
  // 挂载tnode到tree
  // ptreenew->root = ptnodenew; // 不需要

  ptree->size++;
  if (TreeIsEmpty(ptree)) { // 空树添加的第一个节点
    // *ptree = *ptreenew;
    ptree->root = ptnodenew;
    return true;
  }

  // 非空树
  free(ptreenew); // 新树可以销毁内存，只需要子节点存在就行
  SetTreeNode(ptnodenew, ptree->root); // 设置子节点

  return true;

}
bool InTree(const Item * pi, Tree * ptree) {
  return true;
}
bool DeleteItem(const Item * pi, Tree * ptree) {
  return true;
}
void Traverse(const Tree * ptree, void(*pfun)(Item item)) {
}
void DeleteAll(Tree * ptree) {
}

/* 局部函数定义 */
static void InitializeTnode(Trnode * ptrnode) { // 初始化节点
  // (*ptrnode).item = NULL;
  ptrnode->left = NULL;
  ptrnode->right = NULL;
}

static bool ToLeft(const Trnode * pnewnode, const Trnode * pnode) { // 确认新节点是否为左子节点
  bool retval;
  const Item * newItem = &(pnewnode->item);
  const Item * curpitem = &(pnode->item);
  retval = CompareItem(newItem, curpitem);
  return retval;
}
/* Item结构改变或比较条件改变可修改此处代码 */
static bool CompareItem(const Item * a, const Item * b) { // a < b 返回true, a >= b 返回false
  bool retval;
  int result = strncmp(a->petname, b->petname, SLEN);
  retval = result < 0;
  return retval;
}
static void SetTreeNode(Trnode * pnewnode, Trnode * pnode) { // 把新子树添加到树中
  bool isLeft = ToLeft(pnewnode, pnode);
  if (pnode->left == NULL && isLeft) { // 添加到左子树
    (*pnode).left = pnewnode;
  }
  else if (pnode->right == NULL && !isLeft) { // 添加到右子树
    (*pnode).right = pnewnode;
  }
  else if (pnode->left != NULL && isLeft) { // 把新子树添加到树中的左节点
    SetTreeNode(pnewnode, pnode->left);
  }
  else if (pnode->right != NULL && !isLeft) {
    SetTreeNode(pnewnode, pnode->right);
  }
}