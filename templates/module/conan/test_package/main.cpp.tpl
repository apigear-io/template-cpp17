{{- $module_id := snake .Module.Name }}
{{- range .Module.Interfaces }}
{{- $interface := . }}
#include "{{$module_id}}/implementation/{{ lower ( camel $interface.Name) }}.h"
{{- end }}

{{- if  ( len .Module.Interfaces ) }}

using namespace {{ Camel .System.Name }}::{{Camel .Module.Name }};
{{- end }}

int main(){
{{- range .Module.Interfaces }}
{{- $interface := . }}
    {{- $class := Camel $interface.Name }}
    std::unique_ptr<I{{$class}}> test{{$class}} = std::make_unique<{{$class}}>();
{{- end }}

    return 0;
}
