cmake_minimum_required (VERSION 2.6)
project (Pico)

set(CMAKE_CXX_FLAGS "-g -std=c++17 -Wall -Wextra")
set(default_build_type "Release")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include_directories("/opt/picoscope/include/")
link_directories("/opt/picoscope/lib")

add_executable(Pico main.cpp pico.cpp)
target_link_libraries(Pico ps3000a)
