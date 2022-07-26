#include <stdio.h>
#include "zlog.h"

#define LOG_FILE "../zlog.conf"

int main(int argc, char **argv)
{
    int rc;
    zlog_category_t *c;
    char hex_buf[32];

    rc = zlog_init(LOG_FILE);
    if (rc) {
        printf("init failed, please check file %s.\n", LOG_FILE);
        return -1;
    }

    c = zlog_get_category("GetIoT");
    if (!c) {
        printf("get cat fail\n");
        zlog_fini();
        return -2;
    }

    zlog_debug(c, "hello, zlog - debug");
    zlog_info(c, "hello, zlog - info");
    zlog_notice(c, "hello, zlog - notice");
    zlog_warn(c, "hello, zlog - warn");
    zlog_error(c, "hello, zlog - error");
    zlog_fatal(c, "hello, zlog - fatal");

    for (int i = 0; i < sizeof(hex_buf); i++) {
        hex_buf[i] = i;
    }
    hzlog_debug(c, hex_buf, sizeof(hex_buf));

    zlog_fini();

    return 0;
}
