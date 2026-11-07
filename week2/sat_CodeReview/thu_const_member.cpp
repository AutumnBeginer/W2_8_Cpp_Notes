#include <iostream>
using namespace std;

class Point{
private:
    int x_,y_;
public:
    Point(int x,int y):x_(x),y_(y){}

    //const成员函数，只读
    int getX()const{return x_;}
    int getY()const{return y_;}
    //非const成员函数，可写
    void setX(int newX){x_=newX;}
    void setY(int newY){y_=newY;}
    // const 成员函数里试图修改 → 编译错误（取消下面注释验证）
    // void tryModify() const { x_ = 100; }
};

int main(){
    Point a(5,5);
    const Point b(8,8);
    cout << "a.x = " << a.getX() << endl;   // ✅
    a.setX(99);                             // ✅ 普通对象可调非 const
    cout << "a.x after setX = " << a.getX() << endl;

    cout << "b.x = " << b.getX() << endl;   // ✅ const 对象可调 const 成员函数
    // b.setX(1);                           // ❌ 取消注释 → 报错：const 对象不能调非 const

    return 0;
}