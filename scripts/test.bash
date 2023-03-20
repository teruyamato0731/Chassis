#!/bin/bash
set -euxo pipefail
cd ${BASH_SOURCE[0]%/*}/..
mkdir -p build && cd "$_"
rm CMakeCache.txt || true
cmake ..
cmake --build . --target all --clean-first -j4
ctest --rerun-failed --output-on-failure -j4 --output-junit report.xml
