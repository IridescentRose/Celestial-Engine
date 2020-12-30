cmake_minimum_required(VERSION 3.17)
project(Celeste)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(../dep/eventpp/src)
include_directories(../dep/sfml/include)

add_subdirectory(../dep/fmt build/)
add_definitions(-DBUILD_PLAT=BUILD_WINDOWS -DSFML_STATIC)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INC_FILES include/*.cpp)

add_library(Celeste STATIC ${SRC_FILES} ${INC_FILES})
target_precompile_headers(Celeste PRIVATE include/cpch.hpp)
target_link_libraries(Celeste PRIVATE fmt::fmt)
target_link_directories(Celeste PRIVATE ../dep/sfml/lib)
target_link_libraries(Celeste PRIVATE sfml-audio-s.lib sfml-system-s.lib winmm.lib openal32.lib flac.lib vorbisenc.lib vorbisfile.lib vorbis.lib ogg.lib)