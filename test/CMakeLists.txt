cmake_minimum_required(VERSION 3.21)
# ctestをjunit形式で出力するため

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage") # 追加
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage") # 追加

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

file(GLOB TEST_SOURCES ./*.cpp)
add_executable(unit_test ${TEST_SOURCES})
target_link_libraries(unit_test gtest_main Chassis)

gtest_discover_tests(unit_test)
