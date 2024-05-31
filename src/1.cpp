#include <iostream>

int main()
{
    // 

    int a = 0;

    //int& aref;     // ERROR: 

    int& aref = a;

    std::cout << "aref refence a:       aref = " << aref << " a = " << a << std::endl;

    a = 1;

    std::cout << "modify a to 1:        aref = " << aref << " a = " << a << std::endl;

    aref = 2;

    std::cout << "modify aref to 2:     aref = " << aref << " a = " << a << std::endl;



    return 0;
}