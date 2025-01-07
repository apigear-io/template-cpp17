{{- $class := Camel .Interface.Name  }}
{{- $namespace := Camel .Module.Name   }}
{{- $olinkclient := printf "%sClient" .Interface.Name }}
{{- $olinkservice := printf "%sService" .Interface.Name }}
{{- $namespacePrefix := printf "%s::" (Camel .Module.Name) -}}
#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "{{snake .Module.Name}}/generated/core/test_struct_helper.h"
#include "{{snake .Module.Name}}/implementation/{{lower (camel .Interface.Name)}}.h"
#include "{{snake .Module.Name}}/generated/olink/{{lower (camel .Interface.Name)}}client.h"
#include "{{snake .Module.Name}}/generated/olink/{{lower (camel .Interface.Name)}}service.h"

{{- $listcppExterns := cppExterns .Module.Externs}}
{{- $includes := (collectFields $listcppExterns  "Include")}}
{{- range .Module.Imports }}
{{- $includeName :=  printf "\"%s/generated/core/test_struct_helper.h\"" (snake .Name) }}
{{- $includes = (appendList $includes  $includeName) }}
{{- end }}
{{- $includes = unique $includes }}
{{ range $includes }}
#include {{ .}}
{{- end }}

#include "olink/clientregistry.h"
#include "olink/clientnode.h"
#include "olink/remotenode.h"
#include "olink/remoteregistry.h"

{{- define "get_namespace"}}
        {{- $module_prefix:= printf "%s" (Camel .Module.Name) }}
        {{- if (ne .Import "") }}
        {{- $module_prefix = (Camel .Import ) }}
        {{- end}}
        {{- $module_prefix -}}
{{- end}}

// Those tests do not use network connection.
// They are set in a way the client writes data straight into read function of server and vice versa.

namespace{

    int timeout = 1000;//in ms
}

using namespace {{Camel .System.Name}};
using namespace {{Camel .System.Name}}::{{$namespace}};

TEST_CASE("olink  {{.Module.Name}} {{$class}} tests")
{


    ApiGear::ObjectLink::ClientRegistry client_registry;
    auto clientNode = ApiGear::ObjectLink::ClientNode::create(client_registry);
    auto client{{$class}} = std::make_shared<{{Camel .System.Name}}::{{$namespace}}::olink::{{$olinkclient}}>();

    ApiGear::ObjectLink::RemoteRegistry remote_registry;
    auto remoteNode = ApiGear::ObjectLink::RemoteNode::createRemoteNode(remote_registry);
    auto impl{{$class}} = std::make_shared<{{Camel .System.Name}}::{{$namespace}}::{{$class}}>();
    auto service{{$class}} = std::make_shared<{{Camel .System.Name}}::{{$namespace}}::olink::{{$olinkservice}}>(impl{{$class}}, remote_registry);
    remote_registry.addSource(service{{$class}});

    remoteNode->onWrite([clientNode](std::string msg){clientNode->handleMessage(msg);});
    clientNode->onWrite([remoteNode](std::string msg){remoteNode->handleMessage(msg);});

    clientNode->registry().addSink(client{{$class}});
    clientNode->linkRemote(client{{$class}}->olinkObjectName());

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

  {{- range .Interface.Properties }}
    {{- if and (not .IsReadOnly) (not (eq .KindType "extern")) }}
    SECTION("Test setting {{.Name}}")
    {
        std::atomic<bool> is{{.Name}}Changed = false;
        client{{$class}}->_getPublisher().subscribeTo{{Camel .Name}}Changed(
        [&is{{.Name}}Changed, &m_wait ](auto value){
            is{{.Name}}Changed  = true;
            m_wait.notify_all();
        });
        {{- if .IsArray }}
        auto test_value = {{ cppDefault $namespacePrefix . }};
	    {{- if not ( or ( .IsPrimitive)  (eq .KindType "enum")) }}
        auto element = {{ cppTestValue $namespacePrefix . }};
        {{template "get_namespace" .}}::fillTest{{.Type }}(element);
        test_value.push_back(element);
        {{- else }}  
        test_value.push_back({{ cppTestValue $namespacePrefix .}});
        {{- end }}
	{{- else }}
        {{- if and (not .IsPrimitive) (not (eq .KindType "enum"))}}
        auto test_value = {{ cppDefault $namespacePrefix . }};
        {{template "get_namespace" .}}::fillTest{{.Type}}(test_value);
        {{- else}}
        auto test_value = {{ cppTestValue $namespacePrefix . }};
        {{- end }}
	{{- end }}
        client{{$class}}->set{{Camel .Name}}(test_value);;
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is{{.Name}}Changed]() {return is{{.Name}}Changed  == true; }));
        lock.unlock();
        REQUIRE(impl{{$class}}->get{{Camel .Name}}() == test_value);
        REQUIRE(client{{$class}}->get{{Camel .Name}}() == test_value);
    }
    {{- end }}
    {{- end }}

    {{- range .Interface.Signals }}
    SECTION("Test emit {{.Name}}")
    {
        std::atomic<bool> is{{.Name}}Emitted = false;

        {{- range $idx, $p := .Params -}}
        {{- if .IsArray }}
        auto local_{{snake .Name}}_array = {{ cppDefault $namespacePrefix . }};
        {{- if not ( or (eq .KindType "extern") ( or .IsPrimitive  (eq .KindType "enum") ) )}}
        auto element_{{$p.Name}} = {{ cppTestValue $namespacePrefix . }};
        {{template "get_namespace" .}}::fillTest{{.Type }}(element_{{$p.Name}});
        local_{{snake .Name}}_array.push_back(element_{{$p.Name}});
        {{- else }}
        local_{{snake .Name}}_array.push_back({{ cppTestValue $namespacePrefix . }});
        {{- end }}
        {{- else if not ( or (eq .KindType "extern") ( or .IsPrimitive  (eq .KindType "enum") ) )}}
        auto local_{{snake .Name}}_struct = {{ cppDefault $namespacePrefix . }};
        {{template "get_namespace" .}}::fillTest{{.Type }}(local_{{snake .Name}}_struct);
        {{- end -}}
        {{- end }}

        client{{$class}}->_getPublisher().subscribeTo{{Camel .Name}}(
        [&m_wait, &is{{.Name}}Emitted 
        {{- range $idx, $p := .Params -}}
        {{- if .IsArray }}, &local_{{snake .Name}}_array
        {{- else if not ( or (eq .KindType "extern") ( or .IsPrimitive  (eq .KindType "enum") ) ) }}, &local_{{snake .Name}}_struct{{- end -}}
        {{- end }}]({{cppParams $namespacePrefix .Params}})
        {
        {{- range $idx, $p := .Params }}
            REQUIRE({{ .Name}} == 
            {{- if .IsArray }} local_{{snake .Name}}_array
            {{- else if (eq .KindType "extern") }} {{ cppDefault $namespacePrefix .}}
            {{- else if  ( or .IsPrimitive  (eq .KindType "enum") ) }} {{ cppTestValue $namespacePrefix . }}
            {{- else -}} local_{{snake .Name}}_struct
            {{- end }});
        {{- end }}
            is{{.Name}}Emitted  = true;
            m_wait.notify_all();
        });

         impl{{$class}}->_getPublisher().publish{{Camel .Name}}(
    {{- range $idx, $p := .Params -}}
            {{- if $idx }}, {{end -}}
            {{- if .IsArray }}local_{{snake .Name}}_array
            {{- else if (eq .KindType "extern") }}{{ cppDefault $namespacePrefix .}}
            {{- else if  ( or .IsPrimitive  (eq .KindType "enum") ) }}{{ cppTestValue $namespacePrefix . }}
            {{- else -}}
            local_{{snake .Name}}_struct
            {{- end -}}
    {{- end -}}
        );
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is{{.Name}}Emitted ]() {return is{{.Name}}Emitted   == true; }));
        lock.unlock();
    }
    {{- end }}

    {{- range .Interface.Operations }}
    SECTION("Test method {{.Name}}")
    {
        {{ if (not .Return.IsVoid) }}[[maybe_unused]] auto result = {{ end }}client{{$class}}->{{lower1 .Name }}(
    {{- range $idx, $p := .Params -}}
            {{- if $idx }}, {{end -}}
            {{ cppDefault $namespacePrefix .}}
    {{- end -}}
        );
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    SECTION("Test method {{.Name}} async")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = client{{$class}}->{{lower1 .Name }}Async(
    {{- range $idx, $p := .Params -}}
            {{- if $idx }}, {{end -}}
            {{ cppDefault $namespacePrefix .}}
    {{- end -}}
        );
        auto f = std::async(std::launch::async, [&finished, &resultFuture, &m_wait]() {resultFuture.wait(); finished = true; m_wait.notify_all();});
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        {{- if (not .Return.IsVoid) }}
        auto return_value = resultFuture.get();
        {{ if (eq .Return.KindType "extern") }}//{{ end }}REQUIRE(return_value == {{ cppDefault $namespacePrefix .Return }}); {{ if (eq .Return.KindType "extern") }}// Make sure the comparison is valid for extern type. {{ end }}
        {{- else }}
        resultFuture.wait();
        {{- end }}
        // CHECK EFFECTS OF YOUR METHOD HERE
    }
    {{- end }}

    clientNode->unlinkRemote(client{{$class}}->olinkObjectName());
    remote_registry.removeSource(service{{$class}}->olinkObjectName());
    client_registry.removeSink(client{{$class}}->olinkObjectName());
    service{{$class}}.reset();
    client{{$class}}.reset();
}
