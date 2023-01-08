#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

pid_t gettid(void);

struct t_eventData{
    int myData;
};

void expired(union sigval timer_data)
{
    struct t_eventData *data = timer_data.sival_ptr;
    printf("[%lu] Timer fired %d - thread-id: %d\n", time(NULL), ++data->myData, gettid());
}

int main(int argc, char const *argv[])
{
    int res = 0;
    timer_t timerId = 0;

    /*  sigevent specifies behaviour on expiration  */
    struct sigevent sev = { 0 };
    struct t_eventData eventData = { .myData = 0 };

    /* specify start delay and interval
     * it_value and it_interval must not be zero */

    struct itimerspec its = {
        .it_value.tv_sec  = 1,
        .it_value.tv_nsec = 0,
        .it_interval.tv_sec  = 1,
        .it_interval.tv_nsec = 0
    };

    printf("Simple Threading Timer - thread-id: %d\n", gettid());

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function = &expired;
    sev.sigev_value.sival_ptr = &eventData;

    /* create timer */
    res = timer_create(CLOCK_REALTIME, &sev, &timerId);

    if (res != 0) {
        fprintf(stderr, "Error timer_create: %s\n", strerror(errno));
        exit(-1);
    }

    /* start timer */
    res = timer_settime(timerId, 0, &its, NULL);

    if (res != 0) {
        fprintf(stderr, "Error timer_settime: %s\n", strerror(errno));
        exit(-1);
    }

    printf("Press ETNER Key to Exit\n");
    while(getchar()!='\n'){}
    return 0;
}
