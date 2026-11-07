#include <stdio.h>
#include <stdlib.h>

struct Student{
    int id;
    char name[20];
    int score;
};


// 比较函数：按成绩从高到低
int cmp(const void *a, const void *b) {
    float fa = ((const struct Student *)a)->score;
    float fb = ((const struct Student *)b)->score;
    if (fa < fb) return 1;    // 降序
    if (fa > fb) return -1;
    return 0;
}


int main(void){
    int total=0;
    printf("请输入学生人数：\n");
    scanf("%d",&total);
    struct Student*array=(struct Student*)malloc(total*sizeof(struct Student));
    if (array==NULL){printf("malloc failed\n"); return 1;}
    printf("下面开始录入学生成绩：\n");
    printf(" id | name | score\n");
    for(int i=0;i<total;i++){
        scanf("%d %19s %d",&array[i].id,array[i].name,&array[i].score);
    }

    qsort(array,total,sizeof(struct Student),cmp);
    
    printf("按分数由高到低排序后输出名单如下：\n");
    printf(" id | name | score\n");
    for(int i=0;i<total;i++){
        printf("%-5d %-5s %d\n",array[i].id,array[i].name,array[i].score);
    }
    free(array);
    array=NULL;
    return 0;
}