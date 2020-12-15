cmake_minimum_required(VERSION 3.17)
project(Celeste)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(Celeste STATIC ${SRC_FILES})
target_precompile_headers(Celeste PRIVATE include/cpch.hpp)