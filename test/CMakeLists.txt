cmake_minimum_required(VERSION 3.21)
# ctestをjunit形式で出力するため

add_subdirectory(third_party/googletest)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
include(GoogleTest)

file(GLOB TEST_SOURCES ./*.cpp)
add_executable(unit_test ${TEST_SOURCES})
target_link_libraries(unit_test gtest_main Chassis)

gtest_discover_tests(unit_test)
