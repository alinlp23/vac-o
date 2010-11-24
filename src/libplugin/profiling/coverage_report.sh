#!/bin/bash

mkdir gcov
cd gcov
cp ../../CMakeFiles/plugin.dir/src/*.gcno .
cp ../../CMakeFiles/plugin.dir/src/*.gcda .

cp ../../testing/CMakeFiles/libplugin_tests.dir/*.gcno .
cp ../../testing/CMakeFiles/libplugin_tests.dir/*.gcda .

cd ..
gcov ../src/*.cpp -o gcov
lcov --directory ./ --capture --output-file lcov_tmp.info -b ./
lcov --extract lcov_tmp.info "$HOME/*" --output-file libplugin-coverage.info
genhtml -o coverage -t "vac-o libplugin pacakge" libplugin-coverage.info
rm lcov_tmp.info libplugin-coverage.info
rm -fr gcov




