#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // 1.引用不可重绑
    int a = 1, b = 2;
    int &r = a;
    r = b;
    cout << "a = " << a << " r = " << " b = " << b << endl;
    cout << "&a = " << &a << " &r = " << &r << " &b= " << &b << endl; // a 和 r 同址
                                                                      // 2. 指针可以重绑
    int *p = &a;
    p = &b;                      // 合法
    cout << "*p=" << *p << endl; // 2

    // 3. 引用作参数 vs 指针作参数
    auto printRef = [](int &x)
    { x = 100; };
    auto printPtr = [](int *x)
    { if (x) *x = 200; };
    int v = 0;
    printRef(v);
    cout << "after ref: " << v << endl; // 100
    printPtr(&v);
    cout << "after ptr: " << v << endl; // 200

    // 4. 右值引用初体验
    int &&rr = 10;
    rr = 20;                     // 右值引用本身是个左值变量，可以修改
    cout << "rr=" << rr << endl; // 20

    // 5. string 的移动语义
    string s1 = "hello";
    string s2 = move(s1);
    cout << "s2=" << s2 << " s1=" << s1 << endl; // s2=hello s1=(空)

    return 0;
}