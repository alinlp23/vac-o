project (RNAbackends)
include_directories(include)
set (RNABackends_SRC    src/RNABackendProxy.cpp
                        src/SecStructure.cpp
                        src/RNAStartInverse.cpp)

option (RNAinverse "Compile RNAinverse backend" ON)
option (INFORNA "Compile INFORNA backend" ON)
option (RNAfold "Compile RNAfold backend" ON)
option (RNAforester "Compile RNAforester backend" ON)
option (Hamming "Compile Hamming backend" ON)

if (RNAinverse)
    find_program(RNAinverse_PROG RNAinverse)
    if (RNAinverse_PROG)
        set (RNABackends_SRC ${RNABackends_SRC} src/RNAinverse.cpp)
    else (RNAinverse_PROG)
        message (FATAL_ERROR "You must install RNAinverse")
    endif (RNAinverse_PROG)

    if (COMPILE_TESTS)
        set(RNAinverse_PROG ${RNAbackends_SOURCE_DIR}/testing/RNAinverse.sh)
    endif (COMPILE_TESTS)
endif (RNAinverse)

if (INFORNA)
    find_program(INFORNA_PROG INFO-RNA-2.1)
    if (INFORNA_PROG)
        set (RNABackends_SRC ${RNABackends_SRC} src/INFORNA.cpp)
    else (INFORNA_PROG)
        message (FATAL_ERROR "You must install INFO-RNA")
    endif (INFORNA_PROG)

    if (COMPILE_TESTS)
        set(INFORNA_PROG ${RNAbackends_SOURCE_DIR}/testing/INFORNA.sh)
    endif (COMPILE_TESTS)
endif (INFORNA)

if (RNAfold)
    find_program(RNAfold_PROG RNAfold)
    if (RNAfold_PROG)
        set (RNABackends_SRC ${RNABackends_SRC} src/RNAFold.cpp)
    else (RNAfold_PROG)
        message (FATAL_ERROR "You must install RNAfold")
    endif (RNAfold_PROG)

    if (COMPILE_TESTS)
        set(RNAfold_PROG ${RNAbackends_SOURCE_DIR}/testing/RNAfold.sh)
    endif (COMPILE_TESTS)
endif (RNAfold)

if (RNAforester)
    find_program(RNAforester_PROG RNAforester)
    if (RNAforester_PROG)
        set (RNABackends_SRC ${RNABackends_SRC} src/RNAForester.cpp)
    else (RNAforester_PROG)
        message (FATAL_ERROR "You must install RNAforester")
    endif (RNAforester_PROG)

    if (COMPILE_TESTS)
        set(RNAforester_PROG ${RNAbackends_SOURCE_DIR}/testing/RNAforester.sh)
    endif (COMPILE_TESTS)
endif (RNAforester)

if (Hamming)
    set (RNABackends_SRC ${RNABackends_SRC} src/Hamming.cpp)
endif (Hamming)

configure_file (
  "include/RNABackendsConfig.h.in"
  "include/RNABackendsConfig.h"
)

add_library(RNAbackends ${RNABackends_SRC})

if (COMPILE_TESTS)
    add_subdirectory (testing)
endif (COMPILE_TESTS)