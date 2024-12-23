cmake_minimum_required(VERSION 3.29)
project(decrypting)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp decrypt.cpp)
add_executable(test test.cpp decrypt.cpp)
