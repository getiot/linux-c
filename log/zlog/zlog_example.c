#include <stdio.h>
#include "zlog.h"

#define LOG_FILE "../zlog.conf"

int main(int argc, char **argv)
{
    int rc;

    zlog_category_t *c;

    rc = zlog_init(LOG_FILE);
    if (rc)
    {
        printf("init failed, please check file %s.\n", LOG_FILE);
        return -1;
    }

    c = zlog_get_category("GetIoT");
    if (!c)
    {
        printf("get cat fail\n");
        zlog_fini();
        return -2;
    }

    zlog_info(c, "hello, zlog");
    zlog_error(c, "hello, zlog");

    zlog_fini();

    return 0;
}
