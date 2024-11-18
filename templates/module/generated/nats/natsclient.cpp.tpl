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


{{$class}}::{{$class}}(std::shared_ptr<ApiGear::Nats::Client> client)
    :BaseAdapter(client)
    , m_client(client)
    , m_publisher(std::make_unique<{{$pub_class}}>())
{
    BaseAdapter::init([this](){onConnected();});
}

{{$class}}::~{{$class}}() = default;

void {{$class}}::onConnected()
{
    {{- range .Interface.Properties }}
    const std::string topic_{{.Name}} =  "{{$.Module.Name}}.{{$interfaceName}}.prop.{{.Name}}";
    subscribeTopic(topic_{{.Name}}, [this](const auto& value){ set{{Camel .Name}}Local(value); });

    {{- end }}
    {{- range .Interface.Signals }}
    const std::string topic_{{.Name}} = "{{$.Module.Name}}.{{$interfaceName}}.sig.{{.Name}}";
    subscribeTopic(topic_{{.Name}}, [this](const auto& args){on{{Camel .Name }}(args);});

    {{- end }}
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

void {{$class}}::set{{Camel $name}}Local(const std::string& args)
{
    nlohmann::json fields = nlohmann::json::parse(args);
    if (fields.empty())
    {
        return;
    }

    {{ cppParam "" $property }} = fields.get<{{cppType "" $property}}>();
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

std::future<{{$returnType}}> {{$class}}::{{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}})
{
    if(m_client == nullptr) {
        throw std::runtime_error("Client is not initialized");
    }
    static const auto topic = std::string("{{$.Module.Name}}.{{$interfaceName}}.rpc.{{$operation}}");

    return std::async(std::launch::async, [this{{- range $operation.Params -}},{{.Name}}{{- end -}}]()
    {
        std::promise<{{$returnType}}> resultPromise;
        auto callback = [&resultPromise](const auto& result)
        {
            nlohmann::json field = nlohmann::json::parse(result);
            {{- if .Return.IsVoid }}
            (void) result;
            resultPromise.set_value();
            {{- else }}
            const {{$returnType}} value = field.get<{{$returnType}}>();
            resultPromise.set_value(value);
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
