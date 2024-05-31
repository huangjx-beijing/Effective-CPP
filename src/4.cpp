#include <iostream>
#include <vector>

class Person
{
public:
    Person(const std::string& name) : m_name(name) {}
    virtual ~Person() {}
    std::string m_name;
};

class Student : public Person
{
public:
    Student(const std::string& name) : Person(name) {}
    virtual ~Student() {}
    int m_id;
};


int main()
{
    //1.数组问题
    
    // Person persons[10]; //没有默认构造函数，无法创建数组

    // a解决办法
    Person persons[] = {Person("1"), Person("2")};

    // b解决办法
    Person *personsPt[2];
    personsPt[0] = new Person("a");
    personsPt[1] = new Person("b");

    // c解决办法

    //2.模板容器问题
    std::vector<Person> personVec(2); //没有默认构造函数，无法创建vector

    //3.虚基类问题
}