cmake_minimum_required(VERSION 3.16)
project(DynamicCache)

set(CMAKE_CXX_STANDARD 14)

add_executable(DynamicCache main.cpp Mylist.cpp Mylist.h MyLRU.cpp MyLRU.h MyLFU.cpp MyLFU.h)