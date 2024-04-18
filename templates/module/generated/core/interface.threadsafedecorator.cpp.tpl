{{- /* Copyright (c) ApiGear UG 2020 */ -}}

{{- $interfaceName := Camel .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $interfaceName }}
{{- $class := printf "%sThreadSafeDecorator" $interfaceName }}
{{- $sub_class := printf "%sSubscriber" $class }}
{{- $pub_class := printf "I%sPublisher" $interfaceName }}

#include "{{snake .Module.Name}}/generated/core/{{lower (camel .Interface.Name)}}.threadsafedecorator.h"

using namespace {{ Camel .System.Name }}::{{ Camel .Module.Name }};
{{$class}}::{{$class}}(std::shared_ptr<{{$interfaceClass}}> impl)
    : m_impl(impl)
{
}

{{- range .Interface.Operations}}
{{- $operation := . }}
{{cppReturn "" $operation.Return}} {{$class}}::{{lower1 $operation.Name}}({{cppParams "" $operation.Params}})
{
    return m_impl->{{lower1 $operation.Name}}({{cppVars $operation.Params }});
}

std::future<{{cppReturn "" $operation.Return}}> {{$class}}::{{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}})
{
    return m_impl->{{$operation.Name| lower1}}Async({{cppVars $operation.Params }});
}

{{- end }}

{{- range .Interface.Properties}}
{{- $property := . }}
{{- if not .IsReadOnly }}
void {{$class}}::set{{Camel $property.Name}}({{cppParam "" $property}})
{
    std::unique_lock<std::shared_timed_mutex> lock(m_{{lower1 ((Camel $property.Name))}}Mutex);
    m_impl->set{{Camel $property.Name}}({{$property.Name}});
}
{{- end }}

{{cppTypeRef "" $property}} {{$class}}::get{{Camel $property.Name}}() const
{
    std::shared_lock<std::shared_timed_mutex> lock(m_{{lower1 ((Camel $property.Name))}}Mutex);
    return m_impl->get{{Camel $property.Name}}();
}

{{- end }}

{{$pub_class}}& {{$class}}::_getPublisher() const
{
    return m_impl->_getPublisher();
}