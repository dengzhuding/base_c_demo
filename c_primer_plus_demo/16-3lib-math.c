/**
 * @file 16-3lib.c
 * @brief 数学库
 * @date 2023-07-17
 * 
 */

/**
 * 1. 数学库中包含许多有用的数学函数,math.h 头文件提供这些函数的原型
 *    pi 的值通过计算表达式4*atan(1)
 *    (1弧度=180/π=57.296度)
 *    double ceil(double x) - 返回不小于x 的最小整数值
 *    double floor(double x) - 返回不大于x 的最大整数值
 *    double pow(double x, double y) - 返回x 的y 次幂
 *    double sqrt(double x) 返回x 的平方值
 *    double sin(double x) 返回x 的正弦值，x 的单位为弧度
 *    double asin(double x) 返回正弦值为x 的角度（−π/2～π/2弧度）
 * 
 */
#include <stdio.h>
#include <math.h>

#define PI 3.1415926
// 函数宏
#define PT(x) printf(#x" is %f\n", x)

int main (void) {
  PT(PI);
  PT(4*atan(1));
  PT(1 / sqrt(2));
  PT(sin(PI / 4));
  PT(asin(1 / sqrt(2)) * 57.296); // 45°

  return 0;
}