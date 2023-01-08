#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define UNUSED(x) (void)(x)

pid_t gettid(void);

struct t_eventData {
    int myData;
};

static void handler(int sig, siginfo_t *si, void *uc)
{
    UNUSED(sig);
    UNUSED(uc);
    struct t_eventData *data = (struct t_eventData *) si->_sifields._rt.si_sigval.sival_ptr;
    printf("[%lu] Timer fired %d - thread-id: %d\n", time(NULL), ++data->myData, gettid());
}

int main(int argc, char const *argv[])
{
    int res = 0;
    timer_t timerId = 0;

    struct sigevent sev = { 0 };
    struct t_eventData eventData = { .myData = 0 };

    /* specifies the action when receiving a signal */
    struct sigaction sa = { 0 };

    /* specify start delay and interval */
    struct itimerspec its = {
        .it_value.tv_sec  = 1,
        .it_value.tv_nsec = 0,
        .it_interval.tv_sec  = 1,
        .it_interval.tv_nsec = 0
    };

    printf("Signal Interrupt Timer - thread-id: %d\n", gettid());

    sev.sigev_notify = SIGEV_SIGNAL; // Linux-specific
    sev.sigev_signo = SIGRTMIN;
    sev.sigev_value.sival_ptr = &eventData;

    /* create timer */
    res = timer_create(CLOCK_REALTIME, &sev, &timerId);

    if ( res != 0){
        fprintf(stderr, "Error timer_create: %s\n", strerror(errno));
        exit(-1);
    }

    /* specifz signal and handler */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    /* Initialize signal */
    sigemptyset(&sa.sa_mask);

    printf("Establishing handler for signal %d\n", SIGRTMIN);

    /* Register signal handler */
    if (sigaction(SIGRTMIN, &sa, NULL) == -1){
        fprintf(stderr, "Error sigaction: %s\n", strerror(errno));
        exit(-1);
    }

    /* start timer */
    res = timer_settime(timerId, 0, &its, NULL);

    if ( res != 0){
        fprintf(stderr, "Error timer_settime: %s\n", strerror(errno));
        exit(-1);
    }

    printf("Press ENTER to Exit\n");
    while(getchar()!='\n'){}
    return 0;
}
