cmake_minimum_required(VERSION 3.10)
project(HyperLogLogLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(HyperLogLogLab ${SOURCES})

install(TARGETS HyperLogLogLab DESTINATION bin)