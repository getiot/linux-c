#include <stdio.h>

#define CURRENT_MIN    0
#define CURRENT_MAX    1
#define VOLTAGE_MIN    2
#define VOLTAGE_MAX    3

void what_is_type(int type)
{ 
    if (type & (1<<1)) {
        printf("%d Is Voltage\n", type);
    } else {
        printf("%d Is Current\n", type);
    }
}

void what_is_position(int type)
{
    if (type & (1<<0)) {
        printf("%d Is Maximal\n", type);
    } else {
        printf("%d Is Minimal\n", type);
    }
}

int main(void)
{
    what_is_type(CURRENT_MIN);
    what_is_type(CURRENT_MAX);
    what_is_type(VOLTAGE_MIN);
    what_is_type(VOLTAGE_MAX);

    what_is_position(CURRENT_MIN);
    what_is_position(CURRENT_MAX);
    what_is_position(VOLTAGE_MIN);
    what_is_position(VOLTAGE_MAX);
    return 0;
}
