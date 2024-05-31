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

std::ostream& print(std::ostream& os, const Person* person)
{
    // 因为指针可以为NULL，所以使用指针需要判定是不是NULL
    if (person)
    {
        return os << "Person[" << person->m_name << "]" << std::endl;
    }
    else
    {
        return os << "Person == NULL" << std::endl;
    }
}

std::ostream& print(std::ostream& os, const Person& person)
{
    // 因为引用不可以为NULL，所以使用引用不需要判断NULL 
    return os << "Person(" << person.m_name << ")" << std::endl;
}


int main()
{
    Person person1("More");

    Person person2("Effective");

    Person person3("C++");

    //Person& ref1;     // ERROR: 因为引用不可以为NULL，所以必须有初值

    Person& ref1 = person1;    //OK 有初值
    print(std::cout << "init! ref1 reference person1: ref1 = ", ref1);        // ref1 = More
    print(std::cout << "init! ref1 reference person1: person1 = ", person1);  // person1 = More

    person1 = person2;
    print(std::cout << "ref1 reference person1, but person2 assign to person1, ref1 = ", ref1);      // ref1 = Effective
    print(std::cout << "ref1 reference person1, but person2 assign to person1, person1 = ", person1);   // person1 = Effective

    ref1 = person3;   // 无法改为对person3的引用，是把person3的值赋值给person1
    print(std::cout << "ref1 reference person1, but person3 assign to ref1, ref1 = ", ref1);         // ref1 = C++
    print(std::cout << "ref1 reference person1, but person3 assign to ref1, person1 = ", person1);   // person1 = C++

    std::cout << "==========指针可以改变指向==========" << std::endl;
    Person* person4 = &person1;
    print(std::cout << "person4 point to person1, person4 = ", person4);   // person4 -> person1

    person4 = &person2;
    print(std::cout << "person4 point to person2, person4 = ", person4);   // person4 -> person2

    Person* p = NULL;
    Person& pref = *p;
    print(std::cout << "no no no", pref);

    return 0;
}