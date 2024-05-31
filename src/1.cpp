#include <iostream>
#include <string>

// 指针和引用的不同:
// 1.指针使用* ->    引用使用.
// 2.指针可以为NULL  引用不可以   -> 1.引用必须有初值，指针可有可无(最好有初值) 2.引用无需判定NULL，指针需要判定
// 3.指针可以重新赋值 引用不可以

class Person
{
public:
    explicit Person(const std::string& name) : m_name(name) {}
    std::string m_name;
};

void print(const Person* person)
{
    // 因为指针可以为NULL，所以使用指针需要判定是不是NULL
    if (person)
    {
        std::cout << "Person[" << person->m_name << "]" << std::endl;
    }
    else
    {
        std::cout << "Person == NULL" << std::endl;
    }
}

void print(const Person& person)
{
    // 因为引用不可以为NULL，所以使用引用不需要判断NULL
    std::cout << "Person(" << person.m_name << ")" << std::endl;
}


int main()
{
    Person person1("Hello");

    Person person2("World");

    Person person3("XXXXXX");

    //Person& ref1;     // ERROR: 因为引用不可以为NULL，所以必须有初值

    Person& ref1 = person1; //OK 有初值
    print(ref1);        // ref1 = Hello
    print(person1);     // person1 = Hello

    person1 = person2;
    print(ref1);       // ref1 = World
    print(person1);    // person1 = World

    ref1 = person3;   // 无法改为对person3的引用，是把person3的值赋值给person1
    print(ref1);      // ref1 = XXXXXX
    print(person1);   // person1 = XXXXXX

    std::cout << "==========指针可以改变指向==========" << std::endl;
    Person* person4 = &person1;
    print(person4);   // person4 = Hello

    person4 = &person2;
    print(person4);   // person4 = World

    return 0;
}