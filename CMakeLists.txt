cmake_minimum_required(VERSION 3.8)
project(DispatchQueue)
set (CMAKE_CXX_STANDARD 20)

# Set source files and headers

set(SRCPATH ./src)
set(INCLPATH ./include)
include_directories(${INCLPATH})
file(GLOB SOURCES ${SRCPATH}/*.cpp)

add_executable(DispatchQueue main.cpp ${SOURCES})
target_link_libraries(DispatchQueue pthread)
