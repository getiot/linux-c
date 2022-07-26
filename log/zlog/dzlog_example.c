#include <stdio.h>
#include "zlog.h"

#define LOG_FILE "../zlog.conf"

int main(int argc, char **argv)
{
    int rc;
    char hex_buf[32];

    rc = dzlog_init(LOG_FILE, "GetIoT");
    if (rc) {
        printf("init failed, please check file %s.\n", LOG_FILE);
        return -1;
    }

    dzlog_debug("hello, zlog - debug");
    dzlog_info("hello, zlog - info");
    dzlog_notice("hello, zlog - notice");
    dzlog_warn("hello, zlog - warn");
    dzlog_error("hello, zlog - error");
    dzlog_fatal("hello, zlog - fatal");

    for (int i = 0; i < sizeof(hex_buf); i++) {
        hex_buf[i] = i;
    }
    hdzlog_debug(hex_buf, sizeof(hex_buf));

    //zlog_profile();

    zlog_fini();

    return 0;
}
