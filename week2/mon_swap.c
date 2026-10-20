#include <stdio.h>

void swap_c(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int a = 10, b = 20;
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap_c(&a, &b);/* 必须传地址 */
    printf("After swap: a = %d, b = %d\n", a, b);
    return 0;
}
