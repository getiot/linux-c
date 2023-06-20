#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 10   // 初始化数组大小
#define INCREMENT 5    // 数组扩展大小

int main()
{
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i=0; i<10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("a[-1] = %d\n", a[-1]);
    printf("a[-2] = %d\n", a[-2]);
    printf("a[-3] = %d\n", a[-3]);
    printf("a[10] = %d\n", a[10]);

    return 0;
}