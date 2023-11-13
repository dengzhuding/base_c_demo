/**
 * @file yunsuan.c
 * @author dzd
 * @brief 填写运算符：在算式中，添加'+','-','*','/'4个运算符使得等式成立5 5 5 5 5 = 5
 * @date 2023-11-13
  暴力破解法（这里默认输入值为5，无法做到动态数值）
  最终实现：这里第33，34应该是计算5 / 5 / 5为0了，导致结果不准确
  ...
  30: 5 / 5 * 5 - 5 + 5 = 5
  31: 5 / 5 * 5 * 5 / 5 = 5
  32: 5 / 5 * 5 / 5 * 5 = 5
  33: 5 / 5 / 5 * 5 + 5 = 5
  34: 5 / 5 / 5 / 5 + 5 = 5
 * 
 */
#include <stdio.h>
#include <stdlib.h>

// 输入数量
#define LEN 5

// 简单链表，next可为下一条节点或者为NULL
typedef struct SimpleLinked {
  char * str;
  struct SimpleLinked * next;
} Linked;

Linked getResultStr(int nums[], int count, int result);
void printfLinked(Linked * linked);

int main(void) {
  int nums[LEN];
  int count = 0;
  int result;
  int * pnum = &nums[0];
  // 输入运算数值5个
  printf("请输入%d个运算值,用空格隔开(如: 5 5 5 5 5): ", LEN);
  while (count < 5)
  {
    if (scanf("%d", pnum) != 1) {
      printf("请输入数值！\n");
      exit(1);
    }
    count++;
    pnum++;
  }
  
  // 输入结果一个
  printf("请输入运算结果(如: 5): ");
  if (scanf("%d", &result) != 1) {
      printf("请输入数值！\n");
      exit(1);
  }
  // 获取匹配的SimpleLinked解构值
  Linked linked = getResultStr(nums, count, result);
  // 打印
  // printfLinked(&linked);
  return 0;
}
/**
 * @brief Get the Result Str object
 * 
 * @param nums 
 * @param count 
 * @param result 
 * @return STRS 
 */
Linked getResultStr(int nums[], int count, int result) {
  Linked linked;
  linked.next = NULL;
  linked.str = "hello";
  if (count < 2) {
    char str[10];
    linked.str = itoa(nums[0], str, 10);
  }
  char operator[4] = {'+', '-', '*', '/'}; //可加入的运算符
  int len = sizeof(operator);

  char nums_operator[count - 1]; // 保存加入的运算符 如 5 + 5中的'+'
  char nums_operator_copy[count - 1]; // 保存加入的运算符 如 5 + 5中的'+',不会被重置为'0',用于在最终对比成功后取出符号
  int operator_num[count - 1]; // 保存运算过程中间值
  int count_success = 0; // 匹配成功后的编号

  char * p1;
  int count_temp = 0; //统计已经运算过的符号数量
  /** 假设只有5个值如 5 5 5 5 5  = 5 */
  for (int i1 = 0; i1 < len; i1++) {
    nums_operator[0] = nums_operator_copy[0] = operator[i1];
    if (nums_operator[0] == '/' && nums[1] == 0) // 除数为0，跳过这轮
      continue;
    for (int i2 = 0; i2 < len; i2++) {
      nums_operator[1] = nums_operator_copy[1] = operator[i2];
      if (nums_operator[1] == '/' && nums[2] == 0)
        continue;
      for (int i3 = 0; i3 < len; i3++) {
        nums_operator[2] = nums_operator_copy[2] = operator[i3];
        if (nums_operator[2] == '/' && nums[3] == 0)
          continue;
        for (int i4 = 0; i4 < len; i4++) {
          nums_operator[3] = nums_operator_copy[3] = operator[i4];
          if (nums_operator[3] == '/' && nums[4] == 0)
            continue;
          
          // 到这里5个值之间的符号位已经全部填充了，接下来的时计算与结果值比对，如: 5 + 5 * 5 / 5 - 5 ?= 5
          count_temp = 4; //设置初始值
          int leftTotal = 0; // 统计的计算值
          while (count_temp != 0)
          {
            p1 = &nums_operator[0];
            int offset = 0;
            // 优先计算'*','/'符号
            while (*p1 != '*' && *p1 != '/')
            {
              offset++;
              p1++;
              if (offset >= 4) { // 已经比对完，没有*/了
                break;
              }
            }
            if (offset != 4) {
              // 前面如果运算过，就取中间数值代替nums里面的数值
              int left = offset > 0 && nums_operator[offset - 1] == '0' ? operator_num[offset - 1] : nums[offset];
              if (*p1 == '*') {
                operator_num[offset] = left * nums[offset + 1];
              } else {
                operator_num[offset] = left / nums[offset + 1];
              }
              leftTotal = operator_num[offset]; // 最终值
              // 运算符已使用，对应位置设置为'0'
              nums_operator[offset] = '0';
              count_temp--;
              continue;
            }
            // 此时已经就剩+-符号了
            p1 = &nums_operator[0];
            offset = 0;
            while (*p1 != '+' && *p1 != '-')
            {
              offset++;
              p1++;
              if (offset >= 4) { // 已经比对完，没有*/了
                break;
              }
            }
            if (offset != 4) {
              // 前面如果运算过，就取中间数值代替nums里面的数值
              int left = offset > 0 && nums_operator[offset - 1] == '0' ? operator_num[offset - 1] : nums[offset];
              if (*p1 == '+') {
                operator_num[offset] = left + nums[offset + 1];
              } else {
                operator_num[offset] = left - nums[offset + 1];
              }
              leftTotal = operator_num[offset]; // 最终值
              // 运算符已使用，对应位置设置为'0'
              nums_operator[offset] = '0';
              count_temp--;
              continue;
            }
            break;
          }
          // 计算比对正确
          if (leftTotal == result) {
            count_success++;
            printf("%3d: %d %c %d %c %d %c %d %c %d = %d\n",
              count_success,
              nums[0], nums_operator_copy[0],
              nums[1], nums_operator_copy[1],
              nums[2], nums_operator_copy[2],
              nums[3], nums_operator_copy[3], nums[4], result);
          }
        }
      }
    }
  }

  return linked;
}
/**
 * @brief 打印数据
 * 
 * @param linked 
 */
void printfLinked(Linked * linked) {
  Linked * pt_cur = linked;
  while(pt_cur != NULL) {
    fprintf(stdout, linked->str);
    pt_cur = linked->next;
  }
}