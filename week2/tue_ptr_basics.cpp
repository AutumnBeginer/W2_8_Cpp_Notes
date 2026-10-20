#include <iostream>
using namespace std;

int main()
{
    int a = 10;
    int *p = &a;

    cout << "=== 基本操作 ===" << endl;
    cout << "a 的值: " << a << endl;
    cout << "a 的地址: " << &a << endl;
    cout << "p 存储的地址: " << p << endl;
    cout << "p 指向的值: " << *p << endl;
    cout << "p 自己的地址: " << &p << endl;

    cout << "\n=== 大小对比 ===" << endl;
    cout << "sizeof(int): " << sizeof(int) << endl;
    cout << "sizeof(int*): " << sizeof(int *) << endl;
    cout << "sizeof(double*): " << sizeof(double *) << endl;
    cout << "sizeof(char*): " << sizeof(char *) << endl;
    cout << "sizeof(p): " << sizeof(p) << endl;
    cout << "sizeof(*p): " << sizeof(*p) << endl;

    cout << "\n=== 空指针测试 ===" << endl;
    int *q = nullptr;
    if (q == nullptr)
    {
        cout << "q is nullptr, safe to check" << endl;
    }
    // cout << *q << endl;  // ❌ 取消注释会运行时崩溃

    cout << "\n=== 指针修改 ===" << endl;
    cout << "修改前 a = " << a << endl;
    *p = 100;
    cout << "通过 *p = 100 修改后 a = " << a << endl;

    cout << "\n=== 指针重新指向 ===" << endl;
    int b = 50;
    p = &b; // ✅ 指针可以重新指向
    cout << "p 重新指向 b 后，*p = " << *p << endl;

    return 0;
}