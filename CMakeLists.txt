cmake_minimum_required(VERSION 3.5)
project(paging)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp PagingSimulation.cpp PagingSimulation.h PageTableEntry.cpp PageTableEntry.h FifoSimulation.cpp FifoSimulation.h GlobalClockSimulation.cpp GlobalClockSimulation.h LruSimulation.cpp LruSimulation.h RandomSimulation.cpp RandomSimulation.h LfuSimulation.cpp LfuSimulation.h OwnSimulation.cpp OwnSimulation.h)
add_executable(nlc35.exe ${SOURCE_FILES})