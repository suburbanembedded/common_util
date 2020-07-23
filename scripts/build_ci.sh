#!/usr/bin/env bash

trap 'exit -1' err

set -v

CONTAINER_ID=$(docker create -v $GITHUB_WORKSPACE:/tmp/workspace -it docker.pkg.github.com/suburbanembedded/common_util/common_util:${GITHUB_REF##*/}  /bin/bash)
docker start $CONTAINER_ID
docker exec -u $(id -u):$(id -g) -w /tmp/workspace/ $CONTAINER_ID ./generate_cmake.sh
docker exec -u $(id -u):$(id -g) -w /tmp/workspace/ $CONTAINER_ID make package -j`nproc` -C build/debug/
docker exec -u $(id -u):$(id -g) -w /tmp/workspace/ $CONTAINER_ID make package -j`nproc` -C build/release/
docker stop $CONTAINER_ID

pushd $GITHUB_WORKSPACE/build/debug/
sha256sum -b common_util-0.1.0-Linux.deb | tee sha256.txt
tar -czf $GITHUB_WORKSPACE/common_util-debug-$GITHUB_SHA.tar.gz    common_util-0.1.0-Linux.deb sha256.txt
popd

pushd $GITHUB_WORKSPACE/build/release/
sha256sum -b common_util-0.1.0-Linux.deb | tee sha256.txt
tar -czf $GITHUB_WORKSPACE/common_util-release-$GITHUB_SHA.tar.gz  common_util-0.1.0-Linux.deb sha256.txt
popd
