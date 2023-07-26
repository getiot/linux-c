#include <stdio.h>
#include <stdlib.h>

#define ROWS 3  // 二维数组的行数
#define COLS 4  // 二维数组的列数

int main() 
{
    int arr[ROWS * COLS];  // 一维数组
    int (*arr2d)[COLS];      // 二维数组指针

    arr2d = (int (*)[COLS]) arr;  // 将一维数组的地址赋给二维数组指针

    // 通过指针方式访问二维数组的元素，并进行赋值
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            arr2d[i][j] = i * COLS + j;
        }
    }

    // 打印二维数组的元素
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d\t", arr2d[i][j]);
        }
        printf("\n");
    }

    return 0;
}