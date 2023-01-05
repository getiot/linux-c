#include <stdio.h>

/* 计算比特为1的个数 */
int CountBit(int x)
{
    int ret = 0;
    while (x)
    {
        ret++;
        x &= x - 1;
    }
    return ret;
}

int main(void)
{
    int a = 0b00111010;
    printf("%d\n", CountBit(a));
    return 0;
}