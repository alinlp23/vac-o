cmake_minimum_required (VERSION 2.6)
project (vac-o)

option (USE_WEFFC++ "Use Weffc++ flag" OFF)

#common headers
include_directories(include)
set(CMAKE_CXX_FLAGS "-ansi -Wall -pedantic")

if (USE_WEFFC++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")
endif (USE_WEFFC++)

if (CMAKE_CXX_FLAGS_DEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3")
endif(CMAKE_CXX_FLAGS_DEBUG)

#RNAbakends library
add_subdirectory (RNAbackends)

#libplugin shared library
add_subdirectory (libplugin)

#framework core
add_subdirectory (core)

#main program
include_directories(core/include)
add_executable(vac-o core/src/main.cpp)

target_link_libraries (vac-o  core -lbiopp -ldl)

