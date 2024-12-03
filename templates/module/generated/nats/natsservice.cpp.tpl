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

{{- $expectedSubscriptionCount := len (.Interface.Properties) }}
{{- range .Interface.Properties }}
{{- if .IsReadOnly }}
{{- $expectedSubscriptionCount =  len (slice (printf "%*s" $expectedSubscriptionCount "") 1)  }}
{{- end }}
{{- end }}

namespace{
namespace{
{{- if len (.Interface.Operations) }}
const uint32_t  expectedMethodSubscriptions = {{len (.Interface.Operations)}};
{{- end }}
{{- if len (.Interface.Properties) }}
const uint32_t  expectedPropertiesSubscriptions = {{len (.Interface.Properties)}};
const uint32_t  initRespSubscription = 1;
{{- end }}
{{- if or (len (.Interface.Operations)) ( len (.Interface.Properties) ) }}
constexpr uint32_t expectedSubscriptionsCount = 
{{- if len (.Interface.Operations) }}
 expectedMethodSubscriptions
{{- if len (.Interface.Properties) }} + {{- end}}
{{- end}}
{{- if len (.Interface.Properties) }} expectedPropertiesSubscriptions + initRespSubscription {{- end}};
{{- else }}
// no methods requests and properties change requests to subscribe for
constexpr uint32_t expectedSubscriptionsCount = 0;
{{- end }}
}
}

{{$class}}::{{$class}}(std::shared_ptr<{{$interfaceClass}}> impl, std::shared_ptr<ApiGear::Nats::Service> service)
    :BaseAdapter(service, expectedSubscriptionsCount)
    , m_impl(impl)
    , m_service(service)
{
    m_impl->_getPublisher().subscribeToAllChanges(*this);
}

void {{$class}}::init()
{
    BaseAdapter::init([this](){onConnected();});
}

std::shared_ptr<{{$class}}> {{$class}}::create(std::shared_ptr<{{$interfaceClass}}> impl, std::shared_ptr<ApiGear::Nats::Service> service)
{
    std::shared_ptr<{{$class}}> obj(new {{$class}}(impl, service));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> {{$class}}::getSharedFromDerrived()
{
    return shared_from_this();
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
    {{- end }}
    {{- range .Interface.Operations }}
    subscribeRequest("{{$.Module.Name}}.{{$interface}}.rpc.{{.Name}}", [this](const auto& args){  return onInvoke{{ Camel .Name }}(args); });
    {{- end }}
    {{- if len (.Interface.Properties) }}
    const std::string initRequestTopic = "{{$.Module.Name}}.{{$interfaceName}}.init";
    subscribeTopic(initRequestTopic, [this, initRequestTopic](const auto& value){
        nlohmann::json json_id = nlohmann::json::parse(value);
        if (json_id.empty())
        {
            return;
        }
        auto clientId = json_id.get<uint64_t>();
        auto topic = initRequestTopic + ".resp." +  std::to_string(clientId);
        auto properties = getState();
        m_service->publish(topic, properties.dump());
        }
    );
    {{- end }}
    {{- range .Interface.Properties }}
    m_service->publish("{{$.Module.Name}}.{{$interfaceName}}.prop.{{.Name}}", nlohmann::json(m_impl->get{{Camel .Name}}()).dump());
    {{- end }}
}
{{- if len (.Interface.Properties) }}
nlohmann::json {{$class}}::getState()
{
    return nlohmann::json::object({
{{- range $idx, $elem := .Interface.Properties}}
{{- $property := . }}
{{- if $idx }},{{- end }}
        { "{{$property.Name}}", m_impl->get{{Camel $property.Name}}() }
{{- end }}
    });
}
{{- end }}

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
