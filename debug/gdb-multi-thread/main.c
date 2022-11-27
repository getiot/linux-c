#include <stdio.h>
#include <pthread.h>
#include <sys/prctl.h>

static void *thread_job(void *name)
{
    while (1)
    {
        prctl(PR_SET_NAME, name, NULL, NULL, NULL);
        char *thread_name = (char *)name;
        printf("Run %s\n", thread_name);
        printf(">> https://getiot.tech\n");
    }
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, thread_job, "Thread_1 job");
    pthread_create(&tid2, NULL, thread_job, "Thread_2 job");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("Done!\n");
    return 0;
}