cmake_minimum_required(VERSION 3.2)

project(AlgorithmicToolbox)

if (UNIX)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wno-unused-variable -pipe -O2 -std=c++14")
endif(UNIX)

add_subdirectory(Assignment1/fibonacci)
add_subdirectory(Assignment1/fibonacci_huge)
add_subdirectory(Assignment1/fibonacci_last_digit)
add_subdirectory(Assignment1/gcd)
add_subdirectory(Assignment1/lcm)
