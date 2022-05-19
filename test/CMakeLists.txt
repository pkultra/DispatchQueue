cmake_minimum_required(VERSION 3.8)
project(runTests)

set (CMAKE_CXX_STANDARD 20)

# Locate GTest
find_package(GTest REQUIRED)

# Set source files and headers

set(SRCPATH ../src)
set(INCLPATH ../include)
include_directories(${GTEST_INCLUDE_DIRS} ${INCLPATH})
file(GLOB SOURCES ${SRCPATH}/*.cpp)
file(GLOB TESTSRCS ./*.cpp)

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests ${TESTSRCS} ${SOURCES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
