include_directories(include /usr/local/include/ViennaRNA)
add_library(RNAbackends src/RNABackendProxy.cpp
                        src/Hamming.cpp
                        src/RNAFold.cpp
                        src/RNAStartInverse.cpp
                        src/RNAinverse.cpp
                        src/INFORNA.cpp
                        src/RNAForester.cpp
                        src/viennaRNA.c)
						
target_link_libraries (RNAbackends -lRNA)
		

