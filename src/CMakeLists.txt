cmake_minimum_required(VERSION 2.8.4)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp fft.cpp hash.cpp util.cpp)
add_executable(percephash ${SOURCE_FILES})