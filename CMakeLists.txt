cmake_minimum_required(VERSION 3.25)
project(raytracer_cpp)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

# External dependency
SET(STB_HEADER_PATH c:/dev/external/stb) # https://github.com/nothings/stb
target_include_directories(raytracer_cpp PRIVATE c:/dev/external/stb)
