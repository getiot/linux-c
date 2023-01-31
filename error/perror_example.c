#include <stdio.h>

int main()
{
    FILE *fp;
    fp = fopen("/tmp/noexist", "r+");
    if(fp == NULL) 
        perror("fopen");
    return 0;
}