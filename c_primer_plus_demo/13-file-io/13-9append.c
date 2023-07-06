/**
 * @file 13-9append.c
 * @brief 该程序把一系列文件中的内容附加在另一个文件的末尾
 *        与13-9append_std.c不同的是，源文件输入为单行输入多个文件名，用空格隔开
 * @date 2023-07-06
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BUFSIZE 4096
#define SLENGTH 81 // 文件名字符串长度

int append_file(FILE *fp_targrt, FILE *fp_sourse);
/**
 * @param argc 执行程序时参数的个数
 * @param argv 执行程序时的参数，argv[0] - 执行路径  argv[n] - 传入的参数
 */
int main (int argc, char **argv) {
  FILE *fp_targrt, *fp_sourse; // 目标文件，源文件指针
  char file_name[SLENGTH], file_sourse_name[SLENGTH];

  printf("please input target file name(less 80 character):");
  if (scanf("%80s", file_name) != 1)
    exit(EXIT_FAILURE);

  if ((fp_targrt = fopen(file_name, "a+b")) == NULL)
    exit(EXIT_FAILURE);

  // 创建4096字节的缓冲区
  char * pt = malloc(BUFSIZE);
  // 指定一个不同的缓冲区大小, 
  // mode:
  // _IOFBF 表示完全缓冲（在缓冲区满时刷新);_IOLBF 表示行缓冲（在缓冲区满时或写入一个换行符时）;_IONBF 表示无缓冲
  setvbuf(fp_targrt, pt, _IOFBF, BUFSIZE);

  printf("please input sourse file to append to %s(split by space):", file_name);
  int status = 0;
  while ((status = scanf("%80s", file_sourse_name)) == 1) {
    if (status == 0)
      continue;
    int min_count = (int)fminf(strlen(file_name), strlen(file_sourse_name));
    if (strncmp(file_name, file_sourse_name, min_count) == 0) {
      printf("same files %s,continue\n", file_name);
      continue;
    }
    // 打开源文件
    if ((fp_sourse = fopen(file_sourse_name, "rb")) == NULL) {
      printf("open file %s fail,continue\n", file_sourse_name);
      continue;
    }
    // 创建了一个供标准I/O函数替换使用的缓冲区
    setvbuf(fp_sourse, pt, _IOLBF, BUFSIZE);
    append_file(fp_targrt, fp_sourse);
    // 关闭源文件
    fclose(fp_sourse);

    // 检查缓冲区是否结束
    char ch;
    ch = getc(stdin);
    if (ch == EOF || ch == '\n') {
      break;
    }
    ungetc(ch, stdin);
  }

  // 打印目标文件
  char ch[100];
  printf("File %s content is--\n", file_name);
  printf("\n...............print the strings..............\n");
  fseek(fp_targrt, 0L, SEEK_SET);  // 指针位移到开始处
  while (!feof(fp_targrt)){
    //takes the first 100 character in the character array
    fgets(ch, 100, fp_targrt);
    //and print the strings
    printf("%s", ch);
  }
  // 释放缓冲区
  free(pt);
  // 关闭文件
  fclose(fp_targrt);

  return 0;
}

/**
 * @brief 把fp_sourse指向的文件内容通过遍历，附加到fp_targrt文件
 * 
 * @param fp_targrt 
 * @param fp_sourse 
 * @return int 
 */
int append_file(FILE *fp_targrt, FILE *fp_sourse) {
  // 数组具有静态存储期（意思是在编译时分配该数组，
  // 不是在每次调用append() 函数时分配）和块作用域（意思是该数组属于它所在的函数私有）
  static char pt[BUFSIZE]; // 确保能容纳最大内容
  int default_len = BUFSIZE;
  // fread()函数返回成功读取项的数量,正常情况下，该返回值就是nmemb ，
  // 但如果出现读取错误或读到文件结尾，该返回值就会比nmemb(第三个参数) 小
  int status_t, status_s;
  while ((status_t = fread(pt, 1, 4096, fp_sourse)) || 1) {
    int w_length;
    w_length = status_t < default_len ? status_t : default_len;
    //fwrite() 函数返回成功写入项的数量。正常情况下，该返回值就是nmemb ，
    // 但如果出现写入错误，返回值会比nmemb 小
    if ((status_s = fwrite(pt, 1, w_length , fp_targrt)) != w_length) {
      printf("write fail and continue...");
    }
    if (feof(fp_sourse))
      break;
  }
  return 0;

}