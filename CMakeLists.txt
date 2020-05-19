cmake_minimum_required(VERSION 3.13)

project(InputGen)
set(CMAKE_CXX_STANDARD 17)
add_executable(InputGen
        InputGen_src/main.cpp
        InputGen_src/InputGeneration.cpp
        InputGen_src/InputGeneration.hpp
        InputGen_src/Input.hpp)


project(AI)
set(CMAKE_CXX_STANDARD 17)
add_executable(AI
        AI_src/AIMain.cpp
        AI_src/generation.cpp
        AI_src/generation.h
        AI_src/src/Connection.cpp
        AI_src/src/Connection.hpp
        AI_src/src/Node.cpp
        AI_src/src/Node.hpp
        AI_src/src/NeuralNetwork.cpp
        AI_src/src/NeuralNetwork.hpp
        AI_src/src/NeuralData.hpp)

project(Server)
set(CMAKE_CXX_STANDARD 17)

## Set qt for Server
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

#find_package(Qt5Core REQUIRED PATHS "C:\\Qt\\5.13.0\\mingw73_32\\lib\\cmake")
find_package(Qt5Core REQUIRED PATHS "/home/seb/Qt/5.13.1/gcc_64/lib/cmake")
#find_package(Qt5WebSockets REQUIRED PATHS "C:\\Qt\\5.13.0\\mingw73_32\\lib\\cmake")
find_package(Qt5WebSockets REQUIRED PATHS "/home/seb/Qt/5.13.1/gcc_64/lib/cmake")

find_package(Boost REQUIRED system)
find_package(cpprestsdk REQUIRED PATHS "/usr/lib/x86_64-linux-gnu/cmake")

add_executable(Server
        Server_src/ServerMain.cpp
        Server_src/server.cpp
        Server_src/server.h
        )

target_link_libraries(Server Qt5::Core)
target_link_libraries(Server Qt5::WebSockets)
target_link_libraries(AI Qt5::Core)
target_link_libraries(AI Qt5::WebSockets)

project(ANN_API)
set(CMAKE_CXX_STANDARD 17)

add_executable(ANN_API
        ANN_API_src/APIMain.cpp ANN_API_src/API.cpp ANN_API_src/API.hpp
        AI_src/src/Connection.cpp
        AI_src/src/Connection.hpp
        AI_src/src/Node.cpp
        AI_src/src/Node.hpp
        AI_src/src/NeuralNetwork.cpp
        AI_src/src/NeuralNetwork.hpp
        AI_src/src/NeuralData.hpp Helper/Config.hpp)

target_link_libraries(ANN_API PRIVATE cpprestsdk::cpprest ${Boost_SYSTEM_LIBRARY})