#!/usr/bin/env bash

trap 'exit -1' err

if [ -d build ]; then rm -rf build; fi

BASE_PATH=$PWD

CMAKE_OPTS="-DBUILD_TESTS=OFF"

mkdir -p build/ram/release
pushd build/ram/release
cmake -DCMAKE_BUILD_TYPE=Release $CMAKE_OPTS $BASE_PATH
popd

mkdir -p build/ram/relwithdebinfo
pushd build/ram/relwithdebinfo
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo $CMAKE_OPTS $BASE_PATH
popd

mkdir -p build/ram/debug
pushd build/ram/debug
cmake -DCMAKE_BUILD_TYPE=Debug $CMAKE_OPTS $BASE_PATH
popd
