#include <stdio.h>
#include "zlog.h"

#define LOG_FILE "../zlog.conf"

int main(int argc, char **argv)
{

    int rc;
    rc = dzlog_init(LOG_FILE, "GetIoT");
    if (rc)
    {
        printf("init failed, please check file %s.\n", LOG_FILE);
        return -1;
    }

    dzlog_info("hello, zlog");
    dzlog_error("hello, zlog");

    zlog_profile();

    zlog_fini();

    return 0;
}
