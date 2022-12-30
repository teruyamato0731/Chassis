cmake_minimum_required(VERSION 3.21)
# ctestをjunit形式で出力するため

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # 追加
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # 追加

add_subdirectory(third_party/googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(GoogleTest)

file(GLOB TEST_SOURCES ./*.cpp)
add_executable(unit_test ${TEST_SOURCES})
target_link_libraries(unit_test gtest_main Chassis)

gtest_discover_tests(unit_test)
