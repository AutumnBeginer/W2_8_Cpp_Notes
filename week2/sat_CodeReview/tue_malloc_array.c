#include <stdio.h>
#include <stdlib.h>

int main(void){
    int size=5;
    int *array=(int *)malloc(size*sizeof(int));

    if(array==NULL){
        printf("数组malloc失败！");
        return 1;
    }

    for (int i=0;i<size;i++){
        *(array+i)=i+1;
    }
    printf("打印数组array:\n");
    for(int j=0;j<size;j++){
        printf("%d ",*(array+j));

    }
    printf("\n");
    // 指针运算：arr+1 跳过一个 int 的距离（4 字节）
    printf("arr = %p, arr+1 = %p, 差值 = %ld 字节\n",
           (void *)array, (void *)(array + 1),
           (char *)(array + 1) - (char *)array);
    free(array);
    array=NULL;
    return 0;
}