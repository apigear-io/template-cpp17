{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $class := printf "%sClient" .Interface.Name }}
{{- $pub_interface := printf "I%sPublisher" $interfaceName }}
{{- $pub_class := printf "%sPublisher" $interfaceName -}}
#include "{{snake .Module.Name}}/generated/mqtt/{{lower (camel .Interface.Name)}}client.h"
#include "{{snake .Module.Name}}/generated/core/{{lower (camel .Interface.Name)}}.publisher.h"
#include "{{snake .Module.Name}}/generated/core/{{snake .Module.Name}}.json.adapter.h"
#include <random>

using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};
using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }}::MQTT;

namespace {
    std::mt19937 randomNumberGenerator (std::random_device{}());
}

{{$class}}::{{$class}}(std::shared_ptr<ApiGear::MQTT::Client> client)
    : m_isReady(false)
    , m_client(client)
    , m_publisher(std::make_unique<{{$pub_class}}>())
    , m_topics(createTopicMap(m_client->getClientId()))
{
    m_connectionStatusRegistrationID = m_client->subscribeToConnectionStatus([this](bool connectionStatus){ onConnectionStatusChanged(connectionStatus); });
}

{{$class}}::~{{$class}}()
{
    for (const auto& topic: m_topics)
    {
        m_client->unsubscribeTopic(topic. first);
    }
    m_client->unsubscribeToConnectionStatus(m_connectionStatusRegistrationID);
}

std::map<std::string, ApiGear::MQTT::CallbackFunction> {{$class}}::createTopicMap(const std::string& 
    {{- if len .Interface.Operations}} clientId{{end}})
{
    return {
    {{- range .Interface.Properties}}
    {{- $property := . }}
    {{- if not .IsReadOnly }}
        { std::string("{{$.Module.Name}}/{{$interfaceName}}/prop/{{$property}}"), [this](const std::string& args, const std::string&, const std::string&){ this->set{{Camel $property.Name}}Local(args); } },
    {{- end }}
    {{- end }}
    {{- range .Interface.Signals}}
    {{- $signal := . }}
        { std::string("{{$.Module.Name}}/{{$interfaceName}}/sig/{{$signal}}"), [this](const std::string& args, const std::string&, const std::string&){ this->on{{Camel $signal.Name }}(args); } },
    {{- end }}
    {{- range .Interface.Operations}}
    {{- $operation := . }}
        { std::string("{{$.Module.Name}}/{{$interfaceName}}/rpc/{{$operation}}/"+clientId+"/result"), [this](const std::string& args, const std::string&, const std::string& correlationData){ this->onInvokeReply(args, correlationData); } },
    {{- end }}
    };
};

void {{$class}}::onConnectionStatusChanged(bool connectionStatus)
{
    m_isReady = connectionStatus;
    if(!connectionStatus)
    {
        return;
    }

    for (const auto& topic: m_topics)
    {
        m_client->subscribeTopic(topic. first, topic.second);
    }
}

{{- range .Interface.Properties}}
{{- $property := . }}
{{- $name := $property.Name }}
{{- if not .IsReadOnly }}

void {{$class}}::set{{Camel $name}}({{cppParam "" $property}})
{
    if(m_client == nullptr) {
        return;
    }
    static const auto topic = std::string("{{.Module.Name}}/{{$interfaceName}}/set/{{$property}}");
    m_client->setRemoteProperty(topic, nlohmann::json({{$property}}).dump());
}

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
{{- end }}

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
    return std::async(std::launch::async, [this{{- range $operation.Params -}},
                    {{.Name}}
                {{- end -}}]()
        {
            std::promise<{{$returnType}}> resultPromise;
            static const auto topic = std::string("{{$.Module.Name}}/{{$interfaceName}}/rpc/{{$operation}}");
            static const auto responseTopic = std::string(topic + "/" + m_client->getClientId() + "/result");
            ApiGear::MQTT::InvokeReplyFunc responseHandler = [&resultPromise](ApiGear::MQTT::InvokeReplyArg arg) {
                {{- if .Return.IsVoid }}
                (void) arg;
                resultPromise.set_value();
                {{- else }}
                const {{$returnType}}& value = arg.value.get<{{$returnType}}>();
                resultPromise.set_value(value);
                {{- end }}
            };
            auto responseId = registerResponseHandler(responseHandler);
            m_client->invokeRemote(topic, responseTopic,
                nlohmann::json::array({ {{- cppVars $operation.Params -}} }).dump(), responseId);
            return resultPromise.get_future().get();
        }
    );
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

int {{$class}}::registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler)
{
    auto responseId = 0;
    std::uniform_int_distribution<> distribution (0, 100000);
    m_responseHandlerMutex.lock();
    do {
        responseId = distribution(randomNumberGenerator);
    } while (m_responseHandlerMap.find(responseId) != m_responseHandlerMap.end());
    m_responseHandlerMap.insert(std::pair<int, ApiGear::MQTT::InvokeReplyFunc>(responseId, handler));
    m_responseHandlerMutex.unlock();

    return responseId;
}

void {{$class}}::onInvokeReply(const std::string& args, const std::string& correlationData)
{
    const int randomId = std::stoi(correlationData);
    ApiGear::MQTT::InvokeReplyFunc responseHandler {};
    m_responseHandlerMutex.lock();
    if((m_responseHandlerMap.find(randomId) != m_responseHandlerMap.end()))
    {
        responseHandler = m_responseHandlerMap[randomId];
        m_responseHandlerMap.erase(randomId);
    }
    m_responseHandlerMutex.unlock();
    if(responseHandler) {
        const ApiGear::MQTT::InvokeReplyArg response{nlohmann::json::parse(args)};
        responseHandler(response);
    }
}

bool {{$class}}::isReady() const
{
    return m_isReady;
}

{{$pub_interface}}& {{$class}}::_getPublisher() const
{
    return *m_publisher;
}
