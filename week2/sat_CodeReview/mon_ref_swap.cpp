#include <iostream>
using namespace std;

void swap (int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
}

int main(){
    int a=1,b=2;

    cout<<"Before Swap:"<<endl;
    cout<<"a = "<<a<<" b = "<<b<<endl;
    swap(a,b);
    
    cout<<"After Swap:"<<endl;
    cout<<"a = "<<a<<" b = "<<b<<endl;

    return 0;
}