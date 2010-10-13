include_directories(include /usr/local/include/ViennaRNA)
add_library(RNAbackends src/Hamming.cpp
                        src/RNAFold.cpp
                        src/RNAFoldInverse.cpp
                        src/RNAForester.cpp
                        src/viennaRNA.c)
						
target_link_libraries (RNAbackends -lRNA)
		

