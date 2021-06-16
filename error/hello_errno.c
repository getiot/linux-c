#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
 
int main(void)
{
    errno = 0;
    opendir("/tmp/getiot");

    /* 用法1：直接读取errno的值 */
    printf("%d\n", errno);
 
    /* 用法2：使用perror函数，把error的值转化为有意义的字符提示 */
    if(errno != 0){
        perror("opendir: ");
    }
 
    /* 用法3：类似用法2，但使用strerror函数 */
    if(errno != 0){
        printf("%s\n", strerror(errno));
    }
 
    return 0;
}
