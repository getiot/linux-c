#include <stdio.h>
#include <string.h>

int main()
{
    char a[] = "string[a]";
    char b[] = "string(b)";
    char *c;
    c = memccpy(a, b, 'b', sizeof(b));
    printf("memccpy(): %s\n", a);
    if (c)
        printf("%s\n", c);
    return 0;
}
