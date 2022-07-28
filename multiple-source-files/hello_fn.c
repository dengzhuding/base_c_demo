#include <stdio.h>
#include "hello.h"
/*
#include "FILE.h" 在查找系统头文件目录之前先在当前目录中搜索'FILE.h'
#include <FILE.h> 搜索系统头文件，但默认不查找当前目录。
*/

void hello(const char * name) {
  printf("Hello %s!\n", name);
}