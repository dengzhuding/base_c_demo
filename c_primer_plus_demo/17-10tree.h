/**
 * @file 17-10tree.h
 * @brief 二叉查找数 树种不允许有重复的项
 * @date 2023-10-21
 * 
 */

/*
关于sizeof(struct)的大小
结构体是一种复合数据类型,通常编译器会自动的进行其成员变量的对齐,已提高数据存取的效率
在默认情况下,编译器为结构体的成员按照自然对齐（natural alignment）条方式分配存储空间,
各个成员按照其声明顺序在存储器中顺序存储
自然对齐是指按照结构体中成员size最大的对齐,在cl编译器下可以使用: #pragma pack(n)来指定结构体的对齐方式

默认对其方式
在默认对齐方式下,结构体成员的内存分配满足下面三个条件
  1.结构体第一个成员的地址和结构体的首地址相同
  2.结构体每个成员地址相对于结构体首地址的偏移量（offset）是该成员大小的整数倍,
    如果不是则编译器会在成员之间添加填充字节（internal adding）
  3.结构体总的大小要是其成员中最大size的整数倍,如果不是编译器会在其末尾添加填充字节（trailing padding）

指定对齐方式
可以使用#pragma pack(N)来指定结构体成员的对齐方式 对于指定的对齐方式,
其成员的地址偏移以及结构的总的大小也有下面三个约束条件
  1.结构体第一个成员的地址和结构体的首地址相同
  2.结构体每个成员的地址偏移需要满足：
    N大于等于该成员的大小,那么该成员的地址偏移需满足默认对齐方式（地址偏移是其成员大小的整数倍）；
    N小于该成员的大小,那么该成员的地址偏移是N的整数倍
  3.结构体总的大小需要时N的整数倍,如果不是需要在结构体的末尾进行填充
  4.如果N大于结构体成员中最大成员的大小,则N不起作用,仍然按照默认方式对齐

说明：
1.在使用#pragma pack设定对齐方式一定要是2的整数幂,也就是（1,2,4,8,16,...）,不然不起作用的,仍然按照默认方式对齐
2.当结构体中有其他的结构体作为成员时,计算最大成员是不能把结构体成员作为一个整体来计算,要看其每个成员的大小
*/
#ifndef _TREE_H_
#define _TREE_H_
#include <stdbool.h>

/* 根据具体情况重新定义 Item */
#define SLEN 20
typedef struct item {
  char petname[SLEN];
  char petkind[SLEN];
} Item;

#define MAXITEMS 10

typedef struct trnode {
  Item item;
  struct trnode *left;
  struct trnode *right;
} Trnode;

typedef struct tree {
  Trnode * root; // 根节点指针
  int size; // 树的项数
} Tree;

/* 函数原型 */

void InitializeTree(Tree * ptree);//把树初始化为空
bool TreeIsEmpty(const Tree * ptree); // 确定树是否为空
bool TreeIsFull(const Tree * ptree); // 确定树是否已满,已满，该函数返回true
int TreeItemCount(const Tree * ptree); // 确定树的项数
bool AddItem(const Item * pi, Tree * ptree); // 在树中添加一个项,pi是待添加项的地址
bool InTree(const Item * pi, Tree * ptree); // 在树中查找一个项,如果在树中找到指定项，该函数返回true
bool DeleteItem(const Item * pi, Tree * ptree); // 从树中删除一个项,如果从树中成功删除一个项，该函数返回true
void Traverse(const Tree * ptree, void(*pfun)(Item item)); // 把函数应用于树中的每一项
void DeleteAll(Tree * ptree); // 删除树中的所有内容




#endif