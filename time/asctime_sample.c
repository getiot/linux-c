#include <stdio.h>
#include <time.h>

int main()
{
    time_t timep;
    time(&timep);
    printf("%s", asctime(gmtime(&timep)));
    return 0;
}
