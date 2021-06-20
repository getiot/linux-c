#include <stdio.h>
#include <string.h>

int main()
{
    char a[30] = "https://";
    char b[] = "getiot.tech";
    printf("before strnact() : %s\n", a);
    printf(" after strncat() : %s\n", strncat(a, b, strlen(b)+1));
    return 0;
}
