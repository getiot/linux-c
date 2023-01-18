#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    double timestamp = tv.tv_sec + tv.tv_usec / 1000000.0;
    printf("sec: %lu, usec: %lu\n", tv.tv_sec, tv.tv_usec);
    printf("%f\n", timestamp);

    return 0;
}
