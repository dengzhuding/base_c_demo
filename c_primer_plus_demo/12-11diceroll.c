/**
 * @file 12-11diceroll.c
 * @author your name (you@domain.com)
 * @brief 投掷筛子（1个），输入边数，然后回车键可投一次
 * @version 0.1
 * @date 2023-06-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>

int rollem (int sides);
static int count = 0; // 投掷次数

int main () {
  int roll;
  int sides;
  int front, status;

  printf("Enter the number of sides per die, 0 to stop: ");
  while (scanf("%u", &sides) == 1 && sides > 0) {
    /* code */
    printf(" Let's begin, 'q' to back\n");
    while ((status = getchar()) != EOF) {
      if (status != '\n') {
        front = status;
        continue;
      }
      if (front == 'q') {
        front = status;
        break;
      }
      roll = rollem(sides);
      printf("your number is : %d ('enter' to continue and 'q' to back) ", roll);
    }
    
    printf("How many sides? Enter 0 to stop: ");
  }
  printf("Bye. The rollem() function was called %d times.\n",
        count);
  return 0;
}

int rollem (int sides) {
  int roll;
  roll = rand() % sides + 1;
  count ++;
  return roll;
}