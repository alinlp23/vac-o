
if (RNAinverse)
    set(backends_testing_src RNAinverseTests.cpp)
endif (RNAinverse)

if (INFORNA)
    set(backends_testing_src ${backends_testing_src} INFORNATests.cpp)
endif (INFORNA)

if (RNAfold)
    set(backends_testing_src ${backends_testing_src} RNAFoldTests.cpp)
endif (RNAfold)

if (RNAforester)
    set(backends_testing_src ${backends_testing_src} RNAForesterTests.cpp)
endif (RNAforester)

if (Hamming)
    set(backends_testing_src ${backends_testing_src} HammingTests.cpp)
endif (Hamming)

add_executable(backends_tests ${backends_testing_src})
target_link_libraries (backends_tests RNAbackends biopp pthread gtest_main gmock)