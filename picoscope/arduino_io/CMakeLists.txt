cmake_minimum_required(VERSION 2.6)
project(metroidvania)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(default_build_type "RelWithDebugInfo")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

INCLUDE(FindPkgConfig)
###############################################

# game
add_executable(arduino_io main.cpp tty_utils.cpp tty.cpp)
add_custom_command(TARGET arduino_io
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:arduino_io> ..)
