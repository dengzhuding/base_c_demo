/**
 * @file 7-1colddays.c
 * @brief 找出0℃以下的天数占总天数的百分比
 * @date 2022-08-19
 * 
 */
#include<stdio.h>

int main(void) {
  const int PREEZING = 0;
  float temperature;
  int cold_days = 0;
  int all_days = 0;

  printf("Enter the list of daily low temperatures.\n");
  printf("Use Celsius, and enter q to quie.\n");

  while (scanf("%f", &temperature) == 1) {
    all_days++;
    if (temperature < PREEZING)
    {
      cold_days++;
    }
  }
  if (all_days == 0) {
    printf("No data entered!\n");
  } else {
    printf("%d days total: %.1f%% were below freezing.\n",
        all_days, 100 * (float)cold_days / all_days); // 乘积会自动转换为浮点型，使用强制转换可以明确表达转换意图
  }

  return 0;
}