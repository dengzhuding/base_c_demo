// 导入头文件.h(header)
#include<stdio.h>
#include<math.h>

int main(void) {
  int sqrt_num = sqrt(9);
  int num;
  scanf("%d", &num); // scan format, scanf_s -> scanf safe(仅在vs2019提示警告)
  printf("num = %d", num);
  printf("hello world, %s, %d", "dzd", sqrt_num); // print format

  return 0; // 标识退出码
}

void quck_sort() {
  
}