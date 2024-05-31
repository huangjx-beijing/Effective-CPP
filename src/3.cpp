#include <iostream>

class Parent
{
public:
    Parent() : a(38) {}
    virtual ~Parent() {}
    short a;
};

class Child : public Parent
{
public:
    Child() : Parent(), b(200), trival("123") {}
    ~Child() {}
    long b;
    std::string trival;
};

void print(const Parent p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << p[i].a << std::endl;
    }
}

int main()
{
    Child childList[10];
    print(childList, 10);
    return 0;
}