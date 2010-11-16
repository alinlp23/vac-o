#!/bin/bash

mkdir gcov
cd gcov
cp ../../CMakeFiles/plugin.dir/src/*.gcno .
cp ../../CMakeFiles/plugin.dir/src/*.gcda .

cp ../../testing/CMakeFiles/libplugin_tests.dir/*.gcno .
cp ../../testing/CMakeFiles/libplugin_tests.dir/*.gcda .

cd ..
geninfo --output-filename libplugin-coverage.info gcov
genhtml -o coverage -t "vac-o libplugin pacakge" libplugin-coverage.info



