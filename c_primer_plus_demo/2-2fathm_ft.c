// fathm_ft.c --转换2英尺-》英尺
#include<stdio.h>

void butler(void); // 函数原型(也叫函数声明)-prototype|function declaration  c90新增

int main(void) 
{
	int feet, fathoms;

	fathoms = 2;
	feet = 6 * fathoms;
	printf("fathoms:%d  feet:%d\n", fathoms, feet);
	butler(); // 函数调用-function call
	printf("feet is %d\n", 6 * fathoms);

	return 0;
}

void butler(void) // 函数定义
{
	printf("here is called by the second function 'butler'.\n");
}
