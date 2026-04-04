{{- $features := .Features}}
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
#include "{{snake $module.Name}}/implementation/{{ lower ( camel $interface.Name) }}.h"
{{- if $features.monitor }}
#include "{{snake $module.Name}}/generated/monitor/{{ lower ( camel $interface.Name) }}.tracedecorator.h"
{{- end}}
{{- end }}
{{- end }}
{{- if $features.monitor }}
#include "apigear/tracer/tracer.h"
{{- end}}
#include <iostream>

using namespace {{ Camel .System.Name }};

int main(){
{{- if $features.monitor }}
    ApiGear::PocoImpl::Tracer tracer;
    tracer.connect("http://localhost:5555", "testExampleApp");
{{- end}}
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
    {{- $class := Camel $interface.Name }}
    {{- $tracer_class := printf "%sTraceDecorator" $class }}
    std::unique_ptr<{{ Camel $module.Name }}::I{{$class}}> test{{ Camel $module.Name }}{{$class}} = std::make_unique<{{ Camel $module.Name }}::{{$class}}>();
    {{ if $features.monitor }}std::unique_ptr<{{ Camel $module.Name }}::I{{$class}}> test{{ Camel $module.Name }}{{$tracer_class}} = {{ Camel $module.Name }}::{{$tracer_class}}::connect(*test{{ Camel $module.Name }}{{$class}}, tracer); {{- end}}
{{- end }}
{{- end }}

    // Demonstrate basic property access
    {{ $propertyExampleReady := 0 -}}
    {{ $operationExampleReady := 0 -}}
    {{- range .System.Modules -}}
    {{- $module := . -}}
    {{- range $module.Interfaces -}}
    {{- $interface := . -}}
{{- if (and (eq $propertyExampleReady 0) (len $interface.Properties) )}}
    {{- $property := (index $interface.Properties 0) }}
    {{- $class := Camel $interface.Name }}
    {{- $namespacePrefix := printf "%s::" (Camel $module.Name)}}
    {
        [[maybe_unused]] auto value = test{{ Camel $module.Name }}{{$class}}->get{{Camel $property.Name}}();
        std::cout << "{{ Camel $module.Name }}::{{$class}}::{{Camel $property.Name}} default value retrieved" << std::endl;
        test{{ Camel $module.Name }}{{$class}}->set{{Camel $property.Name}}({{cppDefault $namespacePrefix $property}});
        std::cout << "{{ Camel $module.Name }}::{{$class}}::{{Camel $property.Name}} value set" << std::endl;
    }
    {{ $propertyExampleReady = 1}}
{{- end }}
{{- if (and (eq $operationExampleReady 0) (len $interface.Operations))}}
    {{- $operation := (index $interface.Operations 0) }}
    {{- $class := Camel $interface.Name }}
    {{- $namespacePrefix := printf "%s::" (Camel $module.Name)}}
    {
        {{ if (not $operation.Return.IsVoid) }}[[maybe_unused]] auto result = {{ end }}test{{ Camel $module.Name }}{{$class}}->{{lower1 $operation.Name}}(
            {{- range $i, $e := $operation.Params }}
                {{- if $i }}, {{ end }}{{cppDefault $namespacePrefix $e}}
            {{- end }});
        std::cout << "{{ Camel $module.Name }}::{{$class}}::{{$operation.Name}} called" << std::endl;
    }
    {{ $operationExampleReady = 1}}
{{- end }}
{{- if (and $operationExampleReady $propertyExampleReady)}}
    {{- break}}
{{- end }}
{{- end}}
{{- if (and $operationExampleReady $propertyExampleReady)}}
    {{- break}}
{{- end }}
{{- end}}

    std::cout << "App example finished." << std::endl;
    return 0;
}
