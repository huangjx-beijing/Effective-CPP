cmake_minimum_required(VERSION 3.5)

project(CPP C CXX)

add_executable(MECPP-1 src/1.cpp)

add_executable(MECPP-3 src/3.cpp)

add_executable(MECPP-4 src/4.cpp)

add_executable(MECPP-5 src/5.cpp)

add_executable(MECPP-6 src/6.cpp)

##########异常
# 9.利用析构函数避免泄漏资源
add_executable(MECPP-9 src/9.cpp)