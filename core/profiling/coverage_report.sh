#!/bin/bash

mkdir gcov
cd gcov
cp ../../CMakeFiles/core.dir/src/*.gcno .
cp ../../CMakeFiles/core.dir/src/*.gcda .

cp ../../testing/CMakeFiles/core_tests.dir/*.gcno .
cp ../../testing/CMakeFiles/core_tests.dir/*.gcda .

cd ..
geninfo --output-filename core-coverage.info gcov
genhtml -o coverage -t "vac-o core pacakge" core-coverage.info



