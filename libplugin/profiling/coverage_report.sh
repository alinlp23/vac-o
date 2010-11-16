#!/bin/bash

mkdir gcov
cd gcov
cp ../../CMakeFiles/plugin.dir/src/*.gcno .
cp ../../CMakeFiles/plugin.dir/src/*.gcda .

gcov -o SequenceMutator.cpp.gcno ../../src/SequenceMutator.cpp
gcov -o TripletsProductor.cpp.gcno ../../src/TripletsProductor.cpp
gcov -o SSRegion.cpp.gcno ../../src/SSRegion.cpp

cd ..
geninfo --output-filename libplugin-coverage.info gcov
genhtml -o coverage -t "vac-o libplugin pacakge" libplugin-coverage.info



