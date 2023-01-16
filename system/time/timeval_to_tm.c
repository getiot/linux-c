#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    printf("time: %ld\n", timep);
    p = gmtime(&timep);
    printf("%d-%02d-%02d ", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday);
    printf("%s %02d:%02d:%02d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("tv_sec: %ld\n", tv.tv_sec) ;
    printf("tv_usec: %ld\n", tv.tv_usec);

    struct tm *pt;
    pt = gmtime(&tv.tv_sec);
    printf("%d-%02d-%02d ", (1900 + pt->tm_year), (1 + pt->tm_mon), pt->tm_mday);
    printf("%s %02d:%02d:%02d\n", wday[pt->tm_wday], pt->tm_hour, pt->tm_min, pt->tm_sec);

    return 0;
}
