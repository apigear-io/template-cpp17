{{- /* Copyright (c) ApiGear UG 2020 */ -}}
#include "{{snake .Module.Name}}/generated/core/{{snake .Module.Name}}.json.adapter.h"

namespace {{ Camel .System.Name }} {
namespace {{ Camel .Module.Name }} {

{{- range  .Module.Structs }}
{{- $class:= .Name }}
{{- $struct:= . }}
void from_json(const nlohmann::json& j, {{$class}}& p) {
    p = {{$class}}(
{{- range $idx, $elem :=  $struct.Fields }}
{{- $field:= . }}
        {{- if $idx -}},{{ end }}
        j.at("{{$field.Name}}").get<{{cppType "" $field}}>()
{{- end }}
    );
}
void to_json(nlohmann::json& j, const {{$class}}& p) {
    j = nlohmann::json{
    {{- range $idx, $elem :=  $struct.Fields }}
{{- $field:= . }}
        {{- if $idx -}},{{ end }}
        {"{{$field.Name}}", p.{{$field.Name}}}
{{- end }}
        };
}

std::ostream& operator<<(std::ostream& os, const {{$class}}& obj)
{
    nlohmann::json j = obj;
    os << j.dump(4);
    return os;
}
{{- end }}
} // namespace {{ Camel .Module.Name }}
} // namespace {{ Camel .System.Name }}
