cmake_minimum_required(VERSION 3.16.3)

project(hello)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_EXTENSIONS OFF)

include_directories(${/root/.jenkins/workspace/now/Poco})

add_executable(hii Can_main.cpp)  

