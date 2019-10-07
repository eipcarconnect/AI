cmake_minimum_required(VERSION 3.13)
project(InputGen)

set(CMAKE_CXX_STANDARD 17)

add_executable(InputGen
        InputGen/main.cpp
        InputGen/InputGeneration.cpp
        InputGen/InputGeneration.hpp
        InputGen/Input.hpp)


project(AI)
set(CMAKE_CXX_STANDARD 17)
add_executable(AI
        AI/AIMain.cpp
        AI/src/Connection.cpp
        AI/src/Connection.hpp
        AI/src/Node.cpp
        AI/src/Node.hpp
        AI/src/NeuralNetwork.cpp
        AI/src/NeuralNetwork.hpp
        AI/src/NeuralData.hpp)

project(Server)
set(CMAKE_CXX_STANDARD 17)

## Set qt for Server
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#find_package(Qt5Core REQUIRED PATHS "C:\\Qt\\5.13.0\\mingw73_32\\lib\\cmake")
#find_package(Qt5WebSockets REQUIRED PATHS "C:\\Qt\\5.13.0\\mingw73_32\\lib\\cmake")

add_executable(Server
        Server/ServerMain.cpp
        Server/server.cpp
        Server/server.h
        )

#target_link_libraries(Server Qt5::Core)
#target_link_libraries(Server Qt5::WebSockets)
