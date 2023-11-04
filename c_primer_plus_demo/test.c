#include <stdio.h>
#include <ctype.h>

int main() {
    char str[1001];
    char c;
    int count = 0;
    char * pt = fgets(str, sizeof(str), stdin);
    c = getchar();
    if (isalpha(c)) {
        c = toupper(c);
    }
    while(*pt != '\0') {
        if (isalpha(*pt)) {
            *pt = toupper(*pt);
        }
        if (c == *pt) {
            count++;
        }
        pt++;
    }
    printf("%d", count);
    return 0;
}