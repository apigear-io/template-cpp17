{{- /* Copyright (c) ApiGear UG 2020 */ -}}

{{- $class := Camel .Interface.Name  }}
{{- $interfaceClass := printf "I%s" $class }}
{{- $interfaceNameOriginal := .Interface.Name  }}
{{- $pub_class := printf "%sPublisher" $class }}

#include "{{snake .Module.Name}}/implementation/{{lower (camel .Interface.Name)}}.h"
#include "{{snake .Module.Name}}/generated/core/{{lower (camel .Interface.Name)}}.publisher.h"
#include "{{snake .Module.Name}}/generated/core/{{lower (camel .Interface.Name)}}.data.h"

using namespace {{ Camel .System.Name }}::{{Camel .Module.Name }};

{{$class}}::{{$class}}()
    : m_publisher(std::make_unique<{{$pub_class}}>())
{
}
{{$class}}::~{{$class}}()
{
}
{{- range .Interface.Properties}}
{{ $property := . }}
void {{$class}}::set{{Camel $property.Name}}({{cppParam "" $property }})
{
    {{- if ( or ( eq (cppType "" $property) "float") ( eq (cppType "" $property) "double") ) }}
    // consider using fuzzy compare, check library ApiGear::Utilities::fuzzyCompare
    {{- end }}
    if (m_data.m_{{$property.Name}} != {{$property.Name}}) {
        m_data.m_{{$property.Name}} = {{$property.Name}};
        m_publisher->publish{{Camel $property.Name}}Changed({{$property.Name}});
    }
}

{{cppTypeRef "" $property}} {{$class}}::get{{Camel $property.Name}}() const
{
    return m_data.m_{{$property.Name}};
}
{{- end }}

{{- range .Interface.Operations}}
{{- $operation := . }}

{{cppReturn "" $operation.Return}} {{$class}}::{{lower1 $operation.Name}}({{cppParams "" $operation.Params}})
{
    {{- range $operation.Params}}
    {{- $parameter := . }}
    (void) {{$parameter.Name}}; // suppress the 'Unreferenced Formal Parameter' warning.
    {{- end }}
    // do business logic here
    {{- if not .Return.IsVoid }}
    return {{cppDefault "" .Return}};
    {{- end }}
}
{{ $returnType := cppReturn "" $operation.Return }}
std::future<{{$returnType}}> {{$class}}::{{lower1 $operation.Name}}Async({{cppParams "" $operation.Params}})
{
    return std::async(std::launch::async, [this{{- range $operation.Params -}},
                    {{.Name}}
                {{- end -}}]()
        {
            return {{lower1 $operation.Name}}({{cppVars $operation.Params}});
        }
    );
}
{{- end }}

I{{$pub_class}}& {{$class}}::_getPublisher() const
{
    return *m_publisher;
}
