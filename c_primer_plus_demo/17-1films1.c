/**
 * @file 17-1.c
 * @brief 假设要编写一个程序，让用户输入一年内看过的所有电影（包括DVD 和蓝光光碟）。
 * 要储存每部影片的各种信息，如片名、发行年份、导演、主演、片长、影片的种类（喜剧、科幻、爱情等）、评级等。
 * 建议使用一个结构储存每部电影，一个数组储存一年内看过的电影。
 * @date 2023-10-09
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define TSIZE 45 /** 存储片名的数组大小 */
#define FMAX 5 /* 影片最大数量 */

struct film
{
  char title[TSIZE];
  int rating;
  /**
   * 虽然结构不能含有与本身类型相同的结构，但是可以含有指向同类型结构的指针。
   * 这种定义是定义链表 （linked list ）的基础，链表中的每一项都包含着在何处能找到下一项的信息。
   */
  struct film * next;
};


int main(void) {
  // struct film movies[FMAX];
  // 使用动态内存分配来表示数据
  struct film * movies; /* 指向结构的指针 */
  int n,result = 0; // 手动输入的数量
  
  puts("Enter the maximum number of movies you'll enter:\n");
  while ((result = scanf("%d", &n)) != 1) {
    while (getchar() != '\n')
      continue;
    puts("Enter the maximum number of movies you'll enter:\n");
  }
  while (getchar() != '\n')
    continue;
  
  movies = (struct film *)malloc(n * sizeof(struct film));

  int i = 0;
  int j;

  puts("Enter first movie title:");

  while (i < n && s_gets(movies[i].title, TSIZE) != NULL &&
    movies[i].title[0] != '\0') {
      puts("Enter your rating <0 - 10>:");
      scanf("%d", &movies[i++].rating);
      while (getchar() != '\n')
        continue;
      puts("Enter next movie title (empty line to stop):");
    }
  if (i == 0)
    printf("No data entered. ");
  else
    printf("Here is the movie list:\n");

  for (j = 0; j < i; j++)
    printf("Movie: %s  Rating: %d\n", movies[j].title,movies[j].rating);
  printf("Bye!\n");

  free(movies);

  return 0;
}