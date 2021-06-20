#include <stdio.h>
#include <string.h>

int main()
{
    char *s = "0123456789012345678901234567890";
    char *p;
    p = index(s, '5');
    printf("%s\n", p);
    return 0;
}
