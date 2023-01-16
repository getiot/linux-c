/* 用 time()取得时间（秒数），利用 localtime() 转换成 struct tm 
 * 再利用 mktine() 将 struct tm 转换成原来的秒数
 */
#include <stdio.h>
#include <time.h>

int main()
{
    time_t timep;
    struct tm *p;
    time(&timep);
    printf("time() : %ld \n", timep);
    p = localtime(&timep);
    timep = mktime(p);
    printf("time()->localtime()->mktime() : %ld\n", timep);
    return 0;
}
