/**
 * @brief C语言把所有类型和函数的信息集合成一个软件包的方法是：
 * 把类型定义和函数原型（包括前提条件和后置条件注释）放在一个头文件中。
 * 该文件应该提供程序员使用该类型所需的所有信息。
 * 
 * ADT好处。
 * 如果程序运行出现问题，可以把问题定位到具体的函数上。
 * 如果想用更好的方法来完成某个任务（如，添加项），只需重写相应的函数即可。
 * 如果需要新功能，可以添加一个新的函数。
 * 如果觉得数组或双向链表更好，可以重写实现的代码，不用修改使用实现的程序
 * 
 */
#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>

/* 特定程序的声明 */
#define TSIZE 45 /**存储片名的数组大小 */
struct film
{
  char title[TSIZE];
  int rating;
};

/* 一般类型定义 */
typedef struct film Item;

typedef struct node { // 在链表的实现中，每一个链节叫作节点 （node ）
  Item item;
  struct node * next;
} Node;

typedef Node * List; // 指向链表开始处的指针
/*另外一种List类型*/
// typedef struct list {
//   Node * head;/* 指向链表头的指针 */
//   int size;/* 链表中的项数 */
// } List2;

/*movies 代表的确切数据应该是接口层次不可见的实现细节*/
// List movies;
// movies = NULL;
// List 类型的结构实现更好，所以应这样初始化
// movies.head = NULL;
// movies.size = 0;

/* 函数原型 */

/* 操作：初始化一个链表            */
/* 前提条件：plist指向一个链表     */
/* 后置条件：该链表初始化为空       */
void InitializeList(List * plist); // 初始化一个链表,这样调用InitializeList(&movies);
bool ListIsEmpty(const List *plist);
bool ListIsFull(const List *plist);
unsigned int ListUtemCount(const List *plist);
bool AddItem(Item item, List * plist);// 在链表的末尾添加项
void Traverse(const List * plist, void(*pfun)(Item item));// 把函数作用于链表中的每一项
void EmptyTheList(List * plist); // 释放已分配的内存（如果有的话） 

#endif
