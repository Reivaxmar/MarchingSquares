#!/bin/bash

BUILD_SFML_ARG=""

for arg in "$@"; do
  if [ "$arg" == "--sfml-src" ]; then
    BUILD_SFML_ARG="-DBUILD_SFML_FROM_SOURCE=ON"
  fi
done

cmake -B build . $BUILD_SFML_ARG
cmake --build build
