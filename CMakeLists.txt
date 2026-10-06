cmake_minimum_required(VERSION 4.3)
project(ASD CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} source/main.cpp
    source/bajtdocjaSafe.cpp
    source/binomialCoefficient.cpp

    source/factorial.cpp

    source/twoElementsSets.cpp
)