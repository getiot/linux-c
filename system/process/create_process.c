#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/prctl.h>

void myFunction(int loop)
{
    prctl(PR_SET_NAME, "MyChildProcess");

    for (int i=0; i<loop; i++) {
        printf("[%i] This is child process.\n", i);
        sleep(1);
    }
    
    // 执行其他操作
}

int main()
{
    prctl(PR_SET_NAME, "MainProcess");

    pid_t pid = fork(); // 创建子进程
    if (pid == -1) {
        // 创建子进程失败
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 子进程
        prctl(PR_SET_NAME, "MyChildProcess"); // 设置子进程的名字
        myFunction(3); // 调用函数
        return 0;
    } else {
        // 父进程
        int status;
        wait(&status); // 等待子进程退出
        if (WIFEXITED(status)) {
            printf("子进程返回值: %d\n", WEXITSTATUS(status));
        } else {
            printf("子进程异常退出\n");
        }
    }

    return 0;
}