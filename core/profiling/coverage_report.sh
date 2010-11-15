#!/bin/bash

mkdir gcov
cd gcov
cp ../../CMakeFiles/core.dir/src/*.gcno .
cp ../../CMakeFiles/core.dir/src/*.gcda .

gcov -o CombinatoryEngine.cpp.gcno ../../src/CombinatoryEngine.cpp
gcov -o QAEngine.cpp.gcno ../../src/QAEngine.cpp
gcov -o PluginAdmin.cpp.gcno ../../src/PluginAdmin.cpp
gcov -o SequenceRanker.cpp.gcno ../../src/SequenceRanker.cpp
gcov -o SequenceOptimization.cpp.gcno ../../src/SequenceOptimization.cpp

cd ..
geninfo --output-filename core-coverage.info gcov
genhtml -o coverage -t "vac-o core pacakge" core-coverage.info



