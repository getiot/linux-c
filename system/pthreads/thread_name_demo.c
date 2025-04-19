#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *worker(void *arg) {
    char thread_name[16];

    // 设置线程名称
    pthread_setname_np(pthread_self(), "worker-thread");

    // 获取线程名称
    pthread_getname_np(pthread_self(), thread_name, sizeof(thread_name));

    printf("Thread [%ld] running with name: %s\n", pthread_self(), thread_name);

    sleep(2); // 模拟任务处理
    return NULL;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, worker, NULL);

    // 主线程也设置名字
    pthread_setname_np(pthread_self(), "main-thread");

    char name[16];
    pthread_getname_np(pthread_self(), name, sizeof(name));
    printf("Main thread name: %s\n", name);

    pthread_join(tid, NULL);
    return 0;
}