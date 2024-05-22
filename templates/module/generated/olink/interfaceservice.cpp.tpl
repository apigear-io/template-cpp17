{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $class := printf "%sService" .Interface.Name  }}
{{ $interfaceNameOriginal := .Interface.Name  }}
{{ $interfaceName := Camel .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName -}}


#include "{{snake .Module.Name}}/generated/api/datastructs.api.h"
#include "{{snake .Module.Name}}/generated/olink/{{lower (camel .Interface.Name)}}service.h"
#include "{{snake .Module.Name}}/generated/core/{{snake .Module.Name}}.json.adapter.h"
{{- range .Module.Imports }}
#include "{{snake .Name}}/generated/core/{{snake .Name}}.json.adapter.h"
{{- end }}

#include "olink/iremotenode.h"
#include "olink/remoteregistry.h"
#include "apigear/utilities/logger.h"

#include <iostream>


using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};
using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }}::olink;

namespace 
{
const std::string interfaceId = "{{.Module.Name}}.{{$interfaceNameOriginal}}";
}

{{$class}}::{{$class}}(std::shared_ptr<{{$interfaceClass}}> {{$interfaceNameOriginal}}, ApiGear::ObjectLink::RemoteRegistry& registry)
    : m_{{$interfaceNameOriginal}}({{$interfaceNameOriginal}})
    , m_registry(registry)
{
    m_{{$interfaceNameOriginal}}->_getPublisher().subscribeToAllChanges(*this);
}

{{$class}}::~{{$class}}()
{
    m_{{$interfaceNameOriginal}}->_getPublisher().unsubscribeFromAllChanges(*this);
}

std::string {{$class}}::olinkObjectName() {
    return interfaceId;
}

nlohmann::json {{$class}}::olinkInvoke(const std::string& methodId, const nlohmann::json& fcnArgs) {
{{- if len .Interface.Operations }}
{{- $paramsUsed := false}}
{{- range .Interface.Operations }}
{{- $operation := . }}
{{- if len $operation.Params }}{{ $paramsUsed = true }}{{- break }}{{- end }}
{{- end }}
{{- if not $paramsUsed}}
    (void) fcnArgs;
{{- end }}
{{- end }}
    AG_LOG_DEBUG("{{$class}} invoke " + methodId);
    const auto& memberMethod = ApiGear::ObjectLink::Name::getMemberName(methodId);
{{- range .Interface.Operations}}
{{- $operation := . }}
    if(memberMethod == "{{$operation.Name}}") {
{{- range $idx, $elem := $operation.Params }}
{{- $param := . }}
        const {{cppType "" $param}}& {{$param}} = fcnArgs.at({{ $idx}});      
{{- end }}
    {{- if .Return.IsVoid }}
        m_{{$interfaceNameOriginal}}->{{lower1 $operation.Name}}({{ cppVars $operation.Params }});
        return nlohmann::json{};
    {{- else }}
        {{cppReturn "" $operation.Return}} result = m_{{$interfaceNameOriginal}}->{{lower1 $operation.Name}}({{ cppVars $operation.Params }});
        return result;
    {{- end}}
    }
{{- else }}
    // no operations to invoke {{- /* we generate anyway for consistency */}}
    (void) fcnArgs;
    (void) memberMethod;
{{- end }}
    return nlohmann::json();
}

void {{$class}}::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value) {
    AG_LOG_DEBUG("{{$class}} set property " + propertyId);
    const auto& memberProperty = ApiGear::ObjectLink::Name::getMemberName(propertyId);
{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
    if(memberProperty == "{{$property}}") {
        {{cppType "" $property}} {{$property}} = value.get<{{cppType "" $property}}>();
        m_{{$interfaceNameOriginal}}->set{{Camel $property.Name}}({{$property}});
    }
{{- end }}
{{- else }}
    // no properties to set {{- /* we generate anyway for consistency */}}
    (void) value;
    (void) memberProperty;
{{- end }} 
}

void {{$class}}::olinkLinked(const std::string& objectId, ApiGear::ObjectLink::IRemoteNode* /*node*/) {
    AG_LOG_DEBUG("{{$class}} linked " + objectId);
}

void {{$class}}::olinkUnlinked(const std::string& objectId){
    AG_LOG_DEBUG("{{$class}} unlinked " + objectId);
}

nlohmann::json {{$class}}::olinkCollectProperties()
{
    return nlohmann::json::object({
{{- range $idx, $elem := .Interface.Properties}}
{{- $property := . }}
{{- if $idx }},{{- end }}
        { "{{$property.Name}}", m_{{$interfaceNameOriginal}}->get{{Camel $property.Name}}() }
{{- end }}
    });
}

{{- range .Interface.Signals}}
{{- $signal := . }}
void {{$class}}::on{{Camel $signal.Name}}({{cppParams "" $signal.Params}})
{
    const nlohmann::json args = { {{ cppVars $signal.Params}} };
    static const auto signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "{{$signal.Name}}");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifySignal(signalId, args);
        }
    }
}
{{- end }}

{{- range .Interface.Properties}}
{{- $property := . }}
void {{$class}}::on{{Camel $property.Name}}Changed({{cppParam "" $property}})
{
    static const auto propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "{{$property.Name}}");
    static const auto objectId = olinkObjectName();
    for(auto node: m_registry.getNodes(objectId)) {
        auto lockedNode = node.lock();
        if(lockedNode) {
            lockedNode->notifyPropertyChange(propertyId, {{$property}});
        }
    }
}
{{- end }}

