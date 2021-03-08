#!/usr/bin/env bash

trap 'exit -1' err

if [ -d build ]; then rm -rf build; fi

BASE_PATH=$PWD

CMAKE_OPTS="-DBUILD_TESTS=ON"

mkdir -p build/release
pushd build/release
cmake -DCMAKE_BUILD_TYPE=Release $CMAKE_OPTS $BASE_PATH
popd

mkdir -p build/relwithdebinfo
pushd build/relwithdebinfo
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo $CMAKE_OPTS $BASE_PATH
popd

mkdir -p build/debug
pushd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug $CMAKE_OPTS $BASE_PATH
popd
