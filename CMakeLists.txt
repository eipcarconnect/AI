cmake_minimum_required(VERSION 3.13)
project(ai)

set(CMAKE_CXX_STANDARD 17)

add_executable(ai main.cpp InputGeneration.cpp InputGeneration.hpp Input.hpp)