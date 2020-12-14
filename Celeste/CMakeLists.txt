cmake_minimum_required(VERSION 3.17)
project(Celeste)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_library(Celeste src/Celeste.cpp include/Celeste.h)
target_precompile_headers(Celeste include/cpch.h)