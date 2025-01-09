{{- $class := Camel .Interface.Name  }}
{{- $namespace := Camel .Module.Name   }}
{{- $mqttclient := printf "%sClient" .Interface.Name }}
{{- $mqttservice := printf "%sService" .Interface.Name }}
{{- $namespacePrefix := printf "%s::" (Camel .Module.Name) -}}
#pragma warning (disable: 4251)
#pragma warning (disable: 4099)

#include <catch2/catch.hpp>
#include <condition_variable>


#include "{{snake .Module.Name}}/generated/core/test_struct_helper.h"
#include "{{snake .Module.Name}}/implementation/{{lower (camel .Interface.Name)}}.h"
#include "{{snake .Module.Name}}/generated/mqtt/{{lower (camel .Interface.Name)}}client.h"
#include "{{snake .Module.Name}}/generated/mqtt/{{lower (camel .Interface.Name)}}service.h"

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

#include "apigear/mqtt/mqttclient.h"
#include "apigear/mqtt/mqttservice.h"

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

    int timeout = 2000;//in ms
}

using namespace {{Camel .System.Name}};
using namespace {{Camel .System.Name}}::{{$namespace}};

TEST_CASE("mqtt  {{.Module.Name}} {{$class}} tests")
{
    auto mqttservice = std::make_shared<ApiGear::MQTT::Service>("{{$class}}testServer");
    auto mqttclient = std::make_shared<ApiGear::MQTT::Client>("{{$class}}testClient");

    auto client{{$class}} = std::make_shared<{{Camel .System.Name}}::{{Camel .Module.Name}}::MQTT::{{$mqttclient}}>(mqttclient);
    auto impl{{$class}}= std::make_shared<{{Camel .System.Name}}::{{ Camel .Module.Name }}::{{$class}}>();
    auto service{{$class}} = std::make_shared<{{Camel .System.Name}}::{{Camel .Module.Name}}::MQTT::{{$mqttservice}}>(impl{{$class}}, mqttservice);

    mqttservice->connectToHost("");
    mqttclient->connectToHost("");

    std::condition_variable m_wait;
    std::mutex m_waitMutex;
    std::unique_lock<std::mutex> lock(m_waitMutex, std::defer_lock);


    std::atomic<bool> is_serviceConnected{ false };
    auto service_connected_id = service{{$class}}->_subscribeForIsReady([&is_serviceConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_serviceConnected = true;
                m_wait.notify_all();
            }
        });
    if (service{{$class}}->_is_ready() == true)
    {
        is_serviceConnected = true;
        m_wait.notify_all();
    }
    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_serviceConnected]() { return is_serviceConnected == true; });
    lock.unlock();
    REQUIRE(is_serviceConnected);
 
    std::atomic<bool> is_clientConnected{ false };
    client{{$class}}->_subscribeForIsReady([&is_clientConnected, &m_wait](auto connected)
        {
            if (connected)
            {
                is_clientConnected = true;
                m_wait.notify_all();
            }
        });

    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&is_clientConnected]() {return is_clientConnected  == true; });
    lock.unlock();
    REQUIRE(is_clientConnected);


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
        {{ if (not .Return.IsVoid) }}[[maybe_unused]] auto result = {{ end }} client{{$class}}->{{lower1 .Name }}(
    {{- range $idx, $p := .Params -}}
            {{- if $idx }}, {{end -}}
            {{ cppDefault $namespacePrefix .}}
    {{- end -}}
        );
        // CHECK EFFECTS OF YOUR METHOD AFER FUTURE IS DONE
    }
    SECTION("Test method {{.Name}} async")
    {
        {{- if (not .Return.IsVoid) }}
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
        auto return_value = resultFuture.get();
        {{ if (eq .Return.KindType "extern") }}//{{ end }}REQUIRE(return_value == {{ cppDefault $namespacePrefix .Return }}); {{ if (eq .Return.KindType "extern") }}// Make sure the comparison is valid for extern type. {{ end }}
        // CHECK EFFECTS OF YOUR METHOD HERE
        {{- else }}
        auto resultFuture = client{{$class}}->{{lower1 .Name }}Async(
    {{- range $idx, $p := .Params -}}
            {{- if $idx }}, {{end -}}
            {{ cppDefault $namespacePrefix .}}
    {{- end -}}
        );
        // The void function only sends request. It does not wait for the actual function on server side to be finished.
        {{- end}}
    }

    SECTION("Test method {{.Name}} async with callback")
    {
        {{- if (not .Return.IsVoid) }}
        std::atomic<bool> finished = false;
        auto resultFuture = client{{$class}}->{{lower1 .Name }}Async(
    {{- range $idx, $p := .Params -}}
            {{- if $idx }}, {{end -}}
            {{ cppDefault $namespacePrefix .}}
    {{- end -}}{{- if (len .Params) }},{{end -}}
        [&finished, &m_wait]({{cppType "" .Return}} value){ (void) value; finished = true; m_wait.notify_all(); /* YOU CAN CHECK EFFECTS OF YOUR METHOD HERE */ });

        lock.lock();
        REQUIRE( m_wait.wait_for(lock, std::chrono::milliseconds(timeout), [&finished](){ return finished == true; }));
        lock.unlock();
        auto return_value = resultFuture.get();
        {{ if (eq .Return.KindType "extern") }}//{{ end }}REQUIRE(return_value == {{ cppDefault $namespacePrefix .Return }}); {{ if (eq .Return.KindType "extern") }}// Make sure the comparison is valid for extern type. {{ end }}

        {{- else }}
        auto resultFuture = client{{$class}}->{{lower1 .Name }}Async(
    {{- range $idx, $p := .Params -}}
            {{- if $idx }}, {{end -}}
            {{ cppDefault $namespacePrefix .}}
    {{- end -}}{{- if (len .Params) }},{{end -}}
        [](){/* you can add a callback, but it will be called right after sending the request. It does not wait for the actual function on server side to be finished. */ });
        {{- end}}
    }


    {{- end }}

    std::atomic<bool> serviceDisconnected{ false };
    mqttservice->subscribeToConnectionStatus([&serviceDisconnected, &m_wait](auto boo) {
        if (!boo)
        {
            serviceDisconnected = true;
            m_wait.notify_all();
        }
        
        });

    mqttservice->disconnect();

    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout),
        [&serviceDisconnected]() { return serviceDisconnected == true; });
    lock.unlock();
    REQUIRE(serviceDisconnected);

    std::atomic<bool> clientDisonnected{ false };
    mqttclient->subscribeToConnectionStatus([&clientDisonnected, &m_wait](auto boo) {
        if (!boo)
        {
            clientDisonnected = true;
            m_wait.notify_all();
        }
        });

    mqttclient->disconnect();

    lock.lock();
    m_wait.wait_for(lock, std::chrono::milliseconds(timeout),
        [&clientDisonnected]() { return clientDisonnected == true; });
    lock.unlock();
    REQUIRE(clientDisonnected);

    mqttservice.reset();
    mqttclient.reset();
    service{{$class}}.reset();
    client{{$class}}.reset();
}
