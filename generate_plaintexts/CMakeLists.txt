cmake_minimum_required(VERSION 2.6)
project(GeneratePlaintexts)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(default_build_type "RelWithDebugInfo")
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

###############################################

find_package( Boost REQUIRED COMPONENTS program_options )
if(Boost_FOUND)
  include_directories( ${Boost_INCLUDE_DIRS} )
  message("Found boost include directory add ${Boost_INCLUDE_DIRS}")
else()
  message(FATAL_ERROR "Could not find Boost")
endif()

add_executable(generate_plaintexts main.cpp)
