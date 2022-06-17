cmake_minimum_required(VERSION 3.21)

project(ManLib)

set(CMAKE_CXX_STANDARD 20)

add_executable(ManLib main.cpp Book/Book.cpp Book/Book.h Customer/Customer.cpp Customer/Customer.h)