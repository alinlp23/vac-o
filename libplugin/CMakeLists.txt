include_directories(include ../RNAbackends/include)
add_library(plugin SHARED	src/CombinatoryRegion.cpp
							src/SSRegion.cpp
							src/DevPlugin.cpp)
								
target_link_libraries (plugin RNAbackends)
