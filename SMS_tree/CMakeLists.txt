cmake_minimum_required(VERSION 3.17)
project(SMS_tree)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(SMS_tree main.cpp tree.cpp tree.h student.cpp student.h files.cpp files.h course.cpp course.h)