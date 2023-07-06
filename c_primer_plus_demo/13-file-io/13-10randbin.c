/* randbin.c -- 用二进制I/O进行随机访问 */
#include <stdio.h>
#include <stdlib.h>

#define ARSIZE 1000

int main (void) {
  double value;
  double nembers[ARSIZE];
  int i,n;
  char *data_name = "nembers.dat";
  FILE *data_file;

  for (i = 0; i < ARSIZE; i++)
    nembers[i] = 100.0 * i + 1.0/(i + 1);
  
  // 生成数据
  if ((data_file = fopen(data_name, "wb+")) == NULL) {
    printf("Failed to open file %s.", data_name);
    exit(EXIT_FAILURE);
  }
  // 把数据写入文件
  if (fwrite(nembers, sizeof(double), ARSIZE, data_file) != ARSIZE) {
    printf("Failed to write data.");
    exit(EXIT_FAILURE);
  }
  printf("please input the number(between 0 to %d), 'q' to quit:\n", ARSIZE);
  while (scanf("%d", &n) == 1) {
    if (n < 0 || n >= ARSIZE) {
      printf("please input again:\n");
      // 消耗缓冲
      while (getchar()!= '\n')
        continue;
      continue;
    }
    // 移动到目标位置
    fseek(data_file, n * sizeof(double), SEEK_SET);
    // 取出数据放入到value的地址
    fread(&value, sizeof(double), 1, data_file);

    printf("number is %f\n", value);

    // 消耗缓冲
    while (getchar()!= '\n')
      continue;
  }
  // 关闭文件
  if (fclose(data_file) != 0) {
    printf("Failed to  close file %s\n", data_name);
    exit(EXIT_FAILURE);
  }
  return 0;

}