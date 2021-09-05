cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_CXX_STANDARD 11)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -pedantic-errors -Werror")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${GCC_COVERAGE_COMPILE_FLAGS}" )



add_executable(lab1
        t1.cpp)
