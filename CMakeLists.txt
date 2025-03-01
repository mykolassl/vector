cmake_minimum_required(VERSION 3.25)
project(Vector)
set(CMAKE_CXX_STANDARD 20)

include_directories(libs)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)