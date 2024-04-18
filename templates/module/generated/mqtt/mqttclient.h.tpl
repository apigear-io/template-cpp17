{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}
{{- $class := printf "%sClient" .Interface.Name }}
{{- $sub_class := printf "I%sSubscriber" $interfaceName }}
{{- $pub_class := printf "I%sPublisher" $interfaceName -}}
#pragma once

#include <future>
#include "{{snake .Module.Name}}/generated/api/common.h"
#include "{{snake .Module.Name}}/generated/api/{{snake .Module.Name}}.h"
#include "{{snake .Module.Name}}/generated/core/{{lower $interfaceName}}.data.h"
#include "apigear/mqtt/mqttclient.h"

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {
namespace MQTT {
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$class}} : public {{$interfaceClass}}
{
public:
    explicit {{$class}}(std::shared_ptr<ApiGear::MQTT::Client> client);
    virtual ~{{$class}}() override;

{{- range .Interface.Properties}}
{{- $property := . }}
    {{cppTypeRef "" $property}} get{{Camel $property.Name}}() const override;
{{- if not .IsReadOnly }}
    void set{{Camel $property.Name}}({{cppParam "" $property}}) override;
{{- end }}
{{- end }}

{{- range .Interface.Operations}}
{{- $operation := . }}
    {{cppReturn "" $operation.Return}} {{lower1 $operation.Name}}({{cppParams "" $operation.Params}}) override;
    std::future<{{cppReturn "" $operation.Return}}> {{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}}) override;
{{- end }}
    {{$pub_class}}& _getPublisher() const override;

    bool isReady() const;

    void onInvokeReply(const std::string& args, const std::string& correlationData);

    void onConnectionStatusChanged(bool connectionStatus);
private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap(const std::string& 
    {{- if len .Interface.Operations}}clientId{{end}});

{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
    /// @brief sets the value for the property {{Camel $property.Name}} coming from the service
    /// @param args contains the param of the type {{cppType "" $property }}
    void set{{Camel $property.Name}}Local(const std::string& args);
{{- end }}
{{- end }}

{{- range .Interface.Signals}}
{{- $signal := . }}
    /// @brief publishes the value for the signal {{Camel $signal.Name}} coming from the service
    /// @param args contains the param(s) of the type(s) {{cppParams "" $signal.Params }}
    void on{{Camel $signal.Name }}(const std::string& args) const;
{{- end }}

    bool m_isReady;
{{- if len .Interface.Properties}}
    /** Local storage for properties values. */
    {{$interfaceName}}Data m_data;
{{- end }}
    std::shared_ptr<ApiGear::MQTT::Client> m_client;

    /** The publisher for {{$interfaceName}} */
    std::unique_ptr<{{$pub_class}}> m_publisher;

    /**
     * @brief register a response handler for an operation invocation
     * 
     * @param handler function to be called on return
     * @return int unique id of the call
     */
    int registerResponseHandler(ApiGear::MQTT::InvokeReplyFunc handler);
    std::mutex m_responseHandlerMutex;
    std::map<int, ApiGear::MQTT::InvokeReplyFunc> m_responseHandlerMap;

    /// @brief has all the topics of this client and the corresponding function callbacks
    const std::map<std::string, ApiGear::MQTT::CallbackFunction> m_topics;
    // id for connection status registration
    int m_connectionStatusRegistrationID;
};
} // namespace MQTT
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
