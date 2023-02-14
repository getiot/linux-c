#include <stdio.h>
#include <stdlib.h>

int main()
{
    char template[] = "template-XXXXXX";
    mktemp(template);
    printf("template file: %s\n", template);
    return 0;
}