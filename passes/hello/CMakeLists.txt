add_library(HelloPass MODULE
    Hello.cpp
)

# Use C++11 to compile our pass (i.e., supply -std=c++11).
#target_compile_features(HelloPass PRIVATE cxx_range_for cxx_auto_type)
set(CMAKE_CXX_STANDARD 14)

# LLVM is (typically) built with no C++ RTTI. We need to match that;
# otherwise, we'll get linker errors about missing RTTI data.
set_target_properties(HelloPass PROPERTIES
    COMPILE_FLAGS "-fno-rtti"
)
