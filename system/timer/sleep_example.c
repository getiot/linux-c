#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

static char msg[] = "I received a msg.";

void show_msg(int signo)
{
    printf("[%lu] %s\n", time(NULL), msg);
}

int main(int argc, char const *argv[])
{
    struct sigaction act;
    union sigval tsval;
    act.sa_handler = show_msg;
    act.sa_flags = 0;
    
    sigemptyset(&act.sa_mask);
    sigaction(50, &act, NULL);

    printf("Start\n");
    
    while (1) {
        sleep(1);

        /*向主进程发送信号，实际上是自己给自己发信号*/
        sigqueue(getpid(), 50, tsval);
    }
    
    return 0;
}