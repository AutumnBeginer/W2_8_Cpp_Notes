#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n = 5;
    int *arr = (int *)malloc(n * sizeof(int)); // 分配 5 个 int 的空间

    if (arr == NULL)
    { // ✅ 好习惯：检查 malloc 是否成功
        printf("malloc failed!\n");
        return 1;
    }

    // 用指针遍历赋值
    for (int i = 0; i < n; i++)
    {
        *(arr + i) = (i + 1) * 10; // 等价于 arr[i] = ...
    }

    // 用指针遍历打印
    printf("数组元素: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    // 指针运算：arr+1 跳过一个 int 的距离（4 字节）
    printf("arr = %p, arr+1 = %p, 差值 = %ld 字节\n",
           (void *)arr, (void *)(arr + 1),
           (char *)(arr + 1) - (char *)arr);

    free(arr);  // ✅ 释放内存，避免内存泄漏
    arr = NULL; // ✅ 释放后置空，防止野指针

    return 0;
}