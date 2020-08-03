cmake_minimum_required(VERSION 3.5.1)

# set the project name and version
project(timer_test VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -pthread" )

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB SOURCES *.cpp)

add_executable(timer_test ${SOURCES})

set(TIMER_DIR ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_subdirectory(test)
