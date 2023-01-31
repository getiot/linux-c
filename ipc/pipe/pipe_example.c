/* 父进程借管道将字符串“hello!\n”传给子进程并显示*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    int filedes[2];
    char buffer[80];
    pipe(filedes);
    
    if (fork() > 0) {
        /* 父进程*/
        char s[ ] = "hello!\n";
        write(filedes[1], s, sizeof(s));
    }
    else {
        /*子进程*/
        read(filedes[0], buffer, 80);
        printf("%s", buffer);
    }
    return 0;
}