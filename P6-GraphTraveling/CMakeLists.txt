cmake_minimum_required(VERSION 3.21)
project(P6_GraphTraveling)

set(CMAKE_CXX_STANDARD 17)

add_executable(P6_GraphTraveling main.cpp GraphManager.h myStack.h AdjacencyList.h MultipleAdjacencyList.h test.h)
