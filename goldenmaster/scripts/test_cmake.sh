#!/bin/bash
set -x;
export source_root="$( cd "$( dirname "${BASH_SOURCE[0]}" )/../" >/dev/null 2>&1 && pwd )";
echo source root is in $source_root

#
# function implementations
#

# build cmake module
buildCMakeModule()
{
    cmake -B"$2/build_cmake/$1" -DCMAKE_CTEST_ARGUMENTS="--output-on-failure" -DCMAKE_PREFIX_PATH="$2/tmp/" -DCMAKE_CXX_FLAGS="-L/$2/tmp/lib" -DCMAKE_BUILD_RPATH="$2/tmp/lib" -DCMAKE_BUILD_WITH_INSTALL_RPATH=FALSE -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=TRUE -DCMAKE_INSTALL_PREFIX="$2/tmp" "-DCMAKE_INSTALL_RPATH=$2/tmp/lib" -DBUILD_TESTING=ON $3 -S"$2/$1" && cmake --build "$2/build_cmake/$1" && cmake --build "$2/build_cmake/$1" --target test && cmake --build "$2/build_cmake/$1" --target install
    buildresult=$?
}

# build cmake binary
buildCMakeBinary()
{
    cmake -B"$2/build_cmake/$1" -DCMAKE_CTEST_ARGUMENTS="--output-on-failure" -DCMAKE_PREFIX_PATH="$2/tmp/" -DCMAKE_CXX_FLAGS="-L/$2/tmp/lib" -DCMAKE_BUILD_RPATH="$2/tmp/lib" -DCMAKE_BUILD_WITH_INSTALL_RPATH=FALSE -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=TRUE -DCMAKE_INSTALL_PREFIX="$2/tmp"  "-DCMAKE_INSTALL_RPATH=$2/tmp/lib" $3 -S"$2/$1" && cmake --build "$2/build_cmake/$1" && cmake --build "$2/build_cmake/$1" --target install
    buildresult=$?
}

cd $source_root;
rm -rf tmp/ && rm -rf build_cmake/ && mkdir -p build_cmake;
if [ $? -ne 0 ]; then exit 1; fi;
git clone --depth 1 --branch v0.2.9 https://github.com/apigear-io/objectlink-core-cpp.git build_cmake/objectlink-core-cpp
if [ $? -ne 0 ]; then exit 1; fi;
buildCMakeModule "build_cmake/objectlink-core-cpp" $source_root
if [ $? -ne 0 ]; then exit 1; fi;
buildCMakeModule "apigear" $source_root "-DAPIGEAR_BUILD_WITH_OLINK=ON -DAPIGEAR_BUILD_WITH_MONITOR=ON -DAPIGEAR_BUILD_WITH_MQTT=ON -DAPIGEAR_BUILD_WITH_NATS=ON "
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/testbed2" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/tb_enum" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/tb_same1" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/tb_same2" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/tb_simple" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/testbed1" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/tb_names" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/custom_types" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/extern_types" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeModule "modules/counter" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
# examples app
buildCMakeBinary "examples/app" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
# examples appthreadsafe
buildCMakeBinary "examples/appthreadsafe" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeBinary "examples/olinkserver" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeBinary "examples/olinkclient" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeBinary "examples/mqttserver" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeBinary "examples/mqttclient" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeBinary "examples/natsserver" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;
buildCMakeBinary "examples/natsclient" $source_root
if [ $buildresult -ne 0 ]; then exit 1; fi;