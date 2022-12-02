#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int nthreads, tid;
// fork a team of thread
#pragma omp parallel private(nthreads, tid)
    {
        // obtian and print thread id
        tid = omp_get_thread_num();
        printf("Hello Word from OMP thread %d\n", tid);

        // only master thread does this;
        if (tid == 0)
        {
            nthreads = omp_get_num_threads();
            printf("Number of thread: %d\n", nthreads);
        }
    }
    return 0;
}