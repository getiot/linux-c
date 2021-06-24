#include <stdio.h>
#include <errno.h>
#include <linux/unistd.h>       /* for _syscallX macros/related stuff */
#include <linux/kernel.h>       /* for struct sysinfo */
#include <sys/sysinfo.h>

long get_uptime()
{
    struct sysinfo s_info;
    int error = sysinfo(&s_info);
    if(error != 0)
    {
        printf("code error = %d\n", error);
    }
    return s_info.uptime;
}

int main(void)
{
    long uptime = get_uptime();
    long h = uptime / 3600;
    long m = uptime / 60 % 60;
    long s = uptime % 60;

    printf("uptime: %ld:%ld:%ld\n", h, m, s);
    return 0;
}
