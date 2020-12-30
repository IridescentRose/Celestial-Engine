cmake_minimum_required(VERSION 3.17)
project(Celeste-Test)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../Celeste lib/)
include_directories(../Celeste/include)
include_directories(../dep/fmt/include)
include_directories(../dep/eventpp/src)

add_definitions(-DBUILD_PLAT=BUILD_WINDOWS -DSFML_STATIC)

add_executable(Celeste-Test main.cpp main.cpp)
target_link_libraries(Celeste-Test Celeste)
target_link_directories(Celeste-Test PRIVATE ../dep/sfml/lib)