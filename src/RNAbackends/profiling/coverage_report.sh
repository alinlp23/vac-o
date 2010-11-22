#!/bin/bash

mkdir gcov
cd gcov
cp ../../CMakeFiles/RNAbackends.dir/src/*.gcno .
cp ../../CMakeFiles/RNAbackends.dir/src/*.gcda .

cp ../../testing/CMakeFiles/backends_tests.dir/*.gcno .
cp ../../testing/CMakeFiles/backends_tests.dir/*.gcda .

cd ..
geninfo --output-filename backends-coverage.info gcov
genhtml -o coverage -t "vac-o RNAbackends pacakge" backends-coverage.info



