### 首先，理解一下“重载”

“重载”是面向对象编程（尤其是 C++、Java、C# 等语言）中一个非常重要的概念，指的是**在同一个作用域内，允许多个函数或运算符拥有相同的名称，但具有不同的参数列表（参数个数、类型或顺序不同）**。编译器会根据调用时传入的参数来决定具体调用哪一个版本，这个过程发生在编译期，属于**静态多态**。

------

### 一、函数重载（Function Overloading） 

#### 1. 核心规则 

- 函数名相同 
- 参数列表必须不同（参数个数不同，或参数类型不同，或参数顺序不同） 
- 返回值类型**可以不同**，但**不能仅靠返回值类型区分**（因为调用时可能不关心返回值，导致歧义） 

#### 2. 示例 

```cpp
#include <iostream>
using namespace std;

// 打印整数
void print(int x) {
    cout << "Integer: " << x << endl;
}

// 打印浮点数（参数类型不同）
void print(double x) {
    cout << "Double: " << x << endl;
}

// 打印字符串（参数类型不同）
void print(const char* str) {
    cout << "String: " << str << endl;
}

// 打印两个整数（参数个数不同）
void print(int a, int b) {
    cout << "Two integers: " << a << ", " << b << endl;
}

int main() {
    print(42);          // 调用 print(int)
    print(3.14);        // 调用 print(double)
    print("Hello");     // 调用 print(const char*)
    print(1, 2);        // 调用 print(int, int)
    return 0;
}
```





#### 3. 注意事项 

- **参数类型匹配**：编译器会寻找最佳匹配，必要时会进行隐式类型转换（如 `int` 转 `double`），但可能引起歧义。 

- 默认参数

  ：重载与默认参数一起使用时需小心，可能导致二义性。例如： 

  

  ```cpp
  void func(int a);
  void func(int a, int b = 10);  // 调用 func(5) 时，两个都能匹配，编译错误
  ```

  

  

- **const 限定**：对于成员函数，`const` 版本和非 `const` 版本可以构成重载（因为 `this` 指针类型不同）。 

------

### 二、运算符重载（Operator Overloading） 

运算符重载是函数重载的一种特殊形式，允许用户自定义类型（如类）使用已有的运算符（`+`, `-`, `*`, `<<` 等）时表现出特定的行为。

#### 示例：复数类的加法 



```cpp
class Complex {
public:
    double real, imag;
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // 重载 + 运算符
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
};

int main() {
    Complex c1(1, 2), c2(3, 4);
    Complex c3 = c1 + c2;  // 实际调用 c1.operator+(c2)
    return 0;
}
```





运算符重载的本质也是函数重载——`operator+` 就是一个特殊的函数名。C++ 中大部分运算符都可以重载，但有一些不能（如 `::`, `.*`, `?:` 等）。

------

### 三、为什么要使用重载？ 

1. **提高代码可读性**：用同一个名字表示“同一类操作”，比如 `print` 可以打印不同类型的数据，比分别命名 `printInt`, `printDouble`, `printString` 更自然。 
2. **简化接口**：让用户无需记忆多个函数名，只需根据传入参数的不同自动匹配。 
3. **实现泛型思想**：虽然 C++ 有模板，但重载也是一种轻量级的“多态”手段。 
4. **运算符重载使自定义类型表现得更像内置类型**，例如 `string` 的 `+` 拼接，`vector` 的 `[]` 访问。 

------

### 四、重载与覆盖、隐藏的区别 



| 概念                 | 作用域                   | 参数列表     | 关键字    | 决定时机           |
| -------------------- | ------------------------ | ------------ | --------- | ------------------ |
| **重载**             | 同一作用域（同一个类内） | 必须不同     | 无        | 编译期             |
| **覆盖（Override）** | 派生类覆盖基类的虚函数   | 必须完全相同 | `virtual` | 运行期（动态绑定） |
| **隐藏（Hide）**     | 派生类屏蔽基类的同名函数 | 可相同可不同 | 无        | 编译期（名字查找） |

------

### 五、总结 

**重载** 就是“同名不同参，编译选其一”。它让代码更简洁、更直观，是 C++ 静态多态的重要体现。理解重载的关键在于：**参数列表是唯一区分标识**，返回值类型不能作为区分依据。掌握了这一点，你就能轻松运用重载来设计更友好的接口。

------

## 第一步：理解 const 成员函数与 const 对象（C++ 主线）

### 1.1 今天站在昨天的肩膀上

昨天你学会了给**指针**加锁：`const int *p` 表示"不能改指向的值"。  
今天换个场景：**对象**也可以加锁。一个被 `const` 修饰的对象，只允许调用"承诺不改对象"的成员函数，这种函数就叫 **`const` 成员函数**。

> 昨天的口诀"const 离谁近锁住谁"今天升级：  
> `const` 放在**成员函数声明的末尾** → 锁住"这个成员函数不能修改对象本身"。

### 1.2 核心语法

```cpp
class Point {
private:
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) {}

    int getX() const { return x; }   // ✅ const 成员函数：只读，不修改对象
    void setX(int v)   { x = v; }    // 普通成员函数：可以修改对象
};
```

**关键点：**

- `const` 放在函数参数列表**后面**、函数体**前面**。
- 在 `const` 成员函数内部，**不能修改任何成员变量**（除非成员变量被声明为 `mutable`）。
- `const` 成员函数**可以重载**普通版本（同名、参数相同、一个有 const 一个没有）。

### 1.3 const 对象只能调用 const 成员函数

```cpp
const Point p(3, 4);   // const 对象
p.getX();              // ✅ OK：getX 是 const 成员函数
// p.setX(5);          // ❌ 编译错误：const 对象不能调用非 const 成员函数
```

而普通对象两者都能调用：

```cpp
Point q(1, 2);
q.getX();              // ✅ OK
q.setX(10);            // ✅ OK
```

### 1.4 为什么需要 const 成员函数？

**保护 + 自文档化 + 接口清晰。** 最常见的用途是作参数：

```cpp
// 接收一个 Point，但承诺"我只读、绝不改你"
void printPoint(const Point &p) {
    cout << p.getX() << endl;   // ✅ getX 是 const 的，可以调
    // p.setX(5);               // ❌ 编译错误
}
```

> 如果 `getX` 不是 `const` 的，上面这个函数就编不过——因为 `const Point &` 只能调 `const` 成员函数。  
> 这正好呼应昨天你学的"函数参数用 `const int *p` 最安全"：这里用 `const Point &` 是同一个道理，只是换成了对象。

### 1.5 动手实验：写 Point 类验证（今日必做产出） ✍️

新建 `week2/thu_const_member.cpp`：

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int x_, y_;
public:
    Point(int x, int y) : x_(x), y_(y) {}

    // const 成员函数：只读
    int getX() const { return x_; }
    int getY() const { return y_; }

    // 非 const 成员函数：可修改
    void setX(int x) { x_ = x; }
    void setY(int y) { y_ = y; }

    // const 成员函数里试图修改 → 编译错误（取消下面注释验证）
    // void tryModify() const { x_ = 100; }
};

int main() {
    Point a(3, 4);
    const Point b(10, 20);   // const 对象

    cout << "a.x = " << a.getX() << endl;   // ✅
    a.setX(99);                             // ✅ 普通对象可调非 const
    cout << "a.x after setX = " << a.getX() << endl;

    cout << "b.x = " << b.getX() << endl;   // ✅ const 对象可调 const 成员函数
    // b.setX(1);                           // ❌ 取消注释 → 报错：const 对象不能调非 const

    return 0;
}
```

## 1. `Point(int x, int y) : x_(x), y_(y) {}` 是什么？ 

这是 **构造函数（Constructor）**。

### 它干了什么 

```cpp
Point p(10, 20);  // 创建对象时自动调用
```

调用过程等价于：

1. 分配 `p` 的内存 
2. **初始化列表** `: x_(x), y_(y)` 把 `x_` 初始化为 `10`，`y_` 初始化为 `20` 
3. 进入函数体 `{}`（这里为空，啥也不做） 

### 为什么用初始化列表而不是赋值？ 

```cpp
// 方式A：初始化列表（推荐）
Point(int x, int y) : x_(x), y_(y) {}

// 方式B：函数体内赋值
Point(int x, int y) { x_ = x; y_ = y; }
```

区别：

|            | 初始化列表               | 函数体内赋值               |
| ---------- | ------------------------ | -------------------------- |
| 执行时机   | 对象创建时**直接初始化** | 先默认构造，再**赋值覆盖** |
| 效率       | ✅ 更高                   | ❌ 多一次操作               |
| const 成员 | ✅ 可以初始化             | ❌ 不能赋值                 |
| 引用成员   | ✅ 可以初始化             | ❌ 不能赋值                 |

> **结论：构造函数 + 初始化列表是 C++ 里创建对象的标准写法。**

------

## 2. `private:` 下面那两行是"声明"吗？ 

是的，但更准确的说法是 **成员变量声明**。

```cpp
private:
    int x_, y_;   // ← 这是成员变量声明
```

### 完整理解 

```cpp
class Point {
private:
    int x_, y_;    // ① 声明：告诉编译器"这个类的对象里有这两个 int"
public:
    Point(int x, int y) : x_(x), y_(y) {}  // ② 构造函数定义
    int getX() const { return x_; }        // ③ 成员函数定义
};
```

| 代码                        | 性质                                               |
| --------------------------- | -------------------------------------------------- |
| `int x_, y_;`               | 成员变量**声明**（同时隐含了类型、名称、访问权限） |
| `Point(int x, int y) : ...` | 构造函数**定义**                                   |
| `int getX() const { ... }`  | 成员函数**定义**（类内定义 = 隐式 inline）         |

### `private` 的作用 

`private` **不是声明**，是**访问控制修饰符**：

- `private:` → 后面的成员只能在**类内部**访问 
- `public:` → 后面成员可以在**类外部**访问 

```cpp
Point p(1, 2);
p.x_;        // ❌ 编译错误：x_ 是 private
p.getX();    // ✅ OK：getX() 是 public
```

------

## 3. 整体串起来：对象长什么样？ 

```cpp
Point p(3, 4);
```

内存里 `p` 长这样：

```
p
├── x_ = 3    (private, 只有类内方法能直接访问)
└── y_ = 4    (private, 只有类内方法能直接访问)
```

外部代码只能通过 `public` 接口操作它：

```cpp
p.setX(10);      // ✅ 通过 public 方法修改
int a = p.getX(); // ✅ 通过 public 方法读取
```

------

## 4. 一句话总结 

| 问题                          | 答案                                                     |
| ----------------------------- | -------------------------------------------------------- |
| `Point(int x, int y)` 是什么  | **构造函数**，创建对象时自动调用，负责初始化成员变量     |
| `: x_(x), y_(y)` 是什么       | **初始化列表**，在对象创建时直接初始化成员，比赋值更高效 |
| `private: int x_, y_;` 是什么 | **成员变量声明**，`private` 限制它们只能在类内部访问     |
| 外部怎么用                    | 通过 `public` 成员函数（getter/setter）间接读写          |

**验证方法**：用 `g++ -std=c++17 thu_const_member.cpp -o pm && ./pm` 编译运行；把 `tryModify` 或 `b.setX(1)` 的注释取消，观察报错信息是否符合预期。

![](D:\Projects\W2_8_Cpp\assets\DvlKr0OZTv.png)

![](D:\Projects\W2_8_Cpp\assets\kaox1sxWmo.png)

**完成前自测 3 个问题（写进笔记）：**

1. `int getX() const` 末尾这个 `const` 锁住了什么？

   锁住了成员变量x_，使得成员函数无法修改成员变量，只能读取

2. 普通对象能调用 `const` 成员函数吗？反过来呢（const 对象调非 const 函数）？

   可以，不行，哪怕是非const函数并不涉及修改变量也不行

3. 写一个函数 `void dump(const Point &p)`，内部打印 `p.getX()`——为什么 `getX` 必须是 `const` 的？

   不行，const对象只能调用const函数

------

## 第二步：C 语言穿插（限时 20 分钟） ⏱️

新建 `week2/thu_struct_c.c`：

```c
#include <stdio.h>
#include <stdlib.h>

// C 的 struct 没有成员函数，只有数据
struct Student {
    int id;
    char name[20];
    float score;
};

int main(void) {
    struct Student s = {1001, "Alice", 92.5f};

    // 普通变量用 . 访问成员
    printf("id = %d, name = %s, score = %.1f\n", s.id, s.name, s.score);

    // 指针用 -> 访问成员
    struct Student *p = &s;
    printf("via pointer -> id = %d\n", p->id);
    p->score = 95.0f;                                 // 通过指针修改
    printf("after modify -> score = %.1f\n", p->score);

    // 动态分配一个 Student
    struct Student *q = (struct Student *)malloc(sizeof(struct Student));
    if (q != NULL) {
        q->id = 1002;
        // 字符串拷贝用 strcpy，不要直接 = 
        // q->name = "Bob";   // ❌ 数组不能直接赋值
        q->score = 88.0f;
        printf("malloc -> id = %d, score = %.1f\n", q->id, q->score);
        free(q);
    }
    return 0;
}
```

编译运行：`gcc -std=c11 thu_struct_c.c -o sc && ./sc`

这是 C 语言里一个**非常经典、也非常重要**的坑，本质上是：

> **数组不是"一等公民"，数组名在大多数情况下会退化成指针，但它本身不能被赋值。**

------

## 一句话结论 



```c
q->name = "Bob";   // ❌ 编译错误
```





因为 **name 是数组**，数组**不能整体赋值**。

字符串 `"Bob"` 是字符串常量（类型是 `char[4]` / `char*`），你不能用 `=` 把一个地址或数组"塞进"另一个数组。

------

## 1. `name` 到底是什么？ 



```c
struct Student {
    char name[20];   // ← 这是数组，不是指针
};
```





在 `Student` 里，`name` 是**内嵌的 20 个 char 的连续内存**：



```
q
├── id      (int)
├── name    [20 个 char，直接存在结构体里]
└── score   (float)
```





`name` **不是一个指针变量**，它是一块"已经分配好的内存"。

------

## 2. 为什么 `=` 不行？ 

C 语言规定：

> **数组是不可修改的左值（array is not a modifiable lvalue）**

也就是说：



| 操作                           | 是否允许 | 原因                   |
| ------------------------------ | -------- | ---------------------- |
| `int a[10]; a = ...;`          | ❌        | 数组整体不能赋值       |
| `char name[20]; name = "Bob";` | ❌        | 同上                   |
| `char *p; p = "Bob";`          | ✅        | p 是指针，可以指向别处 |
| `int x; x = 10;`               | ✅        | 普通变量可以赋值       |

`q->name = "Bob"` 本质上等价于：



```c
char name[20];
name = "Bob";   // ❌ 数组名 name 是地址常量，不能当左值
```





------

## 3. `"Bob"` 到底是什么？ 



```c
"Bob"
```





这是一个**字符串常量**，类型是：



```
const char[4]   // 'B','o','b','\0'
```





存储在**只读数据段**（`.rodata`），不是你 `malloc` 出来的堆内存。

你不能用 `=` 把它"复制"到数组里，只能：

- **逐字符拷贝** 
- **用库函数拷贝** 

------

## 4. 正确的做法 

### ✅ 方法一：`strcpy`（最常用） 



```c
#include <string.h>   // ← 别忘了头文件

strcpy(q->name, "Bob");
```





作用：把 `"Bob\0"` 逐个字符**拷贝**到 `q->name` 指向的内存里。



```
q->name: ['B', 'o', 'b', '\0', ?, ?, ...]
```





### ✅ 方法二：`strncpy`（更安全） 



```c
strncpy(q->name, "Bob", sizeof(q->name) - 1);
q->name[sizeof(q->name) - 1] = '\0';  // 手动补 \0
```





防止源字符串太长，溢出 `name[20]`。

### ✅ 方法三：逐个赋值（不实用但合法） 



```c
q->name[0] = 'B';
q->name[1] = 'o';
q->name[2] = 'b';
q->name[3] = '\0';
```





------

## 5. 对比：如果 `name` 是指针，情况完全不同 



```c
struct Student {
    int id;
    char *name;    // ← 指针，不是数组
    float score;
};
```





这时：



```c
q->name = "Bob";   // ✅ 合法，指针指向字符串常量
```





但代价是：



| 问题           | 说明                       |
| -------------- | -------------------------- |
| 字符串在只读区 | 不能 `q->name[0] = 'T'`    |
| 结构体拷贝时   | 两个结构体指向同一块字符串 |
| 动态分配时     | 需要额外 `malloc` + `free` |

所以你的代码里用 `char name[20]` 其实是**更安全、更常见**的写法。

------

## 6. 对比 C++ 为什么没这个问题？ 

C++ 里你几乎不会手写 `char name[20]`，而是：



```cpp
class Student {
    std::string name;   // ← string 重载了 =，内部帮你管理内存
};

Student s;
s.name = "Bob";   // ✅ string 的 operator= 做了深拷贝
```





C 没有 `std::string`，所以你得**手动管理字符串内存**，这就是 `strcpy` 存在的原因。

------

## 总结一句话 

> **q->name = "Bob" 不行，因为 name 是数组，数组不能整体赋值。必须用 strcpy 把字符串内容拷贝进去。**

这是 C 语言里"数组 vs 指针"最核心的区别之一，搞明白这个，后面指针、函数传参、动态内存的坑会少踩一大半。

**C vs C++ 对比要点（写进差异笔记）：**

| 对比项         | C                       | C++                                |
| :------------- | :---------------------- | :--------------------------------- |
| struct 关键字  | 必须写 `struct Student` | 可直接 `Student`（已注入名字空间） |
| 成员函数       | ❌ 没有                  | ✅ 有（类成员函数）                 |
| 访问成员       | `.` 和 `->`             | 同样 `.` 和 `->`                   |
| const 成员函数 | ❌ 没有                  | ✅ `int getX() const`               |
| 成员初始化     | 定义时整体赋值或逐个    | 构造函数                           |

**结论：今天 C++ 的 `const` 成员函数是纯 C++ 特性，C 里做不了。** 但 `.` 和 `->` 的用法两边一致。

## 数组名什么时候退化成指针，什么时候不是？ 

这是 C 语言里最容易被误解、也最常考的点。

### 先给结论 

> **数组名在大多数表达式中会"退化"成指向首元素的指针，但有 3 种情况不会。**

------

## 一、什么是"退化"？ 



```c
int arr[5] = {1, 2, 3, 4, 5};
```





`arr` 本身代表**整个数组**（20 字节，假设 int=4），但在大多数表达式中，编译器会把它当成：



```c
&arr[0]    // 指向第一个元素的指针，类型是 int*
```





这就是"退化"（decay）。

------

## 二、什么时候会退化（→ 指针） 

### ✅ 1. 赋值给指针 



```c
int *p = arr;      // arr 退化为 &arr[0]，类型是 int*
p = arr + 1;       // arr 退化为 int*，+1 跳 4 字节
```





### ✅ 2. 作为函数参数 



```c
void foo(int arr[]) {
    // arr 在这里已经是指针了！
    sizeof(arr);    // ❌ 不是 20，是 8（64 位指针大小）
}

foo(arr);           // arr 退化为 int*
```





> **函数参数里的 int arr[] 和 int \*arr 完全等价**，这是 C 语言的"语法糖"。

### ✅ 3. 算术运算 



```c
arr + 1;    // arr 退化为 int*，+1 跳到 &arr[1]
```





### ✅ 4. 比较 



```c
if (arr == &arr[0])  // 相等，arr 退化为 &arr[0]
```





------

## 三、什么时候**不会**退化（仍然是数组） 

### ❌ 1. `sizeof(arr)` 



```c
int arr[5];
sizeof(arr);     // 20（整个数组的大小）
sizeof(&arr[0]); // 8（指针大小）
```





> 如果退化了，`sizeof` 应该返回 8，但它返回了 20 → **没退化**

### ❌ 2. `&arr`（取整个数组的地址） 



```c
int arr[5];
printf("%p\n", arr);     // 首元素地址，类型是 int*
printf("%p\n", &arr);    // 整个数组的地址，类型是 int(*)[5]
```





数值上 `arr` 和 `&arr` **一样**，但类型不同：



```c
arr + 1;     // 跳 4 字节（到 arr[1]）
&arr + 1;    // 跳 20 字节（跳过整个数组！）
```





### ❌ 3. `sizeof` 出现在数组声明时（字符串初始化） 



```c
char str[] = "hello";   // str 是数组，不是指针
sizeof(str);             // 6（包含 '\0'）
```





对比：



```c
char *p = "hello";
sizeof(p);    // 8（指针大小）
```





------

## 四、一张表总结 



| 场景                | 数组名行为       | 结果类型    |
| ------------------- | ---------------- | ----------- |
| `int *p = arr`      | 退化为首元素指针 | `int*`      |
| `foo(arr)` 函数传参 | 退化为指针       | `int*`      |
| `arr + 1`           | 退化为指针       | `int*`      |
| `sizeof(arr)`       | **不退化**       | 整个数组    |
| `&arr`              | **不退化**       | `int(*)[5]` |
| `char str[] = "hi"` | **不退化**       | `char[3]`   |

------

## 五、经典面试题 

### Q1: 下面代码输出什么？ 



```c
int arr[5] = {1, 2, 3, 4, 5};
printf("%d\n", sizeof(arr));        // ?
printf("%d\n", sizeof(arr + 0));    // ?
```





答案：

- `sizeof(arr)` → `20`（不退化） 
- `sizeof(arr + 0)` → `8`（退化成 `int*`，指针大小） 

### Q2: 为什么 `arr` 和 `&arr` 打印出来地址一样？ 



```c
printf("%p %p\n", arr, &arr);
```





因为：

- `arr` → 首元素地址 = 数组起始地址 
- `&arr` → 整个数组的地址 = 也是数组起始地址 

**数值相同，语义不同。**

### Q3: 为什么函数里 `sizeof(arr)` 不等于数组大小？ 



```c
void foo(int arr[]) {
    printf("%zu\n", sizeof(arr));  // 8，不是 20
}
```





因为参数里的 `int arr[]` **就是 int \*arr**，退化已经发生，函数里拿到的只是指针。

------

## 六、跟你的 `Student` 例子串起来 



```c
struct Student {
    char name[20];
};
```





- `name` 是数组 → `sizeof(s.name)` = 20 ✅（没退化） 
- `q->name` 在函数参数里退化 → `sizeof(q->name)` 在 `foo(struct Student s)` 里仍然是 20（因为是成员访问，不是参数传递） 
- `q->name` 退化为 `char*` 的情况：`strcpy(q->name, "Bob")` 里，`q->name` 退化为 `char*` 传给 `strcpy` ✅



## "数组和指针等价"这句话到底对不对？ 

### 先给结论 

> **这句话半对半错，是 C 语言里最大的误导之一。**

准确说法应该是：

> **"数组在表达式中会退化为指针，但数组和指针是两种完全不同的类型。"**

------

## 一、为什么教科书说"等价"？ 

因为 Kernighan & Ritchie（C 语言之父）在《The C Programming Language》里写过：

> *"When an array name is passed to a function, it is treated as a pointer to the first element."*

后来被简化成了一句流传甚广的"口诀"：

> **"数组名就是指针。"**

这句话**在函数传参的场景下是对的**，但被无限推广后就变成了坑。

------

## 二、数组和指针的本质区别 

### 数组：有"实体" 



```c
char name[20];
```





内存里真真实实占了 20 个字节：



```
name: [ ][ ][ ][ ]...20个char，就在结构体/栈里
```





- 数组名 `name` 是这块内存的**名字/标签** 
- 它不存储任何地址，它**就是**这块内存本身 

### 指针：只有"地址" 



```c
char *p;
```





内存里只占了 8 个字节（64 位），存的是一个地址：



```
p: [0x7fff3a4b2c10]  →  指向别处的某块内存
```





- 指针变量本身是一块内存 
- 它**指向**另一块内存 

------

## 三、用 `sizeof` 戳穿"等价"谎言 



```c
char arr[20];
char *p = arr;

printf("%zu\n", sizeof(arr));   // 20  ← 整个数组
printf("%zu\n", sizeof(p));     // 8   ← 指针
```





如果等价，`sizeof` 结果应该一样。不一样 → **不等价**。

------

## 四、用 `&` 再戳一次 



```c
printf("%p\n", (void*)&arr);        // 0x7fff... 类型: char (*)[20]
printf("%p\n", (void*)&arr[0]);     // 0x7fff... 类型: char *
printf("%p\n", (void*)&p);          // 0x7ffe... 类型: char **
```







| 表达式    | 类型           | 含义               |
| --------- | -------------- | ------------------ |
| `&arr`    | `char (*)[20]` | 整个数组的地址     |
| `&arr[0]` | `char *`       | 首元素地址         |
| `&p`      | `char **`      | 指针变量自身的地址 |

三种类型，三种语义。

------

## 五、函数参数：唯一"等价"的地方 



```c
void foo(char arr[]);    // ← 编译器眼里就是 void foo(char *arr)
void bar(char *p);
```





这两个函数签名**完全等价**，编译器生成的代码一模一样。

所以：



```c
char a[20];
foo(a);    // a 退化为 char*，传进去
bar(a);    // 同上
```





这是"数组和指针等价"这句话**唯一成立的地方**。

------

## 六、反过来不成立：指针不能当数组用 



```c
char *p = "hello";
char arr[20];

arr = p;        // ❌ 数组不能赋值
p = arr;        // ✅ 指针可以指向数组

sizeof(arr);    // 20
sizeof(p);      // 8

&arr + 1;       // 跳过 20 字节
&p + 1;         // 跳过 8 字节
```





------

## 七、一个经典错误 



```c
char *getName() {
    char name[] = "Alice";   // 栈上数组
    return name;              // ❌ 返回栈内存地址，函数结束后 name 被销毁
}
```





对比：



```c
char *getName() {
    return "Alice";           // ✅ 字符串常量在只读区，不会销毁
}
```





或者正确写法：



```c
void getName(char *buf, size_t n) {
    strncpy(buf, "Alice", n - 1);
    buf[n - 1] = '\0';
}
```





------

## 八、一句话总结 



| 说法                       | 对不对                                 |
| -------------------------- | -------------------------------------- |
| "数组名就是指针"           | ❌ 错，数组名是数组，不是指针变量       |
| "数组在表达式中退化为指针" | ✅ 对，除了 `sizeof`、`&`、字符串初始化 |
| "函数参数里数组和指针等价" | ✅ 对，这是唯一等价的地方               |
| "数组和指针可以互换使用"   | ❌ 错，类型不同、sizeof不同、语义不同   |

------

## 九、怎么记住不混 

> **数组是"房子"，指针是"地址条"。**

- 房子本身有大小（`sizeof` = 20） 
- 地址条只是一张纸（`sizeof` = 8） 
- 你可以把地址条指向房子（`p = arr`） 
- 但你不能把房子搬进地址条（`arr = p` ❌）

------

## 第三步：算法副线——LeetCode 209 长度最小的子数组

今天只做这一道，**C++ 版和 C 版各提交一次**。

### 思路（滑动窗口，30 秒版）

给定正整数数组 `nums` 和目标值 `target`，求**和 ≥ target 的长度最小的连续子数组**。

- 用两个指针 `left`、`right` 维护一个窗口 `[left, right]`。
- `right` 向右扩张，累加窗口和；一旦和 ≥ target，就记录长度，并尝试收缩 `left` 找更短的。
- 时间复杂度 O(n)（每个元素最多被 left、right 各访问一次）。

### C++ 版（vector）

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0, sum = 0, ans = n + 1;   // ans 初值设大一点
        for (int right = 0; right < n; right++) {
            sum += nums[right];                // 扩张右边界
            while (sum >= target) {            // 满足条件就尽量收缩
                ans = min(ans, right - left + 1);
                sum -= nums[left++];
            }
        }
        return ans == n + 1 ? 0 : ans;         // 没找到返回 0
    }
};
```

### C 版（数组 + 长度参数）

```c
int minSubArrayLen(int target, int* nums, int numsSize) {
    int left = 0, sum = 0, ans = numsSize + 1;
    for (int right = 0; right < numsSize; right++) {
        sum += nums[right];
        while (sum >= target) {
            int len = right - left + 1;
            if (len < ans) ans = len;
            sum -= nums[left++];
        }
    }
    return ans == numsSize + 1 ? 0 : ans;
}
```

### 三个易错点（提交前自查）

1. **`ans` 初始值**：要设成 `n + 1`（比最大可能长度还大），这样第一次找到时一定会被更新。
2. **没找到要返回 0**，不是返回 `ans`。
3. **收缩时用 `while` 不是 `if`**：满足条件后要一直缩，才能找到"最小"。

### Q1: `ans` 初值为什么是 `n + 1` 而不是 `INT_MAX`？ 

```cpp
int ans = n + 1;
```

- 最短子数组长度最多是 `n` 
- `n + 1` 是一个"不可能达到的值"，天然表示"还没找到" 
- 比 `INT_MAX` 更安全（避免 `min(ans, ...)` 溢出风险） 

### Q2: 为什么 `while` 不是 `if`？ 

```cpp
while (sum >= target) { ... }   // ← while，不是 if
```

因为收缩可能不止一步。比如 `sum` 远大于 `target`，需要多次 `left++` 才能退出。

### Q3: 如果数组有负数，这个算法还成立吗？ 

❌ **不成立**。有负数时 `sum` 不单调，收缩 `left` 后 `sum` 可能反而增大，无法保证"缩到极限就是最优"。此时需要前缀和 + 二分，时间复杂度 O(n log n)。

### 手动验证示例

```
输入: target = 7, nums = [2, 3, 1, 2, 4, 3]
过程: [2,3,1,2] 和=8 ≥7，缩→[3,1,2]和=6<7，再扩→[3,1,2,4]和=10≥7 缩...
输出: 2   （子数组 [4,3]）
```

## 一、算法在做什么（直觉） 



```
right 一直往右走（扩张窗口）
     ↓
sum >= target 时，left 往右缩（尽量让窗口变小）
     ↓
记录所有满足条件的最小窗口长度
```





这是**固定方向**的扫描：每个 `right` 只管自己作为**右端点**时，能找到的最短合法子数组。

------

## 二、为什么不会遗漏？（核心证明） 

### 关键性质：所有元素都是正数 

LeetCode 209 的约束：

> ```
> 1 <= nums[i] <= 10^4
> ```

**全是正数** → `sum` 是单调递增的（右移 left 只会让 sum 减小，右移 right 只会让 sum 增大）。

### 证明思路 

对任意一个**合法的子数组** `nums[i...j]`（即 `sum(i..j) >= target`）：

1. 当 `right = j` 时，算法一定会进入 `while (sum >= target)` 循环 
2. `left` 会从当前位置一直右移，直到 `sum < target` 
3. 在这个过程中，`left` **必然经过 i**（因为 `i` 是合法左端点） 
4. 所以 `ans = min(ans, j - i + 1)` 一定会被执行到 

✅ **每一个合法子数组，都至少会在其右端点被扫描到一次。**

------

### 换个角度理解 

算法对每个 `right`，找到的是：

> **以 right 为右端点的最短合法子数组**

因为所有元素 > 0，以 `right` 为右端点的子数组中：

- 越短（left 越靠右）→ sum 越小 
- 一旦 `sum < target`，再往右缩就永远不合法了 

所以 `while` 循环收缩到极限时，记录的就是**以 right 为右端点的最优解**。

遍历了所有 `right` → 全局最优解一定被覆盖。

------

## 三、有没有可能漏掉"跨过 left 之前位置"的解？ 

不会。因为：

- `left` 只往右移，不回退 
- 但 `left` 右移是因为**当前窗口已经满足条件了**，再往左扩只会更长、不会更优 
- 全局最优解一定是某个 `right` 对应的最短窗口，而我们已经对每个 `right` 都找了最短 

------

## 四、时间复杂度 

### 时间复杂度：**O(n)** 



| 操作                | 次数                                 |
| ------------------- | ------------------------------------ |
| `right` 从 0 到 n-1 | 每个元素最多被 `right` 访问 **1 次** |
| `left` 从 0 到 n-1  | 每个元素最多被 `left` 访问 **1 次**  |
| 总操作              | **2n 次** → O(n)                     |

> 这是**均摊 O(1)** 的双指针，不是嵌套循环。

### 空间复杂度：**O(1)** 

只用了几个变量，没有额外数组。

如果要将时间复杂度优化至O(nlogn)：

## 前缀和 + 二分查找思路 

### 核心思想 

> 对每个位置 `i`，找**最左边**的 `j` 使得 `sum(i...j) >= target`。

因为所有元素都是正数，前缀和数组是**严格递增**的，所以可以二分。

### 步骤 

1. **预处理前缀和数组** `preSum[i]` = `nums[0] + ... + nums[i-1]` 
2. 对每个 `i`，二分查找最小的 `j` 使得 `preSum[j+1] - preSum[i] >= target` 
3. 记录最小长度 `j - i + 1` 

------

## 代码实现 



```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        
        // 1. 构建前缀和数组
        // preSum[i] = nums[0] + ... + nums[i-1]
        // preSum[0] = 0
        vector<int> preSum(n + 1, 0);
        for (int i = 0; i < n; i++) {
            preSum[i + 1] = preSum[i] + nums[i];
        }
        
        int ans = n + 1;
        
        // 2. 对每个起点 i，二分查找满足条件的最左终点
        for (int i = 0; i < n; i++) {
            int need = target + preSum[i];  // 需要 preSum[j+1] >= need
            
            // 在 preSum[i+1 ... n] 中二分查找第一个 >= need 的位置
            auto it = lower_bound(preSum.begin() + i + 1, preSum.end(), need);
            
            if (it != preSum.end()) {
                int j = it - preSum.begin() - 1;  // j 是终点下标
                ans = min(ans, j - i + 1);
            }
        }
        
        return ans == n + 1 ? 0 : ans;
    }
};
```





------

## 为什么能二分？ 

前缀和数组 `preSum` 是严格递增的（因为 `nums[i] > 0`）：



```
preSum = [0, 2, 5, 6, 8, 12, 15]
```





对固定的 `i`，我们要找最小的 `j` 使得：



```
preSum[j+1] - preSum[i] >= target
```





即：



```
preSum[j+1] >= target + preSum[i]
```





右边是一个定值，左边是递增数组 → **二分查找完美适用**。

------

## 复杂度分析 



| 操作                | 复杂度             |
| ------------------- | ------------------ |
| 构建前缀和          | O(n)               |
| 对每个 `i` 二分查找 | O(log n)           |
| 总复杂度            | **O(n log n)**     |
| 空间                | O(n)（前缀和数组） |

------

## 滑动窗口 O(n) vs 前缀和+二分 O(n log n) 



|            | 滑动窗口   | 前缀和+二分                |
| ---------- | ---------- | -------------------------- |
| 时间       | **O(n)** ✅ | O(n log n)                 |
| 空间       | O(1) ✅     | O(n)                       |
| 思路直观性 | 稍难理解   | 更直观（枚举+查找）        |
| 有负数时   | ❌ 不能用   | ❌ 也不能用（前缀和不递增） |

> **实际刷题/面试：滑动窗口是最优解，前缀和+二分是"退而求其次"但思路更清晰的方案。