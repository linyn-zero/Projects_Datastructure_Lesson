cmake_minimum_required(VERSION 3.21)
project(TextAnalysisTools)

set(CMAKE_CXX_STANDARD 14)

add_executable(TextAnalysisTools main.cpp TextAnalyst.cpp TextAnalyst.h)
