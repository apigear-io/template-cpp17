{{- /* Copyright (c) ApiGear UG 2020 */ -}}
#include "apigear/tracer/tracer.h"
#include "{{snake .Module.Name}}/generated/core/{{snake .Module.Name}}.json.adapter.h"
{{- range .Module.Imports }}
#include "{{snake .Name}}/generated/core/{{snake .Name}}.json.adapter.h"
{{- end }}
#include "{{snake .Module.Name}}/generated/monitor/{{lower (camel .Interface.Name)}}.tracer.h"

using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};

{{- $class := printf "%sTracer" .Interface.Name  }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $modulName := .Module.Name  }}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}

{{$class}}::{{$class}}(ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(tracer)
{
}

void {{$class}}::capture_state({{$interfaceClass}}* obj)
{
    nlohmann::json fields_;
{{- range .Interface.Properties}}
{{- $property := . }}
    fields_["{{$property.Name}}"] = obj->get{{Camel $property.Name}}();
    {{- else }}
    (void) obj;
{{- end }}
    m_tracer.state("{{lower1 $modulName}}.{{$interfaceNameOriginal}}#_state", fields_);
}

{{- range .Interface.Operations}}
{{ $operation := . }}
void {{$class}}::trace_{{$operation.Name}}({{cppParams "" $operation.Params}})
{
    nlohmann::json fields_;
    {{- range $operation.Params}}
    {{- $param := . }}
    fields_["{{$param.Name}}"] = {{$param.Name}};
    {{- end }}
    m_tracer.call("{{lower1 $modulName}}.{{$interfaceNameOriginal}}#{{$operation.Name}}", fields_);
}
{{- end }}

{{- range .Interface.Signals}}
{{- $signal := . }}
void {{$class}}::trace_{{$signal.Name}}({{ cppParams "" $signal.Params }})
{
    nlohmann::json fields_;
    {{- range $signal.Params}}
    {{- $param := . }}
    fields_["{{$param.Name}}"] = {{$param.Name}};
    {{- end }}
    m_tracer.signal("{{lower1 $modulName}}.{{$interfaceNameOriginal}}#{{$signal.Name}}", fields_);
}
{{- end }}