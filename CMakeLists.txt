cmake_minimum_required(VERSION 3.14)
project(LongNumCmake VERSION 0.1.0 LANGUAGES C CXX)
project(LongNum_Cmake)

include_directories("include/")

set(SOURCE_EXE main.cpp)
set(SOURCE_LIB scr/longnum.cpp scr/picalculation.cpp)	

add_library(longnum ${SOURCE_LIB} include/longnum.h)

add_executable(main ${SOURCE_EXE})
target_link_libraries(main longnum)	

add_compile_options("-O2")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests test/tests.cpp)
target_link_libraries(tests longnum GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
