cmake_minimum_required (VERSION 2.6)
project (vac-o)

#common headers
include_directories(include)

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

