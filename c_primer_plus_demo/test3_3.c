#include <stdio.h>
int main() {
  int i = 0;
  unsigned int sum = 0;
  for (; i < 16; i ++)
    sum += 1U << i;
  printf("%x", sum);
  return 0;
}