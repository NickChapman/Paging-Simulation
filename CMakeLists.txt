cmake_minimum_required(VERSION 3.5)
project(paging)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp PagingSimulation.cpp PagingSimulation.h PageTableEntry.cpp PageTableEntry.h FifoSimulation.cpp FifoSimulation.h)
add_executable(paging ${SOURCE_FILES})