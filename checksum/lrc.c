#include <stdio.h>

static unsigned char msg[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

static unsigned char LRC(unsigned char *auchMsg, unsigned short usDataLen)
{
    unsigned char uchLRC = 0;
    while (usDataLen--)
        uchLRC += *auchMsg++;
    return ((unsigned char)(-((char)uchLRC)));
}

int main(void)
{
    printf("LRC = %02X\n", LRC(msg, sizeof(msg)));
    return 0;
}
