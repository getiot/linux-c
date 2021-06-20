#include <stdio.h>
#include <string.h>

int main()
{
    char s[] = "ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
    char *delim = "-: ";
    char *p;

    printf("%s\n", s);
    printf("%s ", strtok(s, delim));
    while((p = strtok(NULL, delim)))
        printf("%s\n", p);

    return 0;
}
