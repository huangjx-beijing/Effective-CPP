#include <iostream>
#include <memory>

class ALA
{
public:
    ALA() { std::cout << "ALA 构造" << std::endl; }
    virtual ~ALA() { std::cout << "ALA 析构" << std::endl; }
    virtual void processAdoption() = 0;
};

class Puppy : public ALA
{
public:
    Puppy() : ALA() { std::cout << "Puppy 构造" << std::endl; }
    virtual ~Puppy() { std::cout << "Puppy 析构" << std::endl; }
    virtual void processAdoption()
    {
        std::cout << "Process Puppy Adoption" << std::endl;
    }
};

class Kitten : public ALA
{
public:
    Kitten() : ALA() { std::cout << "Kitten 构造" << std::endl; }
    virtual ~Kitten() { std::cout << "Kitten 析构" << std::endl; }
    virtual void processAdoption()
    {
        std::cout << "Process Kitten Adoption" << std::endl;
        //throw 1;
    }
};

ALA* create(int i)
{
    switch (i)
    {
    case 1:
        return new Puppy;
    case 2:
        return new Kitten;
    default:
        return nullptr;
    }
}

// 内存泄漏
void processAdoptions()
{
    for (int i = 1; i <= 2; ++i)
    {
        ALA* pa = create(i);
        pa->processAdoption();
        delete pa;
    }
}

// 无内存泄漏，但是很丑
void processAdoptions2()
{
    for (int i = 1; i <= 2; ++i)
    {
        ALA* pa = create(i);

        try
        {
            pa->processAdoption();
        }
        catch (int)
        {
            delete pa;
            throw;
        }
        delete pa;
    }
}

// 使用智能指针，无内存泄漏, 完美
void processAdoptions3()
{
    for (int i = 1; i <= 2; ++i)
    {
        std::unique_ptr<ALA> pa(create(i));
        pa->processAdoption();
    }
}

int main()
{
    try
    {
        //processAdoptions();
        //processAdoptions2();
        processAdoptions3();
    }
    catch(int e)
    {
        std::cout << "异常" << e << std::endl;
    }
    return 0;
}