#include <stdio.h>

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}

int main(){
    int a=1,b=2;
    printf("Before Swap:\n");
    printf("a = %d b = %d\n",a,b);
    printf("a : %p b : %p\n",&a,&b);
    swap(&a,&b);
    printf("After Swap:\n");
    printf("a = %d b = %d\n",a,b);
    printf("a : %p b : %p\n",&a,&b);
    return 0;
}