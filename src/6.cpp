#include <iostream>

int main()
{
    Array a = 5;

    int i = 1;

    std::cout << ++i << std::endl;

    std::cout << i << std::endl;

    std::cout << i++ << std::endl;

    std::cout << i << std::endl;

    std::cout << ++++i << std::endl;

    std::cout << i << std::endl;

    // std::cout << i++++ << std::endl;   // 错误:后置++ 返回常量 不能再++

    // std::cout << ++i++ << std::endl;   // 错误:默认先计算后置++  后置++ 返回常量 不能再++

    // std::cout << ++(i++) << std::endl; // 错误

    std::cout << (++i)++ << std::endl;





    return 0;
}