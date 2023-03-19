#!/bin/bash
cd ${BASH_SOURCE[0]%/*}/..

echo PROJECT_NUMBER set to ${PROJECT_VERSION:=$(git describe --tags --abbrev=0)}

# doxygen docs/doxygen-custom/Doxyfile
doxygen <(echo "PROJECT_NUMBER = ${PROJECT_VERSION}" | cat docs/doxygen-custom/Doxyfile -)
