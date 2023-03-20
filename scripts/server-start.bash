#!/bin/bash
set -euxo pipefail
cd ${BASH_SOURCE[0]%/*}/..
mkdir -p docs/html && cd "$_"
python3 -m http.server 8000
