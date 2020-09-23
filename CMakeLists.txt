cmake_minimum_required(VERSION 3.10) # optimistic

project(parser LANGUAGES CXX)

add_executable(parser src/main.cpp
                      src/Trie.cpp
                      src/Trie.hpp)

set(default_build_type "Debug")    
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message("Message: Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(parser PRIVATE $<$<CONFIG:RELEASE>:-O2>)
    target_compile_options(parser PRIVATE $<$<CONFIG:DEBUG>:-Wall;-Wextra;-Wpedantic>)
endif()

set_target_properties(parser PROPERTIES CXX_STANDARD 17
                                        CXX_STANDARD_REQUIRED on)