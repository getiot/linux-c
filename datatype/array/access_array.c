#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int32_t ARRAY_MIN = -3;
static int32_t ARRAY_MAX = 10;

int main()
{
    int a[ARRAY_MAX - ARRAY_MIN];
    int *a_ = a - ARRAY_MIN;

    /* Fill data */
    for (int i=0; i<ARRAY_MAX-ARRAY_MIN; i++) {
        a[i] = ARRAY_MIN + i;
    }

    /* Print data */
    printf("Array: ");
    for (int i=0; i<ARRAY_MAX-ARRAY_MIN; i++) {
        printf("%d ", a[i]);
    }
    printf("\n\n");

    printf("a[-1] = %d\n", a[-1]);
    printf("a[-2] = %d\n", a[-2]);
    printf("a[-3] = %d\n", a[-3]);
    printf("a[10] = %d\n\n", a[10]);

    printf("a_[-1] = %d\n", a_[-1]);
    printf("a_[-2] = %d\n", a_[-2]);
    printf("a_[-3] = %d\n", a_[-3]);
    printf("a_[10] = %d\n", a_[10]);

    return 0;
}