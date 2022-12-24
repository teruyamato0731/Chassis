cmake_minimum_required(VERSION 3.15)

# Parameters inside project
project(Chassis)

# Compiler option
# GoogleTest requirest C++11 or later
set(CMAKE_CXX_STANDARD 17)
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
