#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/**
 * @brief 阶乘
 * 
 * @param s_num 数字字符串，范围[1~100]
 * @return char* 
 */
char * factorial(char * s_num); // 
/**
 * @brief 乘法
 * 
 * @param a 字符串a-"12\0"
 * @param b 字符串a-"12\0"
 * @return char* 
 */
char * steMult(char * a, char * b);
/**
 * @brief 加法
 * 
 * @param a 字符串a-"12\0"
 * @param b 字符串a-"12\0"
 * @param len_a 字符串a长度-2
 * @param len_b 字符串b长度-3
 * @return char* 
 */
char * steAddition(char * a, char * b, int len_a, int len_b); 
/**
 * @brief 用指针交换位置
 * 
 * @param a 
 * @param b 
 */
void swap(char *a, char *b);

int main (int argc, char * argv[]) {
    if (argc == 1) {
        printf("请传入1个数字参数！(如：factorial.exe 100)");
        exit(0);
    }
    char * p_num = argv[1];
    while (*p_num != '\0')
    {
        if (!isdigit(*p_num)) {
            fprintf(stdout, "请输入数字字符参数！");
            exit(EXIT_SUCCESS);
        };
        p_num++;
    }
    char * p_result = factorial(argv[1]);
    fprintf(stdout, p_result);
    return 0;
}

char * factorial(char * s_num) {
    int num = atoi(s_num); // 假设输入计算阶乘的起始值为1~100，用int存储够了，关键在于计算过程中的数值如何存储
    if (num > 100 || num < 1) {
        fprintf(stdout, "计算值范围为[1~100]");
        exit(EXIT_SUCCESS);
    }
    if (num == 1) {
        return "1";
    }
    char * s_temp_product = "1";
    char * s_cur = (char *)malloc(sizeof(char) * 3 + 1); // 100\0 4个字符
    *(s_cur+3) = '\n';
    for (int i = num; i > 1; i--) {
        // 相乘
        itoa(i, s_cur, 10);
        s_temp_product = steMult(s_temp_product, s_cur); // 返回相乘后的字符串指针
    }
    return s_temp_product;
}

char * steMult(char * a, char * b) { // 相乘
    static char * s_zero = "0";
    static char * s_one = "1";
    char * s_rtn = (char *)realloc(NULL, sizeof(char) * 200); // 先分配200个字符，不够再扩容
    /**
     * @brief 特殊情况
     * 
     */
    if (!a || !b || a == NULL || b == NULL) {
        return "0";
    }
    if (strcmp(a, s_zero) == 0 || strcmp(b, s_zero) == 0) {
        return "0";
    }
    if (strcmp(a, s_one) == 0) {
        return strcpy(s_rtn, b);
    }
    if (strcmp(b, s_one) == 0) {
        return strcpy(s_rtn, a);
    }

    /**
     * @brief 
     * 
     */
    register char * p_digit = b;
    int len_b = 0; // b的长度，"120\0"就是3
    while (*p_digit != '\0') // 指向b的个位数的指针
    {
        len_b++;
        p_digit++;
    }
    p_digit--;

    register char * p_digit_a = a; // 指向a的个位数的指针
    int len_a = 0; // a的长度，"120\0"就是3
    while (*p_digit_a != '\0')
    {
        len_a++;
        p_digit_a++;
    }
    p_digit_a--;

    // 但前乘积的和
    char * s_sum = "0";

    // b为个位数
    if (len_b == 1) { //个位数的相乘转为加法
        short i = atoi(p_digit); // i最大为9
        for(; i > 0; i--) {
            char a_cpy[len_a+1];
            strcpy(a_cpy, a);
            int len_temp_a = 0;
            char * p_temp_a = s_sum;
            while (*p_temp_a != '\0')
            {
                len_temp_a++;
                p_temp_a++;
            }
            
            s_sum = steAddition(s_sum, a_cpy, len_temp_a, len_a); // 相加 i次
        }
        return s_sum;
    }
    // b为多位数
    while (p_digit - b >= 0) { // 高位相乘转为个位相乘
        char b_cpy[2];
        b_cpy[0] = (char)*p_digit;
        b_cpy[1] = '\0';
        if (p_digit - b < len_b - 1) {
            char a_cpy[len_a+2];
            strcpy(a_cpy, a);
            a_cpy[len_a] = '0';
            a_cpy[len_a+1] = '\0';
            char * s_temp = steMult(a_cpy, b_cpy);
            s_sum = steAddition(s_sum, s_temp , len_a, len_b); // 乘积后加到总值上
        } else {
            char * s_temp_2 = steMult(a, b_cpy);
            s_sum = steAddition(s_sum, s_temp_2, len_a, len_b); // 乘积后加到总值上
        }
        p_digit--;
    }
    return s_sum;
}
char * steAddition(char * a, char * b, int len_a, int len_b) { // 相加
    static char * s_zero = "0";
    char * s_rtn = (char *)realloc(NULL, sizeof(char) * 200); // 先分配200个字符，不够再扩容
    /**
     * @brief 特殊情况
     * 
     */
    if (!a || a == NULL || strcmp(a, s_zero) == 0) {
        if (len_b > 199) {
            s_rtn = realloc(s_rtn, len_b + 1);
        }
        strcpy(s_rtn, b);
        return s_rtn;
    }
    if (!b || b == NULL || strcmp(b, s_zero) == 0) {
        if (len_a > 199) {
            s_rtn = realloc(s_rtn, len_a + 1);
        }
        strcpy(s_rtn, a);
        return s_rtn;
    }
    /**
     * @brief 指向a末尾的数字字符
     * 
     */
    register char * p_a = a + len_a - 1;
    /**
     * @brief 指向b末尾的数字字符
     * 
     */
    register char * p_b = b + len_b - 1;
    if (len_a > 199 || len_b > 199) {
        s_rtn = realloc(s_rtn, len_a > len_b ? len_a  + 10 : len_b  + 10); // 位置不够，加上10位
    }

    short up = 0;
    char * p_rtn = s_rtn;
    int size_rtn = 0;
    while (p_a - a >= 0 || p_b - b >= 0)
    {
        char i_a = p_a - a < 0 ? 0 : *p_a - '0';
        char i_b = p_b - b < 0 ? 0 : *p_b - '0';
        short temp = i_a + i_b + up;
        if (temp > 9) {
            up = 1;
            temp -= 10;
        } else {
            up = 0;
        }
        p_a--;
        p_b--;
        *p_rtn = temp + '0';
        size_rtn++;
        p_rtn++;
    }
    *p_rtn = '\0';

    // 反转字符串才是正确返回数值字符串
    for (int i = 0; i < size_rtn / 2; i++) {
        swap(s_rtn + i, s_rtn + size_rtn - i -1);
    }
    // while (*s_rtn == '0') // 去掉前缀0
    // {
    //     s_rtn++;
    //     if (*s_rtn == '\0') { // 保证有0
    //         s_rtn--;
    //         break;
    //     }
    //     /* code */
    // }
    
    return s_rtn;
}
void swap(char *a, char *b) {
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}