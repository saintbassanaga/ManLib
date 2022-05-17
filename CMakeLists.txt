cmake_minimum_required(VERSION 3.21)
project(LibMan_SYSTEM)

set(CMAKE_CXX_STANDARD 20)

add_executable(LibMan_System main.cpp Book.cpp Book.h _head_file.h Customer.cpp Customer.h Library.cpp Library.h IdGenerator/library.cpp IdGenerator/library.h )
