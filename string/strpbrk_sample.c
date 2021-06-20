#include <stdio.h>
#include <string.h>

int main()
{
    char *s = "0123456789012345678901234567890";
    char *p;
    p = strpbrk(s, "a1 839"); /*1會最先在s字符串中找到*/
    printf("%s\n", p);
    p = strpbrk(s, "4398");    /*3 會最先在s 字符串中找到*/
    printf("%s\n", p);
    return 0;
}
