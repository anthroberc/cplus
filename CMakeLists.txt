cmake_minimum_required(VERSION 3.10)
project(cplus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(cplus
    src/main.cpp
    src/Lexer.cpp
    src/Parser.cpp
    src/Environment.cpp
    src/Interpreter.cpp
)
