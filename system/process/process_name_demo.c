#include <stdio.h>
#include <string.h>
#include <sys/prctl.h>
#include <unistd.h>

int main() {
    prctl(PR_SET_NAME, "my-process");
    
    char name[16];
    prctl(PR_GET_NAME, name);
    printf("Process name is: %s\n", name);

    sleep(10); // 保持进程运行，方便使用 ps/htop 观察
    return 0;
}