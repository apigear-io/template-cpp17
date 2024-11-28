{{- $features := .Features -}}
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

{{- if $features.apigear }}
build_apigear
{{- end}}

{{- range .System.Modules }}
# Building and testing {{Camel .Name}} module
build_module "{{ snake .Name }}"
{{- end }}

{{- if $features.examples }}
build_example "examples/app"
build_example "examples/appthreadsafe"
{{- end}}

{{- if $features.examples_olink }}
build_example "examples/olinkserver"
build_example "examples/olinkclient"
{{- end}}

{{- if $features.examples_mqtt }}
build_example "examples/mqttserver"
build_example "examples/mqttclient"
{{- end}}

{{- if $features.examples_nats }}
build_example "examples/natsserver"
build_example "examples/natsclient"
{{- end}}
# leave build directory
cd ..
