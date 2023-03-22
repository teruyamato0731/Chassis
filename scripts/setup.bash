#!/bin/bash
set -euxo pipefail
cd ${BASH_SOURCE[0]%/*}/..
git config commit.template .commit_template
