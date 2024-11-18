{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}
{{- $class := printf "%sClient" .Interface.Name }}
{{- $sub_class := printf "I%sSubscriber" $interfaceName }}
{{- $pub_class := printf "I%sPublisher" $interfaceName -}}
#pragma once

#include "{{snake .Module.Name}}/generated/api/common.h"
#include "{{snake .Module.Name}}/generated/api/{{snake .Module.Name}}.h"
#include "{{snake .Module.Name}}/generated/core/{{lower $interfaceName}}.data.h"
#include "apigear/nats/natsclient.h"
#include "apigear/nats/natstypes.h"
#include "apigear/nats/baseadapter.h"

#include <future>
#include <unordered_map>

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {
namespace Nats {
class {{ SNAKE .System.Name  }}_{{ SNAKE .Module.Name  }}_EXPORT {{$class}} : public {{$interfaceClass}}, public ApiGear::Nats::BaseAdapter
{
public:
    explicit {{$class}}(std::shared_ptr<ApiGear::Nats::Client> client);
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
private:
{{- range .Interface.Properties}}
{{- $property := . }}
    /// @brief sets the value for the property {{Camel $property.Name}} coming from the service
    /// @param args contains the param of the type {{cppType "" $property }}
    void set{{Camel $property.Name}}Local(const std::string& args);
{{- end }}

{{- range .Interface.Signals}}
{{- $signal := . }}
    /// @brief publishes the value for the signal {{Camel $signal.Name}} coming from the service
    /// @param args contains the param(s) of the type(s) {{cppParams "" $signal.Params }}
    void on{{Camel $signal.Name }}(const std::string& args) const;
{{- end }}

{{- if len .Interface.Properties}}
    /** Local storage for properties values. */
    {{$interfaceName}}Data m_data;
{{- end }}
    std::shared_ptr<ApiGear::Nats::Client> m_client;
    /** The publisher for {{$interfaceName}} */
    std::unique_ptr<{{$pub_class}}> m_publisher;

    void onConnected();

};
} // namespace Nats
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
