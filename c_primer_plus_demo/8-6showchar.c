/**
 * @file 8-6showchar.c
 * @brief 按指定的行列打印字符
 * 
 */
#include<stdio.h>

// 声明
void display(char ch, int lines, int width);

int main(void) {
  int ch;
  int rows, cols;

  printf("Enter [ch rows cols]: ");
  while ((ch = getchar()) != '\n') {
    if (scanf("%d %d", &rows, &cols) != 2)
      break;
    display((char)ch, rows, cols);
    // 丢弃scanf()输入后面所有字符(包括换行符)，否则换行符在下一轮迭代会赋值给getchar()直接结束循环
    while (getchar() != '\n')
      continue;
    
    printf("Enter [ch rows cols] or newline to quit: \n");
  }
  
  return 0;
}

// 定义
void display(char ch, int lines, int width) {
  int row, col;
  for (row = 0; row < lines; row++) {
    for (col = 0; col < width; col++)
      putchar(ch);
    putchar('\n');
  }
}