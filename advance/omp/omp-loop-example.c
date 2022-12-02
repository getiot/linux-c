#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

static void Test(int n)
{
    int i;
    for (i = 0; i < 10000; ++i)
    {
        // do nothing, just waste time
    }
    printf(" %d ", n);
}

int main(int argc, char *argv[])
{
    int i;

    printf("Disable omp\n");
    for (i = 0; i < 10; ++i)
    {
        Test(i);
    }
    
    printf("\n");

    printf("Enable omp\n");
#pragma omp parallel for
    for (i = 0; i < 10; ++i)
    {
        Test(i);
    }
    
    printf("\n");

    return 0;
}