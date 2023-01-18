#include <stdio.h>
#include <time.h>

int main()
{
    time_t seconds = time((time_t*)NULL);
    printf("%lu\n", seconds);
    return 0;
}
