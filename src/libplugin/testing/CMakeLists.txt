 set(libplugin_testing_src      SequenceMutatorTests.cpp
                                TripletsProductorTests.cpp
                                SSRegionTests.cpp)

add_executable(libplugin_tests ${libplugin_testing_src})
target_link_libraries (libplugin_tests plugin biopp pthread gtest_main gmock)
