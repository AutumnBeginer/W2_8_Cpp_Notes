#include <iostream>
using namespace std;

int main() {
    int x = 1, y = 2;

    cout << "=== 实验1: const int *p ===" << endl;
    const int *p1 = &x;
    //  *p1 = 10;      // 取消注释 → 报错
    p1 = &y;          // OK
    cout << "*p1 = " << *p1 << endl;

    cout << "\n=== 实验2: int *const p ===" << endl;
    int *const p2 = &x;
    *p2 = 20;         // OK
    // p2 = &y;       // 取消注释 → 报错
    cout << "x = " << x << endl;

    cout << "\n=== 实验3: const int &r ===" << endl;
    const int &r = x;
    // r = 30;        // 取消注释 → 报错
    cout << "r = " << r << endl;

    return 0;
}