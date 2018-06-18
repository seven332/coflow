cmake_minimum_required(VERSION 2.6)
project(coflow)

set(CMAKE_CXX_STANDARD 11)
include_directories(coflow)
add_executable(coflow
        coflow/main.cpp
        coflow/Coflow.cpp
        coflow/Flow.cpp
        coflow/Generator.cpp
        coflow/Scheduler.cpp)
