{{- /* Copyright (c) ApiGear UG 2020 */}}
{{- $class := printf "%sService" .Interface.Name  }}
{{- $interface := .Interface.Name  -}}
{{- $interfaceName := Camel .Interface.Name  -}}
{{- $interfaceClass := printf "I%s" $interfaceName -}}
#pragma once

#include "{{snake .Module.Name}}/generated/api/{{snake .Module.Name}}.h"
#include "{{snake .Module.Name}}/generated/api/common.h"
#include "apigear/mqtt/mqttservice.h"

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {
namespace MQTT {
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$class}} : public {{$interfaceClass}}Subscriber
{
public:
    explicit {{$class}}(std::shared_ptr<{{$interfaceClass}}> impl, std::shared_ptr<ApiGear::MQTT::Service> service);
    virtual ~{{$class}}() override;

    void onConnectionStatusChanged(bool connectionStatus);

{{- if len .Interface.Signals}}{{nl}}
    // {{$interfaceClass}}Subscriber interface
{{- end}}
{{- range .Interface.Signals}}
{{- $signal := . }}
    void on{{Camel $signal.Name}}({{cppParams "" $signal.Params}}) override;
{{- end }}

private:
    /// @brief factory to create the topic map which is used for bindings
    /// @return map with all topics and corresponding function callbacks
    std::map<std::string, ApiGear::MQTT::CallbackFunction> createTopicMap();

{{- range .Interface.Operations}}
{{- $operation := . }}
    void onInvoke{{ Camel $operation.Name }}(const std::string& args, const std::string& responseTopic, const std::string& correlationData) const;
{{- end }}

{{- range .Interface.Properties}}
{{- $property := . }}
    void on{{Camel $property.Name}}Changed({{cppParam "" $property}}) override;
{{- if not .IsReadOnly }}
    /// @brief requests to set the value for the property {{Camel $property.Name}} coming from the client
    /// @param fields contains the param of the type {{cppType "" $property }}
    void onSet{{Camel $property.Name}}(const std::string& args) const;
{{- end }}
{{- end }}

    std::shared_ptr<{{$interfaceClass}}> m_impl;
    std::shared_ptr<ApiGear::MQTT::Service> m_service;
    // id for connection status registration
    int m_connectionStatusRegistrationID;

    /// @brief has all the topics of this service and the corresponding function callbacks
    const std::map<std::string, ApiGear::MQTT::CallbackFunction> m_topics;
};
} // namespace MQTT
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
