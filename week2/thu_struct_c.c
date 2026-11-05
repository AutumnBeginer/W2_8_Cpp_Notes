#include <stdio.h>
#include <stdlib.h>

// C 的 struct 没有成员函数，只有数据
struct Student
{
    int id;
    char name[20];
    float score;
};

int main(void)
{
    struct Student s = {1001, "Alice", 92.5f};
    // 普通变量用 . 访问成员
    printf("id =%d,name =%s,score =%.1f\n", s.id, s.name, s.score);
    // 指针用 -> 访问成员
    struct Student *p = &s;
    printf("via pointer -> id =%d\n", p->id);
    p->score = 95.0f; // 通过指针修改
    printf("after modify -> score =%.1f\n", p->score);
    // 动态分配一个 Student
    struct Student *q = (struct Student *)malloc(sizeof(struct Student));
    if (q != NULL)
    {
        q->id = 1002;
        // 字符串拷贝用 strcpy，不要直接 =
        // q->name = "Bob";   // ❌ 数组不能直接赋值
        q->score = 88.0f;
        printf("malloc -> id = %d, score = %.1f\n", q->id, q->score);
        free(q);
    }
    return 0;
}
