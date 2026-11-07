#include <iostream>
using namespace std;

int main(){
    int a=1;
    int b=2;
    int const *p=&a;
    p=&b;
    //*p=10 //error
    cout<<*p<<endl;

    const int *p1=&a;
    p1=&b;
    //*p1=10 //error
    cout<<*p1<<endl;

    int * const p2=&a;
    *p2=10;
    // p2=&b;//error
    cout<<*p2<<a<<endl;

    const int *const p3=&b;
    // *p3=20;//error
    // p3=&a;//error

    return 0;
}