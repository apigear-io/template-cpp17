{{- /* Copyright (c) ApiGear UG 2020 */ -}}
{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}
{{- $class := printf "%sTraceDecorator" $interfaceName }}
{{- $sub_class := printf "I%sSubscriber" $interfaceName }}
{{- $pub_class := printf "I%sPublisher" $interfaceName }}

#include "{{snake .Module.Name}}/generated/monitor/{{lower (camel .Interface.Name)}}.tracedecorator.h"
#include "{{snake .Module.Name}}/generated/monitor/{{lower (camel .Interface.Name)}}.tracer.h"

using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};
{{$class}}::{{$class}}({{$interfaceClass}}& impl, ApiGear::PocoImpl::Tracer& tracer)
    : m_tracer(std::make_unique<{{.Interface.Name}}Tracer>(tracer))
    , m_impl(impl)
{
        m_impl._getPublisher().subscribeToAllChanges(*this);
}
{{$class}}::~{{$class}}()
{
    m_impl._getPublisher().unsubscribeFromAllChanges(*this);
}

std::unique_ptr<{{$class}}> {{$class}}::connect({{$interfaceClass}}& impl, ApiGear::PocoImpl::Tracer& tracer)
{
    return std::unique_ptr<{{$class}}>(new {{$class}}(impl, tracer));
}

{{- range .Interface.Operations}}
{{- $operation := . }}
{{cppReturn "" $operation.Return}} {{$class}}::{{lower1 $operation.Name}}({{cppParams "" $operation.Params}})
{
    m_tracer->trace_{{$operation.Name}}({{cppVars $operation.Params }});
    return m_impl.{{lower1 $operation.Name}}({{cppVars $operation.Params }});
}
std::future<{{cppReturn "" $operation.Return}}> {{$class}}::{{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}})
{
    m_tracer->trace_{{$operation.Name}}({{cppVars $operation.Params }});
    return m_impl.{{$operation.Name| lower1}}Async({{cppVars $operation.Params }});
}

{{- end }}

{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
void {{$class}}::set{{Camel $property.Name}}({{cppParam "" $property}})
{
    m_impl.set{{Camel $property.Name}}({{$property.Name}});
}
{{- end }}

{{cppTypeRef "" $property}} {{$class}}::get{{Camel $property.Name}}() const
{
    return m_impl.get{{Camel $property.Name}}();
}

{{- end }}

{{- range .Interface.Signals}}
{{- $signal := . }}
void {{$class}}::on{{Camel $signal.Name}}({{ cppParams "" $signal.Params }})
{
    m_tracer->trace_{{$signal.Name}}({{ cppVars $signal.Params }});
}
{{- nl}}
{{- end }}
{{- range .Interface.Properties}}
{{- $property := . }}
void {{$class}}::on{{Camel $property.Name}}Changed({{cppParam "" $property}})
{
    (void) {{$property.Name}}; // suppress the 'Unreferenced Formal Parameter' warning.
    m_tracer->capture_state(this);
}
{{- nl }}
{{- end }}


{{$pub_class}}& {{$class}}::_getPublisher() const
{
    return m_impl._getPublisher();
}
