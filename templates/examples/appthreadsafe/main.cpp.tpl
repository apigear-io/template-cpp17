{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
#include "{{snake $module.Name}}/implementation/{{ lower ( camel $interface.Name) }}.h"
#include "{{snake $module.Name}}/generated/core/{{ lower ( camel $interface.Name) }}.threadsafedecorator.h"
{{- end }}
{{- end }}{{nl}}

{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
    {{- $class := Camel $interface.Name }}
    {{- $tracer_class := printf "%sThreadSafeDecorator" $class }}
void test{{ Camel $module.Name }}{{$class}}()
{
    using namespace {{ Camel $.System.Name }}::{{ Camel $module.Name }};

    std::unique_ptr<I{{$class}}> test{{$class}} = std::make_unique<{{$tracer_class}}>(std::make_shared<{{$class}}>());

    // Thread safe access
{{- range $interface.Properties}}
{{- $property := . }}
    auto l_{{lower1 (Camel $property.Name)}} = {{cppDefault "" $property}};
    l_{{lower1 (Camel $property.Name)}} = test{{$class}}->get{{Camel $property.Name}}();
{{- if not .IsReadOnly }}
    test{{$class}}->set{{Camel $property.Name}}(l_{{lower1 (Camel $property.Name)}});
{{- end }}
{{- end }}
}{{nl}}
{{- end }}
{{- end }}

int main(){
{{- range .System.Modules }}
{{- $module := . }}
{{- range $module.Interfaces }}
{{- $interface := . }}
    {{- $class := Camel $interface.Name }}
    {{- $tracer_class := printf "%sThreadSafeDecorator" $class }}
    test{{ Camel $module.Name }}{{$class}}();
{{- end }}
{{- end }}

    return 0;
}
