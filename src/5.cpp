#include <iostream>

class Int
{
public:
    Int(int size) : m_value(size) {}

    // 前置
    Int& operator++()
    {
        ++m_value;
        return *this;
    }

    // 后置
    const Int operator++(int)
    {
        Int temp = *this;
        ++(*this);
        return temp;
    }

    operator int() const
    {
        return m_value;
    }

private:
    int m_value;
};

class R
{
public:
    R(int a, int b) : m_a(a), m_b(b) { std::cout << "构造R" << std::endl; }

    R(const R& r) : m_a(r.m_a), m_b(r.m_b) { std::cout << "复制构造R" << std::endl; }

    ~R() { std::cout << "析构" << std::endl; }

    R& operator=(const R& r)
    {
        std::cout << "赋值" << std::endl;
        m_a = r.m_a;
        m_b = r.m_b;
        return *this;
    }

    int a() const { return m_a; }

    int b() const { return m_b; }

private:
    int m_a;
    int m_b;
};

const R operator*(const R& r1, const R& r2)
{
    //R temp(r1.a() * r2.a(), r1.b() * r2.b());
    //return temp;

    return R(r1.a() * r2.a(), r1.b() * r2.b());
}

int main()
{
    int i = 1;

    std::cout << ++i << std::endl; // 2

    std::cout << i << std::endl;   // 2

    std::cout << i++ << std::endl; // 2

    std::cout << i << std::endl;   // 3

    std::cout << ++++i << std::endl; // 5

    std::cout << i << std::endl;  // 5

    ++i = 10;

    std::cout << i << std::endl;  // 10

    // 内置类型前置++: 先增加，返回引用

    // std::cout << i++++ << std::endl;   // 错误:后置++ 返回常量 不能再++

    // std::cout << ++i++ << std::endl;   // 错误:默认先计算后置++  后置++ 返回常量 不能再++

    // std::cout << ++(i++) << std::endl; // 错误:后置++ 返回常量 不能再++

    std::cout << (++i)++ << std::endl;  // 11

    std::cout << i << std::endl;  // 12


    Int myInt = 0;

    std::cout << myInt << std::endl;

    std::cout << ++myInt << std::endl;

    std::cout << myInt << std::endl;

    std::cout << myInt++ << std::endl;

    std::cout << myInt << std::endl;


    R r1(1, 2);
    R r2(3, 4);

    R c = r1 * r2;


    return 0;
}