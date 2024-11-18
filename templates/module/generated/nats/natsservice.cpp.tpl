{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $class := printf "%sService" .Interface.Name }}
{{- $interface := .Interface.Name -}}
{{- $interfaceName := Camel .Interface.Name  -}}
{{- $interfaceClass := printf "I%s" $interfaceName -}}
#include "{{snake .Module.Name}}/generated/nats/{{lower (camel .Interface.Name)}}service.h"
#include "{{snake .Module.Name}}/generated/core/{{snake .Module.Name}}.json.adapter.h"
{{- range .Module.Imports }}
#include "{{snake .Name}}/generated/core/{{snake .Name}}.json.adapter.h"
{{- end }}
#include <iostream>

using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};
using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }}::Nats;

{{$class}}::{{$class}}(std::shared_ptr<{{$interfaceClass}}> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service)
    , m_impl(impl)
    , m_service(service)
{
    BaseAdapter::init([this](){onConnected();});
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

{{$class}}::~{{$class}}()
{
    m_impl->_getPublisher().unsubscribeFromAllChanges(*this);
}


void {{$class}}::onConnected()
{
    {{- range .Interface.Properties }}
    {{- if not .IsReadOnly }}
    subscribeTopic("{{$.Module.Name}}.{{$interfaceName}}.set.{{.Name}}", [this](const auto& value){ onSet{{Camel .Name}}(value); });
    {{- end }}
    subscribeRequest("{{$.Module.Name}}.{{$interfaceName}}.get.{{.Name}}", [this](const auto& /*value*/){ return nlohmann::json{m_impl->get{{Camel .Name}}()}.dump();});
    {{- end }}
    {{- range .Interface.Operations }}
    subscribeRequest("{{$.Module.Name}}.{{$interface}}.rpc.{{.Name}}", [this](const auto& args){  return onInvoke{{ Camel .Name }}(args); });
    {{- end }}
}

{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
void {{$class}}::onSet{{Camel $property.Name}}(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    if (json_args.empty())
    {
        return;
    }

    auto {{$property}} = json_args.get<{{cppType "" $property}}>();
    m_impl->set{{Camel $property.Name}}({{$property}});
}
{{- end }}
{{- end }}

{{- range .Interface.Signals}}
{{- $signal := . }}
void {{$class}}::on{{Camel $signal.Name}}({{cppParams "" $signal.Params}})
{
    {{- range $signal.Params}}
    (void) {{cppVar .}};
    {{- end}}
    static const std::string topic = "{{$.Module.Name}}.{{$interfaceName}}.sig.{{.Name}}";
    nlohmann::json args = { {{ cppVars $signal.Params}} };
    m_service->publish(topic, nlohmann::json(args).dump());
}
{{- end }}

{{- range .Interface.Properties}}
{{- $property := . }}
void {{$class}}::on{{Camel $property.Name}}Changed({{cppParam "" $property}})
{
    static const std::string topic = "{{$.Module.Name}}.{{$interfaceName}}.prop.{{.Name}}";
    m_service->publish(topic, nlohmann::json({{$property}}).dump());
}
{{- end }}

{{- range .Interface.Operations}}
{{- $operation := . }}
std::string {{$class}}::onInvoke{{ Camel $operation.Name }}(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);

{{- range $idx, $elem := $operation.Params }}
{{- $param := . }}
    const {{cppType "" $param}}& {{$param}} = json_args.at({{$idx}}).get<{{cppType "" $param}}>();
{{- end }}
{{- if .Return.IsVoid }}
    m_impl->{{lower1 $operation.Name}}({{ cppVars $operation.Params }});
    return "0";
{{- else }}
    auto result = m_impl->{{lower1 $operation.Name}}({{ cppVars $operation.Params }});
    return nlohmann::json(result).dump();
{{- end }}
}
{{- end }}
