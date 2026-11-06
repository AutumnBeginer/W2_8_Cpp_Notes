#include <stdio.h>

struct Student
{
    int id;
    char name[20];
    float score;
};

int main(void)
{
    struct Student stus[3];
    int n = 3;

    // 用 scanf 录入
    for (int i = 0; i < n; i++)
    {
        printf("录入第%d个学生（id name score）：", i + 1);
        scanf("%d %19s %f", &stus[i].id, stus[i].name, &stus[i].score);
        // 注意：%s 不用 &（数组名即地址），且限宽 19 防溢出
        // scanf("%d %19s %f",stus[i].id,stus[i].name,stus[i].score);
    }
    // 用指针遍历
    printf("\n--- 学生列表 ---\n");
    for (struct Student *p = stus; p < stus + n; p++) // stus + n 是指针加法，结果依然是 Student* 类型（表示数组末尾的地址）。
    {
        printf("id=%-4d name=%-10s score=%.1f\n", p->id, p->name, p->score);
        // printf("id=%-4d name=%-10s score=%.1f\n",p.id,p.name,p.score);//expression must have struct or union type but it has type "struct Student *"
    }
    // 使用整型下标遍历（非指针写法）
    for (int p = 0; p < n; p++)
    {
        // 条件改为 p < n
        printf("id=%-4d name=%-10s score=%.1f", stus[p].id, stus[p].name, stus[p].score);
    }
    return 0;
}