include_directories(include ../RNAbackends/include)
add_library(plugin SHARED   src/CombinatoryRegion.cpp
                            src/SSRegion.cpp
                            src/SequenceMutator.cpp
                            src/AllMutator.cpp
                            src/RandomMutator.cpp
                            src/QARegion.cpp                            
                            src/TripletsProductor.cpp
                            src/GCRegion.cpp
                            src/Solution.cpp
                            src/Strategy.cpp
                            src/FirstImprovement.cpp
                            src/Neighborhood.cpp
                            src/DevPlugin.cpp)
								
target_link_libraries (plugin RNAbackends)
