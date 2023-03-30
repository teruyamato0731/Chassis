#!/bin/bash
set -euxo pipefail
cd ${BASH_SOURCE[0]%/*}/..
git submodule update --init docs/doxygen-custom/doxygen-awesome-css
echo PROJECT_NUMBER set to ${PROJECT_VERSION:=$(git describe --tags --abbrev=0)}

# doxygen docs/doxygen-custom/Doxyfile
doxygen <(echo "PROJECT_NUMBER = ${PROJECT_VERSION}" | cat docs/doxygen-custom/Doxyfile -)

if [ -e "/.dockerenv" ]; then
cat << EOS

Open http://localhost:8000 in your browser.

EOS
fi
