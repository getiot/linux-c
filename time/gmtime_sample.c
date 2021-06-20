#include <stdio.h>
#include <time.h>

int main()
{
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    printf("%d-%02d-%02d ", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday);
    printf("%s %02d:%02d:%02d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
    return 0;
}
