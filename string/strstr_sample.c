#include <stdio.h>
#include<string.h>

int main()
{
    char * s = "012345678901234567890123456789";
    char *p;
    p = strstr(s, "901");
    printf("%s\n", p);
    return 0;
}
