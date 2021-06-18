#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


int main(void)
{
    printf("DataType Size:\n\n");
    printf("     bool = %lu\n", sizeof(bool));
    printf("     char = %lu\n", sizeof(char));
    printf("      int = %lu\n", sizeof(int));
    printf("     long = %lu\n", sizeof(long));
    printf("long long = %lu\n", sizeof(long long));
    printf("    short = %lu\n", sizeof(short));
    printf("    float = %lu\n", sizeof(float));
    printf("   double = %lu\n", sizeof(double));
    printf("\n");
    return 0;
}
