/**
 * @file 18-1.c
 * @brief 多线程相关
 * @date 2023-11-03
 * 
 */
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return int 
 */
void * add(void* arg);

struct AddParams {
  int a;
  int b;
};

int main(void) {
  pthread_t th;
  struct AddParams addparam;
  addparam.a = 1;
  addparam.b = 2;
  int res;
  res = pthread_create(&th, NULL, &add, &addparam);
  if (res != 0) {
    return 0;
  }
  void * thread_result;
  res = pthread_join(th, &thread_result);
  if (res != 0) {
    return 0;
  }
  char * p_str = (char *)thread_result;
  printf("%s", p_str);
  return 0;
}

void * add(void* arg) {
  printf("i am here.");
  return "hello world.";
}