#include <stdio.h>
#include <string.h>

int main()
{
    char a[30]="Hello, World!";
    char b[]="你好，世界！";
    printf("before strncpy() : %s\n", a);
    printf(" after strncpy() : %s\n", strncpy(a, b, strlen(b)+1));
    /* 注意给'\0'留位置 */
    /* 否则可能出现 warning: ‘strncpy’ output truncated before terminating nul copying */
    return 0;
}
