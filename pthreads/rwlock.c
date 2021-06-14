/******************************************************************************
* FILE: rwlock.c
* DESCRIPTION: A read-write lock pthreads program.
*              Demonstrates thread lock and unlock R/W.
* AUTHOR: Rudy Lo
* LAST REVISED: 2021-06-14
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define DATA_SIZE    1024
#define REDER_NUM    5
#define WRITER_NUM   2

struct
{
    pthread_rwlock_t rwlock;
    char datas[DATA_SIZE];
} shared = {
    PTHREAD_RWLOCK_INITIALIZER
};

void *reader_thread(void *args)
{
    long tid = (long)args;

    sleep(5);  /* Ensure all writer thread done */

    pthread_rwlock_rdlock(&shared.rwlock);
    printf("Reader[%ld] - Start\n", tid);
    sleep(1);
    printf("Reader[%ld] - Read message is: %s\n", tid, shared.datas);
    pthread_rwlock_unlock(&shared.rwlock);

    return NULL;
}

void *writer_thread(void *args)
{
    char datas[DATA_SIZE];
    long tid = (long)args;

    pthread_rwlock_wrlock(&shared.rwlock);
    printf("Writer[%ld] - Enter the write message: ", tid);
    scanf("%s", datas);
    //fgets(datas, sizeof(datas), stdin);
    strcat(shared.datas, datas);
    pthread_rwlock_unlock(&shared.rwlock);

    return NULL;
}

int main(int argc, char *argv[])
{
    long i;
    pthread_t tid_reader[REDER_NUM], tid_writer[WRITER_NUM];

    pthread_setconcurrency(REDER_NUM + WRITER_NUM);

    for (i = 0; i < WRITER_NUM; ++i) {
        pthread_create(&tid_writer[i], NULL, writer_thread, (void *)i);
    }

    sleep(1);

    for (i = 0; i < REDER_NUM; ++i) {
        pthread_create(&tid_reader[i], NULL, reader_thread, (void *)i);
    }

    for (i = 0; i < WRITER_NUM; ++i) {
        pthread_join(tid_writer[i], NULL);
    }

    for (i = 0; i < REDER_NUM; ++i) {
        pthread_join(tid_reader[i], NULL);
    }

    exit(0);
}
