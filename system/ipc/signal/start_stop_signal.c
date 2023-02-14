#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

static bool working = false;

void start_work(int signum)
{
    printf("Signal - start\n");
    working = true;
}

void stop_work(int signum)
{
    printf("Signal - stop\n");
    working = false;
}

void signal_handler(int signum)
{
    printf("Signal %d caught\n", signum);
}

void * task(void *args)
{
    signal(SIGUSR1, start_work);
    signal(SIGUSR2, stop_work);
    // signal(SIGCONT, signal_handler);
    //signal(SIGINT, signal_handler);

    // pause();
    while (1) {
        if (working) break;
        sleep(1);
    }

    printf("Start job ...\n");

    while (working)
    {
        printf("  doing ...\n");
        sleep(1);
    }

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t tid;
    void *status;

    printf("process id is %d\n", getpid());
    pthread_create(&tid, NULL, task, NULL);

    sleep(1);
    raise(SIGUSR1);
    sleep(3);
    raise(SIGUSR2);

    pthread_join(tid, &status);

    return 0;
}