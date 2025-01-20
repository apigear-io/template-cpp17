{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $interfaceName := .Interface.Name  }}
{{- $camelInterfaceName := Camel .Interface.Name  }}
{{- $class := printf "%sClient" .Interface.Name }}
{{- $pub_interface := printf "I%sPublisher" $camelInterfaceName }}
{{- $pub_class := printf "%sPublisher" $camelInterfaceName -}}
#include "{{snake .Module.Name}}/generated/nats/{{lower (camel .Interface.Name)}}client.h"
#include "{{snake .Module.Name}}/generated/core/{{lower (camel .Interface.Name)}}.publisher.h"
#include "{{snake .Module.Name}}/generated/core/{{snake .Module.Name}}.json.adapter.h"
{{- range .Module.Imports }}
#include "{{snake .Name}}/generated/core/{{snake .Name}}.json.adapter.h"
{{- end }}
#include "apigear/utilities/logger.h"

using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};
using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }}::Nats;

namespace{
{{- if len (.Interface.Signals) }}
const uint32_t  expectedSingalsSubscriptions = {{len (.Interface.Signals)}};
{{- end }}
{{- if len (.Interface.Properties) }}
const uint32_t  expectedPropertiesSubscriptions = {{len (.Interface.Properties)}};
{{- end }}
const uint32_t  initSubscription = 1;
const uint32_t  serviceAvailableSubscription = 1;
{{- if or (len (.Interface.Signals)) ( len (.Interface.Properties) ) }}
constexpr uint32_t expectedSubscriptionsCount = serviceAvailableSubscription  + initSubscription 
{{- if len (.Interface.Signals) }}
 + expectedSingalsSubscriptions
{{- end}}
{{- if len (.Interface.Properties) }} + expectedPropertiesSubscriptions {{- end}};
{{- else }}
// no singals and properties to subscribe for
constexpr uint32_t expectedSubscriptionsCount = 0;
{{- end }}
}

std::shared_ptr<{{$class}}> {{$class}}::create(std::shared_ptr<ApiGear::Nats::Client> client)
{
    std::shared_ptr<{{$class}}> obj(new {{$class}}(client));
    obj->init();
    return obj;
}

std::shared_ptr<ApiGear::Nats::BaseAdapter> {{$class}}::getSharedFromDerrived()
{
    return shared_from_this();
}

{{$class}}::{{$class}}(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client, expectedSubscriptionsCount)
    , m_client(client)
    , m_publisher(std::make_unique<{{$pub_class}}>())
{}

void {{$class}}::init()
{
    BaseAdapter::init([this](){onConnected();});
}

{{$class}}::~{{$class}}() = default;

void {{$class}}::onConnected()
{
    auto clientId = m_client->getId();
    m_requestInitCallId = _subscribeForIsReady([this, clientId](bool is_subscribed)
    { 
        if(!is_subscribed)
        {
            return;
        }
        const std::string initRequestTopic = "{{$.Module.Name}}.{{$interfaceName}}.init";
        m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
        _unsubscribeFromIsReady(m_requestInitCallId);
    });
    subscribeTopic("{{$.Module.Name}}.{{$interfaceName}}.service.available",[this](const auto& value){ handleAvailable(value); });
    const std::string initTopic =  "{{$.Module.Name}}.{{$interfaceName}}.init.resp." + std::to_string(clientId);
    subscribeTopic(initTopic,[this](const auto& value){ handleInit(value); });

    {{- range .Interface.Properties }}
    const std::string topic_{{.Name}} =  "{{$.Module.Name}}.{{$interfaceName}}.prop.{{.Name}}";
    subscribeTopic(topic_{{.Name}}, [this](const auto& value){ set{{Camel .Name}}Local(_to_{{Camel .Name}}(value)); });

    {{- end }}
    {{- range .Interface.Signals }}
    const std::string topic_{{.Name}} = "{{$.Module.Name}}.{{$interfaceName}}.sig.{{.Name}}";
    subscribeTopic(topic_{{.Name}}, [this](const auto& args){on{{Camel .Name }}(args);});

    {{- end }}
}
void {{$class}}::handleAvailable(const std::string& /*empty payload*/)
{
    auto clientId = m_client->getId();
    const std::string initRequestTopic = "{{$.Module.Name}}.{{$interfaceName}}.init";
    m_client->publish(initRequestTopic, nlohmann::json(clientId).dump());
}

{{- range .Interface.Properties}}
{{- $property := . }}
{{- $name := $property.Name }}
{{- if not .IsReadOnly }}

void {{$class}}::set{{Camel $name}}({{cppParam "" $property}})
{
    static const auto topic = std::string("{{.Module.Name}}.{{$interfaceName}}.set.{{$property}}");
    if(m_client == nullptr) {
        return;
    }
    m_client->publish(topic, nlohmann::json({{$property}}).dump());
}
{{- end }}

{{cppType "" $property}} {{$class}}::_to_{{Camel $name}}(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        //AG_LOG_WARNING("error while setting the property {{cppVar $property}}");
        return {{cppDefault "" $property}};
    }
   return fields.get<{{cppType "" $property}}>();
}

void {{$class}}::set{{Camel $name}}Local({{ cppParam "" $property }})
{
    if (m_data.m_{{$name}} != {{$name}}) {
        m_data.m_{{$name}} = {{$name}};
        m_publisher->publish{{Camel $name}}Changed({{$name}});
    }
}

{{cppTypeRef "" $property}} {{$class}}::get{{Camel $name}}() const
{
    return m_data.m_{{$name}};
}

{{- end }}

void {{$class}}::handleInit(const std::string& value)
{
    nlohmann::json fields = nlohmann::json::parse(value);
{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
    if(fields.contains("{{$property.Name}}")) {
        set{{Camel $property.Name}}Local(fields["{{$property.Name}}"].get<{{cppType "" $property}}>());
    }
{{- end }}
{{- end }}
}

{{- range .Interface.Operations}}
{{- $operation := . }}
{{- $returnType := cppReturn "" $operation.Return }}

{{$returnType}} {{$class}}::{{lower1 $operation.Name}}({{cppParams "" $operation.Params}})
{
    if(m_client == nullptr) {
        {{- if not .Return.IsVoid }}
        return {{cppDefault "" $operation.Return}};
        {{- else }}
        return;
        {{- end }}
    }
    {{- if .Return.IsVoid }}
    {{lower1 $operation.Name}}Async({{ cppVars $operation.Params }});
    {{- else }}
    {{$returnType}} value({{lower1 $operation.Name}}Async({{ cppVars $operation.Params }}).get());
    return value;
    {{- end }}
}

std::future<{{$returnType}}> {{$class}}::{{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}}{{- if len ($operation.Params) }},{{end}} std::function<void({{cppReturn "" $operation.Return}})> user_callback)
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("{{$.Module.Name}}.{{$interfaceName}}.rpc.{{$operation}}");

    return std::async(std::launch::async, [this, user_callback{{- range $operation.Params -}},{{.Name}}{{- end -}}]()
    {
        std::promise<{{$returnType}}> resultPromise;
        auto callback = [&resultPromise, user_callback](const auto& result)
        {
            {{- if .Return.IsVoid }}
            (void) result;
            resultPromise.set_value();
            if (user_callback)
            {
                user_callback();
            }
            {{- else }}
            if (result.empty())
            {
                resultPromise.set_value({{cppDefault "" $operation.Return}});
                if (user_callback)
                {
                    user_callback({{cppDefault "" $operation.Return}});
                }
                return;
            }
            nlohmann::json field = nlohmann::json::parse(result);
            const {{$returnType}} value = field.get<{{$returnType}}>();
            resultPromise.set_value(value);
            if (user_callback)
            {
                user_callback(value);
            }
            {{- end }}
        };

        m_client->request(topic,  nlohmann::json::array({ {{- cppVars $operation.Params -}} }).dump(), callback);
        return resultPromise.get_future().get();
    });
}

{{- end }}

{{- range .Interface.Signals}}
{{- $signal := . }}
void {{$class}}::on{{Camel $signal.Name }}(const std::string& args) const
{
    nlohmann::json json_args = nlohmann::json::parse(args);
    m_publisher->publish{{Camel $signal.Name }}(
{{- range $idx, $elem := $signal.Params }}
{{- $param := . -}}
        {{- if $idx }},{{- end -}}
        json_args[{{$idx}}].get<{{cppType "" $param}}>()
{{- end -}}
    );
}
{{- end }}

{{$pub_interface}}& {{$class}}::_getPublisher() const
{
    return *m_publisher;
}

