#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse(char *s)
{
    char *delim = ":";
    char *ipaddr;
    char *port;
    int num;
    char ss[32];

    memcpy(ss, s, strlen(s));

    ipaddr = strtok(ss, delim);
    printf("ip  : %s\n", ipaddr);

    port = strtok(NULL, delim);
    printf("port: %d\n", atoi(port));
}

void parse_r(char *s)
{
    char *save = (char *)malloc(32);
    char *delim = ":";
    char *ipaddr;
    char *port;
    int num;

    ipaddr = strtok_r(s, delim, &save);
    printf("ip  : %s\n", ipaddr);

    port = strtok_r(NULL, delim, &save);
    printf("port: %s\n", port);
}

int main()
{
    char s[] = "192.168.1.100:8080";
    char *delim = ":";
    char *p;

    printf("--------  %s\n", s);
    parse(s);

    char ss[] = "192.168.30.99:5656";
    printf("--------  %s\n", ss);
    parse(ss);

    printf("--------  %s\n", s);
    parse(s);

    return 0;
}
