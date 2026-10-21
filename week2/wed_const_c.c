#include <stdio.h>

int main(void)
{
    int x = 1, y = 2;
    printf("=== 实验1: const int *p ===\n");
    const int *p1 = &x;
    // *p1 = 10;      // 取消注释 → 报错
    p1 = &y; // OK
    printf("x = %d\n", *p1);
    printf("=== 实验2: int *const p ===\n");
    int *const p2 = &x;
    *p2 = 20; // OK
    // p2 = &y;       // 取消注释 → 报错
    printf("x = %d\n", *p2);
}