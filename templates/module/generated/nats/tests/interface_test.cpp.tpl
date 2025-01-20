{{- $class := Camel .Interface.Name  }}
{{- $namespace := Camel .Module.Name   }}
{{- $natsclient := printf "%sClient" .Interface.Name }}
{{- $natsservice := printf "%sService" .Interface.Name }}
{{- $namespacePrefix := printf "%s::" (Camel .Module.Name) -}}
#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "{{snake .Module.Name}}/generated/core/test_struct_helper.h"
#include "{{snake .Module.Name}}/implementation/{{lower (camel .Interface.Name)}}.h"
#include "{{snake .Module.Name}}/generated/nats/{{lower (camel .Interface.Name)}}client.h"
#include "{{snake .Module.Name}}/generated/nats/{{lower (camel .Interface.Name)}}service.h"

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

#include "apigear/nats/natsclient.h"
#include "apigear/nats/natsservice.h"

{{- define "get_namespace"}}
        {{- $module_prefix:= printf "%s" (Camel .Module.Name) }}
        {{- if (ne .Import "") }}
        {{- $module_prefix = (Camel .Import ) }}
        {{- end}}
        {{- $module_prefix -}}
{{- end}}

// Those tests require an external nats server, interface adapters for both client and service object side, are clients from Nats protocol pov.
// Before running tests make sure that the server of your choice is running.

namespace{

    int timeout = 1000;//in ms
}
using namespace {{Camel .System.Name}};
using namespace {{Camel .System.Name}}::{{$namespace}};

TEST_CASE("Nats  {{.Module.Name}} {{$class}} tests")
{
    auto service = std::make_shared<ApiGear::Nats::Service>();

    auto client = std::make_shared<ApiGear::Nats::Client>();
    service->connect("nats://localhost:4222");
    client->connect("nats://localhost:4222");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);

    auto impl{{$class}} = std::make_shared<{{Camel .System.Name}}::{{$namespace}}::{{$class}}>();
    auto service{{$class}} = Nats::{{$natsservice}}::create(impl{{$class}}, service);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [service{{$class}}]() {return  service{{$class}}->_is_ready();}));
    lock.unlock();
    service->flush();

    auto client{{$class}} = Nats::{{$natsclient}}::create(client);
    lock.lock();
    REQUIRE(m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [client{{$class}}]() {return client{{$class}}->_is_ready(); }));
    lock.unlock();
    client->flush();
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
    SECTION("Test method {{.Name}} async with callback")
    {
        std::atomic<bool> finished = false;
        auto resultFuture = client{{$class}}->{{lower1 .Name }}Async(
    {{- range $idx, $p := .Params -}}
            {{- if $idx }}, {{end -}}
            {{ cppDefault $namespacePrefix .}}
    {{- end -}}
    {{- if (len .Params) }},{{end }}
            [&finished, &m_wait](
                {{- if (not .Return.IsVoid) -}}{{cppType "" .Return}} value)
            { 
            {{- if (eq .Return.KindType "extern") }} (void) value;// Make sure the comparison is valid for extern type.
            {{- else }}
                REQUIRE(value == {{ cppDefault $namespacePrefix .Return }});
            {{- end}}
            {{- else -}} )
            { {{ end }}
                finished = true;
                m_wait.notify_all();
                /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */
            });
        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();

        resultFuture.wait();
    }
    {{- end }}

    service{{$class}}.reset();
    client{{$class}}.reset();
    client->disconnect();
    service->disconnect();
    client.reset();
    service.reset();
}
