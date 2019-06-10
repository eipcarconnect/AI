cmake_minimum_required(VERSION 3.13)
project(InputGen)

set(CMAKE_CXX_STANDARD 17)

add_executable(InputGen
        InputGen/main.cpp
        InputGen/InputGeneration.cpp
        InputGen/InputGeneration.hpp
        InputGen/Input.hpp)


project(AI)

add_executable(AI AI/AIMain.cpp AI/src/Connection.cpp AI/src/Connection.hpp AI/src/Node.cpp AI/src/Node.hpp AI/src/NeuralNetwork.cpp AI/src/NeuralNetwork.hpp AI/src/NeuralData.hpp)