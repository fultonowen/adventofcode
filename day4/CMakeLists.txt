cmake_minimum_required(VERSION 3.30)
project(day4)

set(CMAKE_CXX_STANDARD 20)
file(COPY input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(day4 main.cpp)
