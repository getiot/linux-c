#include <signal.h>
#include <unistd.h>
#include <stdio.h>

static int flag = 1;

void sigroutine(int dunno)
{ /* 信号处理例程，其中dunno将会得到信号的值 */
    switch (dunno)
    {
    case SIGHUP:
        printf("Get a signal -- SIGHUP\n");  // 1
        break;
    case SIGINT:
        printf("Get a signal -- SIGINT\n");  // 2
        flag = 0;
        break;
    case SIGQUIT:
        printf("Get a signal -- SIGQUIT\n");  // 3
        break;
    case SIGUSR1:
        printf("Get a signal -- SIGUSR1\n");  // 10
        break;
    case SIGUSR2:
        printf("Get a signal -- SIGUSR2\n");  // 12
        break;
    }
    return;
}

int main(void)
{
    printf("process id is %d\n", getpid());

    signal(SIGHUP, sigroutine); //* 下面设置三个信号的处理方法
    signal(SIGINT, sigroutine);
    signal(SIGQUIT, sigroutine);
    signal(SIGUSR1, sigroutine);
    signal(SIGUSR2, sigroutine);

    while (flag) {
        sleep(1);
    }
    
    return 0;
}