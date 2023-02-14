#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 10   // 初始化数组大小
#define INCREMENT 5    // 数组扩展大小

int main()
{
    int *arr;          // 定义指向数组的指针
    int size = 0;      // 数组大小
    int capacity = 0;  // 数组容量
    int i;

    // 初始化数组
    arr = (int *)malloc(INIT_SIZE * sizeof(int));
    if (arr == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(1);
    }
    capacity = INIT_SIZE;

    // 逐个添加元素
    for (i = 0; i < 15; i++) {
        // 如果数组已满，扩展数组
        if (size == capacity) {
            capacity += INCREMENT;
            arr = (int *)realloc(arr, capacity * sizeof(int));
            if (arr == NULL) {
                printf("Error: memory allocation failed.\n");
                exit(1);
            }
        }

        // 添加元素
        arr[size] = i;
        size++;
    }

    // 输出数组元素
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 释放内存
    free(arr);

    return 0;
}
