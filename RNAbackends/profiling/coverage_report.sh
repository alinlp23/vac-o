#!/bin/bash

mkdir gcov
cd gcov
cp ../../CMakeFiles/RNAbackends.dir/src/*.gcno .
cp ../../CMakeFiles/RNAbackends.dir/src/*.gcda .

cp ../../testing/CMakeFiles/backends_tests.dir/*.gcno .
cp ../../testing/CMakeFiles/backends_tests.dir/*.gcda .

cd ..
gcov ../src/*.cpp -o gcov
lcov --directory ./ --capture --output-file lcov_tmp.info -b ./
lcov --extract lcov_tmp.info "$HOME/*" --output-file backends-coverage.info
genhtml -o coverage -t "vac-o RNAbackends pacakge" backends-coverage.info
rm lcov_tmp.info backends-coverage.info
rm -fr gcov

