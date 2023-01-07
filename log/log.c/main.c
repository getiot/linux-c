#include "log.h"

int main(void)
{
    log_set_quiet(false);

    log_trace("Hello GetIoT.tech");
    log_debug("Hello GetIoT.tech");
    log_info("Hello GetIoT.tech");
    log_warn("Hello GetIoT.tech");
    log_error("Hello GetIoT.tech");
    log_fatal("Hello GetIoT.tech");

    return 0;
}