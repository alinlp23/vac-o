#!/bin/bash

mkdir gcov
cd gcov
cp ../../CMakeFiles/core.dir/src/*.gcno .
cp ../../CMakeFiles/core.dir/src/*.gcda .

cp ../../testing/CMakeFiles/core_tests.dir/*.gcno .
cp ../../testing/CMakeFiles/core_tests.dir/*.gcda .

cd ..
gcov ../src/*.cpp -o gcov
lcov --directory ./ --capture --output-file lcov_tmp.info -b ./
lcov --extract lcov_tmp.info "$HOME/*" --output-file core-coverage.info
genhtml -o coverage -t "vac-o core pacakge" core-coverage.info
rm lcov_tmp.info core-coverage.info
rm -fr gcov


