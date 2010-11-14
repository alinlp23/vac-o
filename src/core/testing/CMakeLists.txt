 set(core_testing_src   CombinatoryEngineTests.cpp
                        QAEngineTests.cpp
                        SequenceRankerTests.cpp
                        PluginAdminTests.cpp)

add_executable(core_tests ${core_testing_src})
target_link_libraries (core_tests core biopp dl pthread gtest_main gmock)

add_library(testing_right_plg SHARED   RightPlugin.cpp)
add_library(testing_wrong_plg SHARED   WrongPlugin.cpp)