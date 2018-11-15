cmake_minimum_required (VERSION 2.6)
project (CollectTraces)

set(CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")
set(default_build_type "Release")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

include_directories("/opt/picoscope/include/")
link_directories("/opt/picoscope/lib")

add_executable(CollectTraces main.cpp pico.cpp tty.cpp tty_utils.cpp)
target_link_libraries(CollectTraces ps3000a)
