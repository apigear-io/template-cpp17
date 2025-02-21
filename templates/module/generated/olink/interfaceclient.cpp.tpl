{{- /* Copyright (c) ApiGear UG 2020 */ -}}

{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}
{{- $identifiername := printf "%s.%s" .Module.Name .Interface.Name }}
{{- $class := printf "%sClient" .Interface.Name }}
{{- $pub_interface := printf "I%sPublisher" $interfaceName }}
{{- $pub_class := printf "%sPublisher" $interfaceName }}

#include "{{snake .Module.Name}}/generated/olink/{{lower (camel .Interface.Name)}}client.h"
#include "{{snake .Module.Name}}/generated/core/{{lower (camel .Interface.Name)}}.publisher.h"
#include "{{snake .Module.Name}}/generated/core/{{snake .Module.Name}}.json.adapter.h"
{{- range .Module.Imports }}
#include "{{snake .Name}}/generated/core/{{snake .Name}}.json.adapter.h"
{{- end }}

#include "olink/iclientnode.h"
#include "apigear/utilities/logger.h"

using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};
using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }}::olink;

namespace 
{
const std::string interfaceId = "{{$identifiername}}";
}

{{$class}}::{{$class}}()
    : m_publisher(std::make_unique<{{$pub_class}}>())
{}

void {{$class}}::applyState(const nlohmann::json& fields) 
{
{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
    if(fields.contains("{{$property.Name}}")) {
        set{{Camel $property.Name}}Local(fields["{{$property.Name}}"].get<{{cppType "" $property}}>());
    }
{{- end }}
{{- else }}
    // no properties to apply state {{- /* we generate anyway for consistency */}}
    (void) fields;
{{- end }}
}

void {{$class}}::applyProperty(const std::string& propertyName, const nlohmann::json& value)
{
{{- range $idx, $property := .Interface.Properties }}
{{- if not .IsReadOnly }}
    {{ if $idx }}else {{ end -}}if ( propertyName == "{{$property.Name}}") {
        set{{Camel $property.Name}}Local(value.get<{{cppType "" $property}}>());
    }
{{- end }}
{{- else -}}
    // no properties to apply state {{- /* we generate anyway for consistency */}}
    (void) propertyName;
    (void) value;
{{- end }}
}

{{- range .Interface.Properties}}
{{- $property := . }}
{{- $name := $property.Name }}
{{- if not .IsReadOnly }}

void {{$class}}::set{{Camel $name}}({{cppParam "" $property}})
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to set property but " + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return;
    }
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "{{$property.Name}}");
    m_node->setRemoteProperty(propertyId, {{$property.Name}});
}

void {{$class}}::set{{Camel $name}}Local({{cppParam "" $property }})
{
    {
        std::unique_lock<std::shared_timed_mutex> lock(m_{{lower1 ((Camel $property.Name))}}Mutex);
        {{- if ( or ( eq (cppType "" $property) "float") ( eq (cppType "" $property) "double") ) -}}
        // consider using fuzzy compare, check library ApiGear::Utilities::fuzzyCompare
        {{- end }}
        if (m_data.m_{{$name}} == {{$name}}) {
            return;
        }
        m_data.m_{{$name}} = {{$name}};
    }

    m_publisher->publish{{Camel $name}}Changed({{$name}});
}
{{- end }}

{{cppTypeRef "" $property}} {{$class}}::get{{Camel $name}}() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_{{lower1 ((Camel $property.Name))}}Mutex);
    return m_data.m_{{$name}};
}

{{- end }}


{{- range .Interface.Operations}}
{{- $operation := . }}
{{- $returnType := cppReturn "" $operation.Return }}

{{$returnType}} {{$class}}::{{lower1 $operation.Name}}({{cppParams "" $operation.Params}})
{
    return {{lower1 $operation.Name}}Async({{ cppVars $operation.Params }}).get();
}

std::future<{{$returnType}}> {{$class}}::{{$operation.Name| lower1}}Async({{cppParams "" $operation.Params}}{{- if len ($operation.Params) }},{{end}} std::function<void({{cppReturn "" $operation.Return}})> callback)
{
    if(!m_node) {
        AG_LOG_WARNING("Attempt to invoke method but" + olinkObjectName() +" is not linked to source . Make sure your object is linked. Check your connection to service");
        return std::future<{{$returnType}}>{};
    }
    std::shared_ptr<std::promise<{{$returnType}}>> resultPromise = std::make_shared<std::promise<{{$returnType}}>>();
    static const auto operationId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "{{$operation.Name}}");
    m_node->invokeRemote(operationId,
        nlohmann::json::array({ {{- cppVars $operation.Params -}} }), [resultPromise, callback](ApiGear::ObjectLink::InvokeReplyArg arg) {        
            {{- if .Return.IsVoid }}
            (void) arg;
            resultPromise->set_value();
            if (callback)
            {
                callback();
            }
            {{- else }}
            const {{$returnType}}& value = arg.value.get<{{$returnType}}>();
            resultPromise->set_value(value);
            if (callback)
            {
                callback(value);
            }
            {{- end }}
        });
    return resultPromise->get_future();
}

{{- end }}

std::string {{$class}}::olinkObjectName()
{
    return interfaceId;
}

void {{$class}}::olinkOnSignal(const std::string& signalId, const nlohmann::json& args)
{
{{- if len .Interface.Signals }}
{{- $paramsUsed := false}}
{{- range .Interface.Signals }}
{{- $signal := . }}
{{- if len $signal.Params }}{{ $paramsUsed = true }}{{- break }}{{- end }}
{{- end }}
{{- if not $paramsUsed}}
    (void) args;
{{- end }}
{{- end }}
    const auto& signalName = ApiGear::ObjectLink::Name::getMemberName(signalId);
{{- range .Interface.Signals}}
{{- $signal := . }}
    if(signalName == "{{$signal}}") {
        m_publisher->publish{{Camel $signal.Name -}}(
{{- range $idx, $elem := $signal.Params }}
{{- $param := . -}}
        {{- if $idx }},{{- end -}}
        args[{{$idx}}].get<{{cppType "" $param}}>()
{{- end -}}
        );   
        return;
    }
{{- else }}
    (void) args;
    (void) signalName;
{{- end }}
}

void {{$class}}::olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value)
{
    applyProperty(ApiGear::ObjectLink::Name::getMemberName(propertyId), value);
}
void {{$class}}::olinkOnInit(const std::string& /*name*/, const nlohmann::json& props, ApiGear::ObjectLink::IClientNode *node)
{
    m_node = node;
    applyState(props);
}

void {{$class}}::olinkOnRelease()
{
    m_node = nullptr;
}

bool {{$class}}::isReady() const
{
    return m_node != nullptr;
}

{{$pub_interface}}& {{$class}}::_getPublisher() const
{
    return *m_publisher;
}
