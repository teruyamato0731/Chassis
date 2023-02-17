cmake_minimum_required(VERSION 3.21)
# ctestをjunit形式で出力するため

# Parameters inside project
project(Chassis)

# Compiler option
# GoogleTest requirest C++11 or later
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library
add_library(Chassis INTERFACE)
target_include_directories(Chassis INTERFACE src)


# Add test module
option(BUILD_TESTS "BUILD_TESTS" ON)
if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
