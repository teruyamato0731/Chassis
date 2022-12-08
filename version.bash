#!/bin/bash
version=`git describe --tags`
version=${version:1}
sed -i '/version/d' library.properties library.json
sed -i -e "2i version=$version" library.properties
sed -i -e "3i \  \"version\": \"$version\"," library.json
