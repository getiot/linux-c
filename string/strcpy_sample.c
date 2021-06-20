#include <stdio.h>
#include <string.h>

int main()
{
    char a[30]="Hello, World!";
    char b[]="你好，世界！";
    printf("before strcpy() : %s\n", a);
    printf(" after strcpy() : %s\n", strcpy(a, b));
    return 0;
}
