#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

int main()
{
    int shmid;
    char *shmaddr;
    char *msg = "Hello, GetIoT.tech!";
    
    // 创建共享内存
    shmid = shmget((key_t)1234, SHM_SIZE, 0666|IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    
    // 连接共享内存
    shmaddr = shmat(shmid, (void *)0, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    
    // 向共享内存写入数据
    strcpy(shmaddr, msg);
    printf("Write: %s\n", shmaddr);
    
    // 分离共享内存
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }
    
    return 0;
}
