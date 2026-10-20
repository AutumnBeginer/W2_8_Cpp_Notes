#include <iostream>
using namespace std;

// void swap(int &a,int &b)
// {
//     int temp=a;
//     a=b;
//     b=temp;
// }

// void swap(int a,int b)
// {
//     int temp=a;
//     a=b;
//     b=temp;
// }

// int main()
// {
//     int a=10,b=20;
//     cout<<"Before swap: a="<<a<<" b="<<b<<endl;
//     swap(a,b);
//     cout<<"After swap: a="<<a<<" b="<<b<<endl;
//     return 0;
// }
int main()
{
    int a=10,b=20;
    int &r =a;
    r=b;
    cout<<a<<endl;
    cout<<b<<endl;
    return 0;
}
