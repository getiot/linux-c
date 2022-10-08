#include <stdio.h>

static int debug = 1;  /* enable this to printf */

#define DEBUG_PRINT(fmt, args...) \
    do { if(debug) \
    printf(fmt, ## args); \
    } while(0)

int main(void)
{
    DEBUG_PRINT("Hello, World!\n");
    return 0;
}