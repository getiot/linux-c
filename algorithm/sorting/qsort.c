#include <stdio.h>
#include <assert.h>

static void qsort(int* a, const unsigned int size)
{
	assert(a);

	if(size < 2) return;

	int base = a[0];     /* 以序列中的第一个数为基准值 */
	int *i = &a[0];      /* 指针变量i指向第一个 */
	int *j = &a[size-1]; /* 指针变量j指向最后一个 */
	int t;
	static unsigned int round = 0;

	printf("\nRound %u: size=%u, i=%d, j=%d\n", ++round, size, *i, *j);

	while(i != j) {
	
		while(*j >= base && j > i) j--; /* 先从右往左找小于base的数 */
		while(*i <= base && i < j) i++; /* 再从左往右找大于base的数 */

		printf("%d, %d\n", *i, *j);

		if(i < j) {  /* 如果i和j没有重合则交换位置 */

			t = *i; *i = *j; *j = t;  
		}
		else {  /* 如果i和j重合则将基准数归位 */
		
			t = *i; *i = a[0]; a[0] = t;

			int *left = &a[0]; /* 左子序列 */
			int *right = i+1;  /* 右子序列 */

			qsort(left, (i-&a[0]));       /* 递归处理左子序列 */
			qsort(right, (&a[size-1]-i)); /* 递归处理右子序列 */
		}
	}
}

int main(void)
{
	int a[10] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
	int i;
    
	for(i=0; i<10; i++) 
		printf("%d ", a[i]);
	printf("\n");

	qsort(a, 10); /* 快速排序 */

	printf("\n");
	for(i=0; i<10; i++) 
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
