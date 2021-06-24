#include <utmp.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


int main()
{
    struct utmp *u ;
    FILE *fp = fopen("shutdown_note","w+");
    utmpname("/var/log/wtmp");
    while((u = getutent()))
    {
        if(strncmp(u->ut_user,"shutdown",8) == 0)
            fprintf(fp," %s time: %s", u->ut_user, ctime((time_t *)(&u->ut_tv.tv_sec)));
    }

    endutent();

   return 0;

}
