#!/bin/bash
mkdir -p build && cd "$_"
cmake ..
cmake --build . --target all --clean-first -j4
ctest --rerun-failed --output-on-failure -j4 --output-junit report.xml
# gcovr --xml -o coverage.xml -e ".*test.*" -r ../
