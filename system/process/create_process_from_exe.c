#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork(); // 创建子进程
    if (pid == -1) {
        // 创建子进程失败
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // 子进程
        execl("/usr/bin/hello", "hello", NULL, NULL, NULL);
        // execl() 函数替换当前进程为一个新的程序
        // 第一个参数是程序的路径，第二个参数是程序的名字，后面的参数是传递给程序的参数列表
        perror("execl");
        return 1;
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