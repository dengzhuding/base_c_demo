#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 9

struct P{
    short i;
    short j;
    struct P * next;
    struct P * pre;
};
typedef struct P Point;

// 还没有输入的数字
bool cannotFInd(Point * ppoint, int num, short (*arr)[MAX]) {
    bool res = true;
    int i = ppoint->i;
    int j = ppoint->j;
    // 行
    for (int k=0; k < MAX ; k++) {
        if (arr[i][k] == num) {
            return false;
        }
    }
    // 列
    for (int g=0; g < MAX ; g++) {
        if (arr[g][j] == num) {
            return false;
        }
    }
    double di = i / 3;
    double dj = j / 3;
    int starti = di >= 2 ? 6 : (di >= 1 ? 3 : 0);
    int endi = starti + 3;
    int startj = dj >= 2 ? 6 : (dj >= 1 ? 3 : 0);
    int endj = startj + 3;
    for (int k1 = starti; k1 < endi; k1++) {
        for (int k2 = startj; k2 < endj; k2++) {
            if (arr[k1][k2] == num) {
                return false;
            }
        }
    }
    // 列
    // 3x3 宫格
    return res;
}

bool calc(Point * ptpoint, short (*arr)[MAX], bool canChoose) {
  short temp = 0;
  int count = 0;
    for (short i = 1; i <= 9; i++) {
        if (cannotFInd(ptpoint, i, arr)) {
            count++;
            temp = i;
        }
    }
  if (count == 1 || (canChoose && count > 1)) {
    // printf("i:%d j:%d value:%d \n", ptpoint->i, ptpoint->j, temp);
    // if (ptpoint->i==6 && ptpoint->j == 5) {
    //   printf("stop here.....");
    // }
    arr[ptpoint->i][ptpoint->j] = temp;
    // short * target = &(arr[ptpoint->i][ptpoint->j]);
    // *target = temp;
    count = 0;
    temp = 0;
    return true;
  }
  return false;
}

int main() {
    Point * ptpoint;
    Point * ptcurpoint;
    ptpoint = NULL;
    short arr[MAX][MAX];
    
    int zerozount = 0;
    int inputcount = 0;
    int i = 0, j = 0;
    // 输入
    while (scanf("%hd", &arr[i][j]) == 1) {
        inputcount++;

        if (arr[i][j] == 0) {
            Point * ppoint = (Point *)malloc(sizeof(Point));
            ppoint->i = i;
            ppoint->j = j;
            ppoint->next = NULL;
            ppoint->pre = NULL;
            if (zerozount == 0) {
                ptpoint = ppoint;
                ptcurpoint = ppoint;
            } else {
                ptcurpoint->next = ppoint;
                ppoint->pre = ptcurpoint;
                ptcurpoint = ppoint;
            }

            zerozount++;
        }
        if (i == 8 && j == 8) {
            break;
        }
        j++;
        if (j >= MAX) {
            i++;
            j = j % MAX;
        }
    }
    if (inputcount < MAX * MAX) {
        printf("sorry, input data error!");
        exit(0);
    }
    // 处理
    ptcurpoint->next = ptpoint;
    ptpoint->pre = ptcurpoint; // 首位相连

    
    Point * pttemp = ptpoint;
    ptcurpoint = ptpoint;
    // 计算是否够一个周期循环
    int stateCode = zerozount;
    while (pttemp != NULL) {
        // 如果到一个循环结束还没有找到仅剩一个选择的节点，就随机取出一个
        if (calc(pttemp, arr, stateCode == 0)) {
          // 一处链表点
          pttemp->next->pre = pttemp->pre;
          pttemp->pre->next = pttemp->next;
          zerozount--;
          // 找到点了接刷新循环圈stateCode
          stateCode = zerozount;
        } else {
          stateCode--;
        };
        pttemp = pttemp->next;
        if (zerozount == 0) {
          break;
        }
    }

    int k = 0;
    short * pt = &arr[0][0];
    // 输出
    while (k < MAX * MAX) {
        printf("%hd ", *pt);
        k++;
        if (k % MAX == 0) {
            printf("\n");
        }
        pt++;
    }
    return 0;
}