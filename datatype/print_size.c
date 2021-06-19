#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define TEST_STR "getiot.tech"

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
    printf(" TEST_STR = %lu (sizeof %s)\n", sizeof(TEST_STR), TEST_STR);
    printf(" TEST_STR = %lu (strlen %s)\n", strlen(TEST_STR), TEST_STR);
    printf("\n");
    return 0;
}
