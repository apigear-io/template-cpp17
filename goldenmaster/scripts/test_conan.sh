#!/bin/bash
set -x;

#
# function implementations
#
build_apigear()
{
    conan remove "apigear/*" -c
    ## create conan package in cache
    conan create ../apigear --build missing
    if [ $? -ne 0 ]; then exit 1; fi;
}

build_module()
{
    conan remove "$1/*" -c
    ## create conan package in cache
    conan create ../modules/$1/conan --build missing
    buildresult=$?
    if [ $buildresult -ne 0 ]; then exit 1; fi;
}

build_example()
{
    mkdir -p $1 &&\
    pushd $1 &&\
    cp -a ../../../$1/* . &&\
    conan install --build missing . -g=VirtualRunEnv &&\
    cmake -S . --preset conan-release &&\
    cmake --build .
    buildresult=$?
    popd
    if [ $buildresult -ne 0 ]; then exit 1; fi;
}

#
# main
#
export DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )/..";
cd $DIR;
rm -rf build/ && mkdir -p build && cd build;
if [ $? -ne 0 ]; then exit 1; fi;
build_apigear
# Building and testing Testbed2 module
build_module "testbed2"
# Building and testing TbEnum module
build_module "tb_enum"
# Building and testing TbSame1 module
build_module "tb_same1"
# Building and testing TbSame2 module
build_module "tb_same2"
# Building and testing TbSimple module
build_module "tb_simple"
# Building and testing Testbed1 module
build_module "testbed1"
# Building and testing TbNames module
build_module "tb_names"
# Building and testing CustomTypes module
build_module "custom_types"
# Building and testing ExternTypes module
build_module "extern_types"
# Building and testing Counter module
build_module "counter"
build_example "examples/app"
build_example "examples/appthreadsafe"
build_example "examples/olinkserver"
build_example "examples/olinkclient"
build_example "examples/mqttserver"
build_example "examples/mqttclient"
# leave build directory
cd ..
