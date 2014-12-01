cmake_minimum_required(VERSION 2.8.4)
project(src)

find_package(OpenMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${OpenMP_CXX_FLAGS}")
set(SOURCE_FILES main.cpp fft/serialfft.cpp fft/parallelfft.cpp hash/hash.cpp fft/util.cpp bmp/bmpProcess.cpp bmp/easyBMP/easyBMP.cpp)
add_executable(percephash ${SOURCE_FILES})